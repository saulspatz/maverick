#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "types.h"

extern int backup;
extern RankSet straights[];
extern pthread_mutex_t mutex1;
int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);
int bitcount(RankSet n);

int restoreState(State *state, unsigned long stop);
void saveState(State *state);

void dist_7_6_6_6() {
  extern RankSet ranks7[];
  RankSet *SPADES_START = ranks7;
  RankSet *SPADES_END = ranks7 + 867;
  RankSet *SYM_START = ranks7 + 848;

  extern RankSet suit6[];
  RankSet *HEARTS_START = suit6;
  RankSet *HEARTS_END = suit6 + 1715;

  extern RankSet suit6[];
  RankSet *DIAMONDS_START = suit6;
  extern RankSet suit6[];
  RankSet *CLUBS_START = suit6;

  State state;
  int factor;
  double begin, end;
  RankSet *clubs;

  RankSet *diamonds;
  RankSet *hearts;
  RankSet *spades;

  // check whether to continue an interrupted run
  strncpy(state.name, "dist_7_6_6_6", 20);
  int completed = restoreState(&state, SPADES_END-SPADES_START);
  if (completed) return;

  clubs = CLUBS_START + state.cc;

  diamonds = DIAMONDS_START + state.dd;
  hearts = HEARTS_START + state.hh;
  spades = SPADES_START + state.ss;
     
  begin = clock();

  while(1) {
    if (clubs < diamonds) {
      clubs++;
      if (hearts==clubs) factor = 4;
      else if (clubs==diamonds) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts == diamonds) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = 12;
      if (spades < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = (spades < SYM_START) ? 8 : 4;
    }
    else break;
    int result;
    result = 0;
    int heur = 0;

    RankSet intersect = *spades & *hearts & *diamonds;
    RankSet intersect2 = *spades & *clubs;
    RankSet int1, card;
    while (intersect) {
      int1 = intersect & (intersect-1);
      card = intersect & (~int1);
      intersect = int1;
      if (intersect2 & (~card)) {
        result = 1;
        heur = 1; 
        goto done;
      }
    }

    intersect = *spades & *hearts & *clubs;
    intersect2 = *spades & *diamonds;
    while (intersect) {
      int1 = intersect & (intersect-1);
      card = intersect & (~int1);
      intersect = int1;
      if (intersect2 & (~card)) {
        result = 1;
        heur = 1; 
        goto done;
      }
    }

    intersect = *spades & *diamonds & *clubs;
    intersect2 = *spades & *hearts;
    while (intersect) {
      int1 = intersect & (intersect-1);
      card = intersect & (~int1);
      intersect = int1;
      if (intersect2 & (~card)) {
        result =1;
        heur = 1; 
        goto done;
      }
    }
    
    // Check for a straight
    RankSet join = *spades | *hearts | *diamonds | *clubs;
    for (int m = 0; m <10; m++) {
      if ((join & straights[m]) != straights[m])
        continue;
      RankSet straight = straights[m];
      RankSet s = *spades & straight;
      RankSet h = *hearts & straight;
      RankSet d = *diamonds & straight;
      RankSet c = *clubs & straight;
      int bs = bitcount(s);
      int bh = bitcount(h);
      int bd = bitcount(d);
      int bc = bitcount(c);
      if ( bs < 2 || bh < 1 || bd < 1 || bc < 1)
        continue;
      if ( bs == 2 && bh == 1 && (*spades & *hearts) )
        continue;
      if ( bs == 2 && bd == 1 && (*spades &  *diamonds))
        continue;
      if ( bs == 2 && bc == 1 && (*spades &  *clubs))
        continue;
      if ( bh == 1 && bd == 1 && (*hearts & *diamonds) )
        continue;
      if ( bh == 1 && bc == 1 && (*hearts &  *clubs))
        continue;
      if ( bd == 2 && bc == 1 && (*diamonds & *clubs))
        continue;
      int cards[5];
      memset(cards, 0, sizeof(cards));
      // which cards of the straight are in each suit?
      RankSet st = straight;
      for (int j = 0; j < 5; j++) {  // for each bit 
        RankSet st1 = st & (st-1);   // clear lsb
        RankSet card = st & (~st1);  // isolate the bit
        st = st1;                    // remaining cards
        if (s & card) cards[j] |= 8;
        if (h & card) cards[j] |= 4;
        if (d & card) cards[j] |= 2;
        if (c & card) cards[j] |= 1;
      }
      int available[5];
      int used[5][4];
      memset(used, 0, sizeof(used));
      available[0] = cards[0];
      int k = 0;
      while (k >= 0) {
        while (available[k]) {
          if (1 & available[k]) {
            used[k][0] += 1;
            available[k] &= ~1;
          }
          else if (2 & available[k]) {
            used[k][1] += 1;
            available[k] &= ~2;
          }
          else if (4 & available[k]) {
            used[k][2] += 1;
            available[k] &= ~4;
          }
          else {
            used[k][3] += 1;
            available[k] &= ~8;
          }
          k++;
          if (k == 5) {
            result = 1;
            heur = 1;
            goto done;
          }
          available[k] =cards[k];
          for (int m = 0; m < 4; m++)
            used[k][m] = used[k-1][m];
          if (used[k][0]==1)
            available[k] &= ~1;
          if (used[k][1]==1)
            available[k] &= ~2;
          if (used[k][2]==1)
            available[k] &= ~4;
          if (used[k][3]==2)
          available[k] &= ~8;
        }
        k-=1;
      }
    }
    result = solver(*spades, *hearts, *diamonds, *clubs);

done:

    if (heur == 0) {
      state.exhaustC += 1;
      state.exhaustD += factor;
    } else {
      state.heurC += 1;
      state.heurD += factor;
    }

    if (result == 1) state.solutions += factor;
    pthread_mutex_lock( &mutex1 );
    if (backup) {
      end = clock();
      state.elapsed += (end-begin)/CLOCKS_PER_SEC;
      state.cc = clubs - CLUBS_START;
      state.dd = diamonds - DIAMONDS_START;
      state.hh = hearts - HEARTS_START;
      state.ss = spades - SPADES_START;
      saveState(&state);
      backup = 0;
      begin = clock();        
      }
      pthread_mutex_unlock( &mutex1 );
  }
  end = clock();
  state.elapsed += (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("../results/counts.csv", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",  
        "7-6-6-6", 
        state.exhaustC, 
        state.heurC, 
        state.skipC, 
        state.exhaustD, 
        state.heurD, 
        state.skipD, 
        state.solutions, 
        state.elapsed);
  fputs(buffer, out);
  fclose(out);
  state.cc = clubs - CLUBS_START;
  state.dd = diamonds - DIAMONDS_START;
  state.hh = hearts - HEARTS_START;
  state.ss = spades - SPADES_START + 1;  
  saveState(&state);  // last backup shows calculation complete
}

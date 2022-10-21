#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "types.h"
#include "straights.h"

extern int backup;
extern pthread_mutex_t mutex1;
int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);
int bitcount(RankSet n);

int restoreState(State *state, unsigned long stop);
void saveState(State *state);

void dist_7_7_6_5() {
  extern RankSet suit7[];
  RankSet *SPADES_START = suit7;
  RankSet *SPADES_END = suit7 + 1715;
  extern RankSet suit7[];
  RankSet *HEARTS_START = suit7;
  extern RankSet ranks6[];
  RankSet *DIAMONDS_START = ranks6;
  RankSet *DIAMONDS_END = ranks6 + 867;
  RankSet *SYM_START = ranks6 + 848;
  extern RankSet suit5[];
  RankSet *CLUBS_START = suit5;
  RankSet *CLUBS_END = suit5 + 1286;

  State state;
  int factor;
  double begin, end;
  RankSet *clubs;

  RankSet *diamonds;
  RankSet *hearts;
  RankSet *spades;

  // check whether to continue an interrupted run
  strncpy(state.name, "dist_7_7_6_5", 20);
  int completed = restoreState(&state, SPADES_END-SPADES_START);
  if (completed) return;

  clubs = CLUBS_START + state.cc;

  diamonds = DIAMONDS_START + state.dd;
  hearts = HEARTS_START + state.hh;
  spades = SPADES_START + state.ss;
     

  begin = clock();

  while (1) {
    if (clubs < CLUBS_END) {
      clubs++;
      factor = (hearts==spades) ? 12 : 24;
      if (diamonds < SYM_START) factor *= 2;
    }
    else if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts==spades) ? 12 : 24;
      if (diamonds < SYM_START) factor *= 2;
    }
    else if (hearts < spades) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (hearts==spades) ? 12 : 24;
      if (diamonds < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = (diamonds < SYM_START) ? 48 : 24;
    }
    else break;
    int result = 0;
    RankSet intersect = (*spades) & (*hearts) & (*diamonds);
    int bits = bitcount(intersect);
    if (bits>=2) result = 5;  //full house
    else if (bits==1) {
      if ((*spades & ~intersect) & (*hearts & ~intersect))
        result = 5; 
    }
    else { // look for a straight
      RankSet join = *spades | *hearts | *diamonds;
      for (int m = 0; m <10; m++) {
        if ((join & straights[m]) != straights[m])
          continue;
        RankSet straight = straights[m];
        RankSet s = *spades & straight;
        RankSet h = *hearts & straight;
        RankSet d = *diamonds & straight;
        int bs = bitcount(s);
        int bh = bitcount(h);
        int bd = bitcount(d);
        if ( bs < 2 || bh < 2 || bd < 1)
          continue;
        if ( bs == 2 && bd == 2 && (*spades & *hearts) )
          continue;
        if ( bs == 2 && bd == 1 && (*spades &  *diamonds))
          continue;
        if ( bd == 2 && bd == 1 && (*hearts &  *diamonds))
          continue;
        int cards[5];
        memset(cards, 0, sizeof(cards));
        // which cards of the straight are in each suit?
        RankSet st = straight;
        for (int j = 0; j < 5; j++) {  // for each bit 
          RankSet st1 = st & (st-1);   // clear lsb
          RankSet card = st & (~st1);  // isolate the bit
          st = st1;                    // remaining cards
          if (s & card) cards[j] |= 4;
          if (h & card) cards[j] |= 2;
          if (d & card) cards[j] |= 1;
        }
        int available[5];
        int choice[5];
        int used[5][3];
        memset(used, 0, sizeof(used));
        available[0] = cards[0];
        int k = 0;
        while (k >= 0) {
          while (available[k]) {
            if (1 & available[k]) {
              choice[k] = 0;
              used[k][0] += 1;
              available[k] &= ~1;
            }
            else if (2 & available[k]) {
              choice[k] = 1;
              used[k][1] += 1;
              available[k] &= ~2;
            }
            else {
              choice[k] = 2;
              used[k][2] += 1;
              available[k] &= ~4;
            }
            k++;
            if (k == 5) {
              result = 5;

              goto found;
            }
            available[k] =cards[k];
            for (int m = 0; m < 3; m++)
              used[k][m] = used[k-1][m];
            if (used[k][0]==1)
              available[k] &= ~1;
            if (used[k][1]==2)
              available[k] &= ~2;
            if (used[k][2]==2)
              available[k] &= ~4;
          }
          k -= 1;
        }
      }
    }
    if ( !result ) result = solver(*spades, *hearts, *diamonds, *clubs);

found:

    state.exhaustC += 1;
    state.exhaustD += factor;
    if (result == 5) {
      int skipped = CLUBS_END - clubs;
      state.skipC += skipped;
      state.skipD += factor*skipped;
      state.solutions += (skipped+1)*factor;
      clubs = CLUBS_END;
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
        "7-7-6-5", 
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

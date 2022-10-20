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
      for (int k = 0; k <10; k++) {
        if ((join & straights[k]) != straights[k])
          continue;
        RankSet s = *spades & straights[k];
        RankSet h = *hearts & straights[k];
        RankSet d = *diamonds & straights[k];
        if ((bitcount(s)<2) || (bitcount(h)<2) || (bitcount(d)<1))
          continue;
        int cards[5];
        memset(cards, 0, sizeof(cards));
        for (int k = 0; k < 5; k++) {
          RankSet st = straights[k];
          RankSet st1 = st & (st-1);
          RankSet card = st & (~st1);
          st = st1;
          if (s & card) cards[k] |= 0x100;
          if (h & card) cards[k] |= 0x01;
          if (d & card) cards[k] |= 0x11;
        }
        int available[5];
        int choice[5];
        int used[5][3];
        memset(used, 0, sizeof(used));
        available[0] = cards[0];
        int k = 0;
        while(k >= 0) {
          while (available[k]) {
            int a = 1;
            while (a& available[k]) 
              a <<= 1;
            available[k] &= (~a);
            choice[k] = a;
            if ( a == 1)
              used[k][0] += 1;
            else if (a== 2)
              used[k][1] += 1;
            else
              used[k][2] += 1;
            k++;
            if (k == 5) {
              result = 5;
              fprintf(stderr, "%x %x %x %d %d %d %d %d\n",
                              *spades, *hearts, *diamonds, 
                              choice[0], choice[1], choice[2], choice[3], choice[4]);
              break;
            }
            available[k] =cards[k];
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

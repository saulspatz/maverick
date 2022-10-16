#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "types.h"

extern int backup;
extern int interval;
int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

void sig_handler(int signum);
int restoreState(State *state, unsigned long stop);
void saveState(State *state);

void dist_8_7_5_5() {
  extern RankSet suit5[];
  RankSet *CLUBS_START = suit5;
  extern RankSet suit5[];
  RankSet *DIAMONDS_START = suit5;
  RankSet *DIAMONDS_END = suit5 + 1286;

  extern RankSet suit8[];
  RankSet *SPADES_START = suit8;
  RankSet *SPADES_END = suit8 + 1286;

  extern RankSet ranks7[];
  RankSet *HEARTS_START = ranks7;
  RankSet *HEARTS_END = ranks7 + 867;
  RankSet *SYM_START = ranks7 + 848;


  State state;
  int factor;
  double begin, end;
  RankSet *clubs;

  RankSet *diamonds;
  RankSet *hearts;
  RankSet *spades;

  // check whether to continue an interrupted run
  strncpy(state.name, "dist_8_7_5_5", 20);
  int completed = restoreState(&state, SPADES_END-SPADES_START);
  if (completed) return;

  clubs = CLUBS_START + state.cc;

  diamonds = DIAMONDS_START + state.dd;
  hearts = HEARTS_START + state.hh;
  spades = SPADES_START + state.ss;
     
  signal(SIGALRM,sig_handler); // Register signal handler
  alarm(interval);             // schedule a backup in an hour
  begin = clock();

  while(1) {
    if (clubs < diamonds) {
      clubs++;
      factor = (diamonds==clubs) ? 12 : 24;
      if (hearts < SYM_START) factor *= 2;
    }
    else if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts < SYM_START) ? 48 : 24;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (hearts < SYM_START) ? 24 : 12;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = (hearts < SYM_START) ? 24 : 12;
    }
    else break;
    int result = solver(*spades, *hearts, *diamonds, *clubs);
    state.exhaustC += 1;
    state.exhaustD += factor;
    if (result == 5) {
      int skipped = diamonds - 1 - clubs;
      if (skipped >= 0) {
        state.skipC += skipped;
        state.skipD += factor*skipped;
        state.solutions += (skipped+1)*factor;
        clubs = diamonds - 1;
       }
    else result = 1;  // ignore flush
    }

    if (result == 1) state.solutions += factor;
    if (backup) {
      end = clock();
      state.elapsed += (end-begin)/CLOCKS_PER_SEC;
      state.cc = clubs - CLUBS_START;

      state.dd = diamonds - DIAMONDS_START;
      state.hh = hearts - HEARTS_START;
      state.ss = spades - SPADES_START;
      saveState(&state);
      begin = clock();        
      }
  }
  end = clock();
  state.elapsed += (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("../results/counts.csv", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",  
        "8-7-5-5", 
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

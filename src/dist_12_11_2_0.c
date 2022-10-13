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

void dist_12_11_2_0() {
  extern RankSet suit12[];
  RankSet *SPADES_START = suit12;
  RankSet *SPADES_END = suit12 + 12;

  extern RankSet ranks11[];
  RankSet *HEARTS_START = ranks11;
  RankSet *HEARTS_END = ranks11 + 41;
  RankSet *SYM_START = ranks11 + 36;

  extern RankSet suit2[];
  RankSet *DIAMONDS_START = suit2;
  RankSet *DIAMONDS_END = suit2 + 77;


  State state;
  int factor;
  double begin, end;

  RankSet *diamonds;
  RankSet *hearts;
  RankSet *spades;

  // check whether to continue an interrupted run
  strncpy(state.name, "dist_12_11_2_0", 20);
  int completed = restoreState(&state, SPADES_END-SPADES_START);
  if (completed) return;


  diamonds = DIAMONDS_START + state.dd;
  hearts = HEARTS_START + state.hh;
  spades = SPADES_START + state.ss;
     
  signal(SIGALRM,sig_handler); // Register signal handler
  alarm(interval);             // schedule a backup in an hour
  begin = clock();

  while(1) {
    if (diamonds < DIAMONDS_END) {
      diamonds++;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts= HEARTS_START;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else break;
    int result = solver(*spades, *hearts, *diamonds, 0);
    state.exhaustC += 1;
    state.exhaustD += factor;

    if (result == 1) state.solutions += factor;
    if (backup) {
      end = clock();
      state.elapsed += (end-begin)/CLOCKS_PER_SEC;
      state.cc = 0;

      state.dd = diamonds - DIAMONDS_START;
      state.hh = hearts - HEARTS_START;
      state.ss = spades - SPADES_START;
      saveState(&state);
      begin = clock();        
      }
  }
  end = clock();
  state.elapsed += (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts1.log", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",  
        "{title}", 
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
  state.cc = 0;

  state.dd = diamonds - DIAMONDS_START;
  state.hh = hearts - HEARTS_START;
  state.ss = spades - SPADES_START;
  saveState(&state);  // last backup shows calculation complete
}

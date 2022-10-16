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

void dist_11_9_5_0() {
  extern RankSet suit11[];
  RankSet *SPADES_START = suit11;
  RankSet *SPADES_END = suit11 + 77;

  extern RankSet ranks9[];
  RankSet *HEARTS_START = ranks9;
  RankSet *HEARTS_END = ranks9 + 364;
  RankSet *SYM_START = ranks9 + 350;

<<<<<<< HEAD
<<<<<<<< HEAD:src/dist_11_9_5_0.c
  extern RankSet suit5[];
  RankSet *DIAMONDS_START = suit5;
  RankSet *DIAMONDS_END = DIAMONDS_START + 1286;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

========
  extern RankSet suit3[];
  RankSet *DIAMONDS_START = suit3;
  RankSet *DIAMONDS_END = suit3 + 285;

  extern RankSet suit2[];
  RankSet *CLUBS_START = suit2;
  RankSet *CLUBS_END = suit2 + 77;


  State state;
>>>>>>>> backup:src/dist_11_9_3_2.c
  int factor;
  double begin, end;
  RankSet *clubs;
=======
  extern RankSet suit5[];
  RankSet *DIAMONDS_START = suit5;
  RankSet *DIAMONDS_END = suit5 + 1286;


  State state;
  int factor;
  double begin, end;
>>>>>>> backup

  RankSet *diamonds;
  RankSet *hearts;
  RankSet *spades;

  // check whether to continue an interrupted run
<<<<<<< HEAD
  strncpy(state.name, "dist_11_9_3_2", 20);
  int completed = restoreState(&state, SPADES_END-SPADES_START);
  if (completed) return;

  clubs = CLUBS_START + state.cc;
=======
  strncpy(state.name, "dist_11_9_5_0", 20);
  int completed = restoreState(&state, SPADES_END-SPADES_START);
  if (completed) return;

>>>>>>> backup

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
<<<<<<< HEAD
<<<<<<<< HEAD:src/dist_11_9_5_0.c
    int result = solver(*spades, *hearts, *diamonds, 0);
    exhaustC += 1;
    exhaustD += factor;
    if (result == 5) {
      int skipped = DIAMONDS_END - diamonds;
      skipC += skipped;
      skipD += factor*skipped;
      solutions += (skipped+1)*factor;
      diamonds = DIAMONDS_END;
    }
    if (result == 1)      solutions += factor;
========
    int result = solver(*spades, *hearts, *diamonds, *clubs);
    state.exhaustC += 1;
    state.exhaustD += factor;
=======
    int result = solver(*spades, *hearts, *diamonds, 0);
    state.exhaustC += 1;
    state.exhaustD += factor;
    if (result == 5) {
      int skipped = DIAMONDS_END - diamonds;
      state.skipC += skipped;
      state.skipD += factor*skipped;
      state.solutions += (skipped+1)*factor;
      diamonds = DIAMONDS_END;
    }
>>>>>>> backup

    if (result == 1) state.solutions += factor;
    if (backup) {
      end = clock();
      state.elapsed += (end-begin)/CLOCKS_PER_SEC;
<<<<<<< HEAD
      state.cc = clubs - CLUBS_START;
=======
      state.cc = 0;
>>>>>>> backup

      state.dd = diamonds - DIAMONDS_START;
      state.hh = hearts - HEARTS_START;
      state.ss = spades - SPADES_START;
      saveState(&state);
      begin = clock();        
      }
<<<<<<< HEAD
>>>>>>>> backup:src/dist_11_9_3_2.c
=======
>>>>>>> backup
  }
  end = clock();
  state.elapsed += (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("../results/counts.csv", "a");
  char buffer[256];
<<<<<<< HEAD
<<<<<<<< HEAD:src/dist_11_9_5_0.c
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",
       "11-9-5-0", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions, time);
========
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",  
        "11-9-3-2", 
=======
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",  
        "11-9-5-0", 
>>>>>>> backup
        state.exhaustC, 
        state.heurC, 
        state.skipC, 
        state.exhaustD, 
        state.heurD, 
        state.skipD, 
        state.solutions, 
        state.elapsed);
<<<<<<< HEAD
>>>>>>>> backup:src/dist_11_9_3_2.c
  fputs(buffer, out);
  fclose(out);
  state.cc = clubs - CLUBS_START;
=======
  fputs(buffer, out);
  fclose(out);
  state.cc = 0;
>>>>>>> backup

  state.dd = diamonds - DIAMONDS_START;
  state.hh = hearts - HEARTS_START;
  state.ss = spades - SPADES_START + 1;  
  saveState(&state);  // last backup shows calculation complete
}

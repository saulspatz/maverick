#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

typedef struct {
  unsigned long exhaustC;  // classes
  unsigned long heurC;
  unsigned long skipC;
  unsigned long exhaustD;   // deals
  unsigned long heurD;
  unsigned long skipD;
  unsigned long solutions;
  double        elapsed;
  unsigned long cc;         // "loop counters"
  unsigned long dd;
  unsigned long hh;
  unsigned long ss; 
} State;
int backup = 0;
int interval = 3600;

void sig_handler(int signum){
  if (signum == SIGALRM) {
    backup = 1;
    alarm(interval);  // Schedule a new alarm after an hour
  }
}

extern RankSet suit8[];
RankSet *SPADES_START = suit8;
extern RankSet suit8[];
RankSet *HEARTS_START = suit8;
extern RankSet suit8[];
RankSet *DIAMONDS_START = suit8;
extern RankSet ranks1[];
RankSet *CLUBS_START = ranks1;
RankSet *SPADES_END = suit8 + 1286;
RankSet *CLUBS_END = ranks1 + 6;
RankSet *SYM_START = ranks1 + 6;

RankSet *spades;
RankSet *hearts;
RankSet *diamonds;
RankSet *clubs;

int restoreState(State *state, RankSet *stop) {
  FILE *saved = NULL;
  if (access("dist_8_8_8_1.sav1", F_OK))
    saved = fopen("dist_8_8_8_1.sav1", "r");
  else if (access("dist_8_8_8_1.sav2", F_OK))
    saved = fopen("dist_8_8_8_1.sav2", "r");
  if (saved) {
    fscanf(saved, "%lu, %lu, %lu, %lu", &state->cc, &state->dd, &state->hh, &state->ss);
    fscanf(saved, "%lu %lu %lu %lu %lu %lu %lu %lf", 
                  &state->exhaustC, &state->heurC, &state->skipC, 
                  &state->exhaustD, &state->heurD, &state->skipD, 
                  &state->solutions, &state->elapsed);
    if (spades >= stop)
      return 1;      //calculation already completed
  }
  else {             // initial run
    state->exhaustC = 0L;
    state->exhaustD = 0L;
    state->heurC = 0L;
    state->heurD = 0L;
    state->skipC = 0L;
    state->skipD = 0L;
    state->solutions = 0L;
    state->elapsed = 0;
    state->cc =-1;
    state->dd = 0;
    state->hh = 0;
    state->ss = 0;
  }   
  return 0;
}

void saveState(State *state) {
  if (access("dist_8_8__1.sav2",  F_OK))  // 2nd generation backup exists
    unlink("dist_8_8_8_1.sav2");
  if (access("dist_8_8__1.sav1", F_OK))  // 1st generation backup exists
    rename("dist_8_8_8_1.sav1", "dist_8_8_8_1.sav2");
  FILE *back = fopen("dist_8-8-8_1.sav1", "w");
  fprintf(back, "%lu %lu %lu %lu\n",
      clubs-CLUBS_START, 
      diamonds-DIAMONDS_START, 
      hearts-HEARTS_START,
      spades-SPADES_START);
  
  fprintf(back, "%lu %lu %lu %lu %lu %lu %lu %.2f\n", 
      state->exhaustC, 
      state->heurC, 
      state->skipC,
      state->exhaustD,
      state->heurD, 
      state->skipD, 
      state->solutions, 
      state->elapsed);
  fclose(back);
  backup = 0;
}

void dist_8_8_8_1() {
  
  State state;
  int factor;
  double begin, end;

  // check whether to continue an interrupted run
  int completed = restoreState(&state, SPADES_END);
  if (completed) return;

  clubs = CLUBS_START + state.cc;
  diamonds = DIAMONDS_START + state.dd;
  hearts = HEARTS_START + state.hh;
  spades = SPADES_START + state.ss;
     
  signal(SIGALRM,sig_handler); // Register signal handler
  alarm(interval);             // schedule a backup in an hour
  begin = clock();
  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (hearts < spades) {
      hearts++;
      diamonds = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = (hearts == spades) ? 12 : 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      hearts = HEARTS_START;
      diamonds  = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = (clubs < SYM_START) ? 24 : 12;
    }
    else break;
    int result = solver(*spades, *hearts, *diamonds, *clubs);
    state.exhaustC += 1;
    state.exhaustD += factor;
    if (result == 1) state.solutions += factor;
    if (backup) {
        end = clock();
        state.elapsed += (end-begin)/CLOCKS_PER_SEC;
        saveState(&state);
        begin = clock();        
      }
  }
  end = clock();
  state.elapsed += (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts1.log", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",  
        "8-8-8-1", 
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
  saveState(&state);  // last backup shows calculation complete
}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "types.h"

extern int backup;
extern int interval;

void sig_handler(int signum){
  if (signum == SIGALRM) {
    backup = 1;
    alarm(interval);  // Schedule a new alarm after an hour
  }
}

int restoreState(State *state, unsigned long stop) {
  FILE *saved = NULL;
  char gen1[32];
  char gen2[32];

  strncpy(gen1, state->name, 20);
  strncat(gen1, ".sav1", 6);
  strncpy(gen2, state->name, 20);
  strncat(gen2, ".sav2", 6);

  if (access(gen1, F_OK))
    saved = fopen(gen1, "r");
  else if (access(gen2, F_OK))
    saved = fopen(gen2, "r");
  if (saved) {
    fscanf(saved, "%lu, %lu, %lu, %lu", &state->cc, &state->dd, &state->hh, &state->ss);
    fscanf(saved, "%lu %lu %lu %lu %lu %lu %lu %lf", 
                  &state->exhaustC, &state->heurC, &state->skipC, 
                  &state->exhaustD, &state->heurD, &state->skipD, 
                  &state->solutions, &state->elapsed);
    if (state->ss >= stop)
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
  char gen1[32];
  char gen2[32];

  strncpy(gen1, state->name, 20);
  strncat(gen1, ".sav1", 6);
  strncpy(gen2, state->name, 20);
  strncat(gen2, ".sav2", 6);

  if (access(gen2,  F_OK))  // 2nd generation backup exists
    unlink(gen2);
  if (access(gen1, F_OK))  // 1st generation backup exists
    rename(gen1, gen2);
  FILE *back = fopen(gen1, "w");
  fprintf(back, "%lu %lu %lu %lu\n",
      state->cc, 
      state->dd, 
      state->hh,
      state->ss);
  
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
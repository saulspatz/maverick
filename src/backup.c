#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "types.h"

extern int backup;
extern int interval;

int fexists(const char *filename)
{   struct stat buffer;
    return stat(filename, &buffer) == 0 ? 1 : 0;
}

int restoreState(State *state, unsigned long stop) {
  FILE *saved = NULL;
  char gen1[36];
  char gen2[36];

  memset(gen1, 0, sizeof(gen1));
  memset(gen2, 0, sizeof(gen2));
  strncpy(gen1, "../results/", 12);
  strncat(gen1, state->name, 20);
  strncat(gen1, ".sav1", 6);
  strncpy(gen2, "../results/", 12);
  strncat(gen2, state->name, 20);
  strncat(gen2, ".sav2", 6);

  if (fexists(gen1))
    saved = fopen(gen1, "r");
  else if (fexists(gen2))
    saved = fopen(gen2, "r");
  if (saved) {
    fscanf(saved, "%lu %lu %lu %lu", &state->cc, &state->dd, &state->hh, &state->ss);
    fscanf(saved, "%lu %lu %lu %lu %lu %lu %lu %lf", 
                  &state->exhaustC, &state->heurC, &state->skipC, 
                  &state->exhaustD, &state->heurD, &state->skipD, 
                  &state->solutions, &state->elapsed);
    if (state->ss >= stop)
      return 1;      //calculation already completed
  }
  else {             // initial run
    int n = strlen(state->name);
    int noClubs = (state->name[n-1]=='0'); 
    state->exhaustC = 0L;
    state->exhaustD = 0L;
    state->heurC = 0L;
    state->heurD = 0L;
    state->skipC = 0L;
    state->skipD = 0L;
    state->solutions = 0L;
    state->elapsed = 0;
    if (noClubs){
      state->cc = 0;
      state->dd = -1;
    } else {
      state->cc =-1;
      state->dd = 0;
    }
    state->hh = 0;
    state->ss = 0;
  }   
  return 0;
}

void saveState(State *state) {
  char gen1[36];
  char gen2[36];

  memset(gen1, 0, sizeof(gen1));
  memset(gen2, 0, sizeof(gen2));
  strncpy(gen1, "../results/", 12);
  strncat(gen1, state->name, 20);
  strncat(gen1, ".sav1", 6);
  strncpy(gen2, "../results/", 12);
  strncat(gen2, state->name, 20);
  strncat(gen2, ".sav2", 6);

  if (fexists(gen2))  // 2nd generation backup exists
    unlink(gen2);
  if (fexists(gen1))  // 1st generation backup exists
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
}

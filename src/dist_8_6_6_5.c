#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "types.h"

extern int backup;
extern pthread_mutex_t mutex1;
int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);
int hasStraight3(RankSet spades, RankSet hearts, RankSet diamonds);


int restoreState(State *state, unsigned long stop);
void saveState(State *state);

void dist_8_6_6_5() {
  extern RankSet suit6[];
  RankSet *HEARTS_START = suit6;
  RankSet *HEARTS_END = suit6 + 1715;

  extern RankSet suit6[];
  RankSet *DIAMONDS_START = suit6;
  extern RankSet ranks8[];
  RankSet *SPADES_START = ranks8;
  RankSet *SPADES_END = ranks8 + 650;
  RankSet *SYM_START = ranks8 + 636;

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
  strncpy(state.name, "dist_8_6_6_5", 20);
  int completed = restoreState(&state, SPADES_END-SPADES_START);
  if (completed) return;

  clubs = CLUBS_START + state.cc;

  diamonds = DIAMONDS_START + state.dd;
  hearts = HEARTS_START + state.hh;
  spades = SPADES_START + state.ss;
     

  begin = clock();

  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = (spades < SYM_START) ? 24 : 12;
    }
    else break;

    int result = 0;
    // Since the heuristic tries to make a straight without breaking
    // up the clubs, there's no point in checking again until 
    // another suit changes

    int heur = 0;
    if (clubs == CLUBS_START)
      heur = hasStraight3(*spades, *hearts, *diamonds); 
    if (heur)
      result = 5;
    else
      result = solver(*spades, *hearts, *diamonds, *clubs);

    if (heur == 0) {
      state.exhaustC += 1;
      state.exhaustD += factor;
    } else {
      state.heurC += 1;
      state.heurD += factor;
    }
 
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
        "8-6-6-5", 
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

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
int hasStraight4(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);
int bitcount(RankSet n);
int restoreState(State *state, unsigned long stop);
void saveState(State *state);

int testFull(RankSet intersect3, RankSet intersect2) {
  RankSet int1, card;
  while (intersect3) {
    int1 = intersect3 & (intersect3-1);  
    card = intersect3 & (~int1);  // card = least significant 1 bit
    intersect3 = int1;
    if (intersect2 & (~card)) 
      return 1; 
  }
  return 0;
}

int hasFull(RankSet spades, RankSet hearts, RankSet diamonds, RankSet clubs) {
  RankSet intersect = spades & hearts & diamonds;
  RankSet intersect2 = spades & clubs;
  if (testFull(intersect, intersect2)) 
    return 1;
  
  intersect = spades & hearts & clubs;
  intersect2 = spades & diamonds;
  if (testFull(intersect, intersect2)) 
    return 1;

  intersect = spades & diamonds & clubs;
  intersect2 = spades & hearts;
  if (testFull(intersect, intersect2)) 
    return 1;

  return 0;
}

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

    int heur = hasFull(*spades, *hearts, *diamonds, *clubs);
    
    fprintf(stderr, "%x %x %x %x full %d\n",   
       *spades, *hearts, *diamonds, *clubs, heur);

    if (!heur)
      heur = hasStraight4(*spades, *hearts, *diamonds, *clubs);

    if (!heur)
      result = solver(*spades, *hearts, *diamonds, *clubs);

    if (heur == 0) {
      state.exhaustC += 1;
      state.exhaustD += factor;
    } else {
      state.heurC += 1;
      state.heurD += factor;
      result = 1;
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

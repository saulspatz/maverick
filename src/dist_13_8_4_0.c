#include <stdio.h>
#include <time.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

void dist_13_8_4_0() {
  extern RankSet suit13[];
  RankSet *SPADES_START = suit13;
  RankSet *SPADES_END = SPADES_START + 0;

  extern RankSet ranks8[];
  RankSet *HEARTS_START = ranks8;
  RankSet *HEARTS_END = HEARTS_START + 650;
  RankSet *SYM_START = HEARTS_START + 636;

  extern RankSet suit4[];
  RankSet *DIAMONDS_START = suit4;
  RankSet *DIAMONDS_END = DIAMONDS_START + 714;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long exhaustC = 0L;  // classes
  unsigned long heurC = 0L;
  unsigned long skipC = 0L;
  unsigned long exhaustD = 0L;   // deals
  unsigned long heurD = 0L;
  unsigned long skipD = 0L;
  unsigned long solutions = 0L;
  double begin, end;
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
    exhaustC += 1;
    exhaustD += factor;
    if (result == 1)      solutions += factor;
  }
  end = clock();
  double time = (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts.log", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",
       "13-8-4-0", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions, time);
  fputs(buffer, out);
  fclose(out);
}
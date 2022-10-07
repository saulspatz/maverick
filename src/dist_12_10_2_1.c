#include <stdio.h>
#include <time.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

void dist_12_10_2_1() {
  extern RankSet suit12[];
  RankSet *SPADES_START = suit12;
  RankSet *SPADES_END = SPADES_START + 12;

  extern RankSet ranks10[];
  RankSet *HEARTS_START = ranks10;
  RankSet *HEARTS_END = HEARTS_START + 145;
  RankSet *SYM_START = HEARTS_START + 140;

  extern RankSet suit2[];
  RankSet *DIAMONDS_START = suit2;
  RankSet *DIAMONDS_END = DIAMONDS_START + 77;

  extern RankSet suit1[];
  RankSet *CLUBS_START = suit1;
  RankSet *CLUBS_END = CLUBS_START + 12;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
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
    if (clubs < CLUBS_END) {
      clubs++;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts= HEARTS_START;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else break;
    int result = solver(*spades, *hearts, *diamonds, *clubs);
    exhaustC += 1;
    exhaustD += factor;
    if (result == 1)      solutions += factor;
  }
  end = clock();
  double time = (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts.log", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",
       "12-10-2-1", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions, time);
  fputs(buffer, out);
  fclose(out);
}
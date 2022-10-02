#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

void dist_10_8_7_0() {
  extern RankSet suit10[];
  RankSet *SPADES_START = suit10;
  RankSet *SPADES_END = SPADES_START + 285;

  extern RankSet suit8[];
  RankSet *HEARTS_START = suit8;
  RankSet *HEARTS_END = HEARTS_START + 1286;

  extern RankSet ranks7[];
  RankSet *DIAMONDS_START = ranks7;
  RankSet *DIAMONDS_END = DIAMONDS_START + 867;
  RankSet *SYM_START = DIAMONDS_START + 848;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long exhaustC = 0L;
  unsigned long heurC = 0L;
  unsigned long skipC = 0L;
  unsigned long exhaustD = 0L;
  unsigned long heurD = 0L;
  unsigned long skipD = 0L;
  unsigned long solutions = 0L;
  double begin, end;
  begin = clock();
  while(1) {
    if (diamonds < DIAMONDS_END) {
      diamonds++;
      factor = diamonds < SYM_START ? 48 : 24;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = diamonds < SYM_START ? 48 : 24;
    }
    else if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts= HEARTS_START;
      factor = diamonds < SYM_START ? 48 : 24;
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
  setlocale(LC_ALL, "");
  fprintf(out, "%-9s %'18lu %'18lu %'18lu %'18lu %'18lu %'18lu %'18lu\n",
      "10-8-7-0", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions);
   fprintf(stderr, "%.2f", time);
  fclose(out);
}
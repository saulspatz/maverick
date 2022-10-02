#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

void dist_9_8_8_0() {
  extern RankSet ranks9[];
  RankSet *SPADES_START = ranks9;
  RankSet *SPADES_END = SPADES_START + 364;
  RankSet *SYM_START = SPADES_START + 350;

  extern RankSet suit8[];
  RankSet *HEARTS_START = suit8;
  RankSet *HEARTS_END = HEARTS_START + 1286;

  extern RankSet suit8[];
  RankSet *DIAMONDS_START = suit8;
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
  while (1) {
    if (diamonds < hearts) {
      diamonds++;
      factor = (diamonds == hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = (spades < SYM_START) ? 48 : 24;
    }
    else if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
     factor = (spades < SYM_START) ? 24 : 12;
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
      "9-8-8-0", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions);
   fprintf(stderr, "%.2f", time);
  fclose(out);
}
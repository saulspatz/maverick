#include <stdio.h>
#include <locale.h>
#include "types.h"

void dist1177() {
  extern RankSet ranks11[];
  RankSet *SPADES_START = ranks11;
  RankSet *SPADES_END = SPADES_START + 41;
  RankSet *SYM_START = SPADES_START + 36;

  extern RankSet suit7[];
  RankSet *HEARTS_START = suit7;
  RankSet *HEARTS_END = HEARTS_START + 1715;

  extern RankSet suit7[];
  RankSet *DIAMONDS_START = suit7;
  RankSet *DIAMONDS_END = DIAMONDS_START + 1715;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
  while (1) {
    if (diamonds < hearts) {
      diamonds++;
      factor = (diamonds == hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = (spades < SYM_START) ? 24 : 48;
    }
    if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      (spades < SYM_START) ? 12 : 24;
    }
    else break;
    deals += factor;
    classes += 1;
  }
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%9s %'15lu %'15lu\n", "11-7-7-0", deals, classes);
  fclose(out);
}
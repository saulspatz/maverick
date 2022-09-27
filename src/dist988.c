#include <stdio.h>
#include <locale.h>
#include "types.h"

void dist988() {
  extern RankSet ranks9[];
  RankSet *SPADES_START = ranks9;
  RankSet *SPADES_END = SPADES_START + 364;
  RankSet *SYM_START = SPADES_START + 350;

  extern RankSet suit8[];
  RankSet *HEARTS_START = suit8;
  RankSet *HEARTS_END = HEARTS_START + 1286;

  extern RankSet suit8[];
  RankSet *DIAMONDS_START = suit8;
  RankSet *DIAMONDS_END = DIAMONDS_START + 1286;

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
  fprintf(out, "%9s %'15lu %'15lu\n", "9-8-8-0", deals, classes);
  fclose(out);
}
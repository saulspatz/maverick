#include <stdio.h>
#include <locale.h>
#include "types.h"

void dist997() {
  extern RankSet suit9[];
  RankSet *SPADES_START = suit9;
  RankSet *SPADES_END = SPADES_START + 714;

  extern RankSet suit9[];
  RankSet *HEARTS_START = suit9;
  RankSet *HEARTS_END = HEARTS_START + 714;

  extern RankSet ranks7[];
  RankSet *DIAMONDS_START = ranks7;
  RankSet *DIAMONDS_END = DIAMONDS_START + 867;
  RankSet *SYM_START = DIAMONDS_START + 848;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
  while (1) {
    if (diamonds < DIAMONDS_END) {
      diamonds++;
    factor = (hearts == spades) ? 12 : 24;
    if (diamonds < SYM_START) factor *= 2;
    }
    else if (hearts < spades) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = (hearts == spades) ? 12 : 24;
    if (diamonds < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = diamonds < SYM_START ? 24 : 48;
    }
    else break;
    deals += factor;
    classes += 1;
  }
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%9s %'15lu %'15lu\n", "9-9-7-0", deals, classes);
  fclose(out);
}
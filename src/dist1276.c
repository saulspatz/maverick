#include <stdio.h>
#include <locale.h>
#include "types.h"

void dist1276() {
  extern RankSet suit12[];
  RankSet *SPADES_START = suit12;
  RankSet *SPADES_END = SPADES_START + 12;

  extern RankSet ranks7[];
  RankSet *HEARTS_START = ranks7;
  RankSet *HEARTS_END = HEARTS_START + 867;
  RankSet *SYM_START = HEARTS_START + 848;

  extern RankSet suit6[];
  RankSet *DIAMONDS_START = suit6;
  RankSet *DIAMONDS_END = DIAMONDS_START + 1715;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
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
    deals += factor;
    classes += 1;
  }
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%9s %'15lu %'15lu\n", "12-7-6-0", deals, classes);
  fclose(out);
}
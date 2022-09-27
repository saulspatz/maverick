#include <stdio.h>
#include <locale.h>
#include "types.h"

void dist1186() {
  extern RankSet suit11[];
  RankSet *SPADES_START = suit11;
  RankSet *SPADES_END = SPADES_START + 77;

  extern RankSet suit8[];
  RankSet *HEARTS_START = suit8;
  RankSet *HEARTS_END = HEARTS_START + 1286;

  extern RankSet ranks6[];
  RankSet *DIAMONDS_START = ranks6;
  RankSet *DIAMONDS_END = DIAMONDS_START + 867;
  RankSet *SYM_START = DIAMONDS_START + 848;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
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
    deals += factor;
    classes += 1;
  }
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%9s %'15lu %'15lu\n", "11-8-6-0", deals, classes);
  fclose(out);
}
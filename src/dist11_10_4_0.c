#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

void dist111040() {
  extern RankSet suit11[];
  RankSet *SPADES_START = suit11;
  RankSet *SPADES_END = SPADES_START + 77;

  extern RankSet suit10[];
  RankSet *HEARTS_START = suit10;
  RankSet *HEARTS_END = HEARTS_START + 285;

  extern RankSet ranks4[];
  RankSet *DIAMONDS_START = ranks4;
  RankSet *DIAMONDS_END = DIAMONDS_START + 364;
  RankSet *SYM_START = DIAMONDS_START + 350;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
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
    deals += factor;
    classes += 1;
  }
  end = clock();
  double time = (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%-9s %'18lu %'18lu %8.2f\n", "11-10-4-0", deals, classes, time);
  fclose(out);
}
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

void dist111130() {
  extern RankSet suit11[];
  RankSet *SPADES_START = suit11;
  RankSet *SPADES_END = SPADES_START + 77;

  extern RankSet suit11[];
  RankSet *HEARTS_START = suit11;
  extern RankSet ranks3[];
  RankSet *DIAMONDS_START = ranks3;
  RankSet *DIAMONDS_END = DIAMONDS_START + 145;
  RankSet *SYM_START = DIAMONDS_START + 140;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
  double begin, end;
  begin = clock();
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
  end = clock();
  double time = (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%9s %'15lu %'15lu %.2f\n", "11-11-3-0", deals, classes, time);
  fclose(out);
}
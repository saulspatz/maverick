#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

void dist11770() {
  extern RankSet ranks11[];
  RankSet *SPADES_START = ranks11;
  RankSet *SPADES_END = SPADES_START + 41;
  RankSet *SYM_START = SPADES_START + 36;

  extern RankSet suit7[];
  RankSet *HEARTS_START = suit7;
  RankSet *HEARTS_END = HEARTS_START + 1715;

  extern RankSet suit7[];
  RankSet *DIAMONDS_START = suit7;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;

  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
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
    deals += factor;
    classes += 1;
  }
  end = clock();
  double time = (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%-9s %'18lu %'18lu %8.2f\n", "11-7-7-0", deals, classes, time);
  fclose(out);
}
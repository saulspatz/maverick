#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

void dist11662() {
  extern RankSet suit6[];
  RankSet *HEARTS_START = suit6;
  RankSet *HEARTS_END = HEARTS_START + 1715;

  extern RankSet suit6[];
  RankSet *DIAMONDS_START = suit6;
  extern RankSet ranks11[];
  RankSet *SPADES_START = ranks11;
  RankSet *SPADES_END = SPADES_START + 41;
  RankSet *SYM_START = SPADES_START + 36;

  extern RankSet suit2[];
  RankSet *CLUBS_START = suit2;
  RankSet *CLUBS_END = CLUBS_START + 77;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
  double begin, end;
  begin = clock();
  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
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
  fprintf(out, "%-9s %'18lu %'18lu %8.2f\n", "11-6-6-2", deals, classes, time);
  fclose(out);
}
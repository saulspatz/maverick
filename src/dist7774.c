#include <stdio.h>
#include <locale.h>
#include "types.h"

void dist7774() {
  extern RankSet suit7[];
  RankSet *SPADES_START = suit7;
  RankSet *SPADES_END = SPADES_START + 1715;

  extern RankSet suit7[];
  RankSet *HEARTS_START = suit7;
  RankSet *HEARTS_END = HEARTS_START + 1715;

  extern RankSet suit7[];
  RankSet *DIAMONDS_START = suit7;
  RankSet *DIAMONDS_END = DIAMONDS_START + 1715;

  extern RankSet ranks4[];
  RankSet *CLUBS_START = ranks4;
  RankSet *CLUBS_END = CLUBS_START + 364;
  RankSet *SYM_START = CLUBS_START + 350;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (hearts < spades) {
      hearts++;
      diamonds = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = (hearts == spades) ? 12 : 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      hearts = HEARTS_START;
      diamonds  = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = (clubs < SYM_START) ? 24 : 12;
    }
    else break;
    deals += factor;
    classes += 1;
  }
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%9s %'15lu %'15lu\n", "7-7-7-4", deals, classes);
  fclose(out);
}
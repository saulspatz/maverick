#include <stdio.h>
#include <locale.h>
#include "types.h"

void dist13633() {
  extern RankSet suit3[];
  RankSet *CLUBS_START = suit3;
  RankSet *CLUBS_END = CLUBS_START + 285;

  extern RankSet suit3[];
  RankSet *DIAMONDS_START = suit3;
  RankSet *DIAMONDS_END = DIAMONDS_START + 285;

  extern RankSet suit13[];
  RankSet *SPADES_START = suit13;
  RankSet *SPADES_END = SPADES_START + 0;

  extern RankSet ranks6[];
  RankSet *HEARTS_START = ranks6;
  RankSet *HEARTS_END = HEARTS_START + 867;
  RankSet *SYM_START = HEARTS_START + 848;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  unsigned long deals = 0L;
  unsigned long classes = 0L;
  while(1) {
    if (clubs < diamonds) {
      clubs++;
      factor = (diamonds==clubs) ? 12 : 24;
      if (hearts < SYM_START) factor *= 2;
    }
    else if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts < SYM_START) ? 48 : 24;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (hearts < SYM_START) ? 24 : 12;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = (hearts < SYM_START) ? 24 : 12;
    }
    else break;
    deals += factor;
    classes += 1;
  }
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%9s %'15lu %'15lu\n", "13-6-3-3", deals, classes);
  fclose(out);
}
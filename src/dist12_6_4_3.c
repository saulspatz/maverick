#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

void dist12643() {
  extern RankSet suit12[];
  RankSet *SPADES_START = suit12;
  RankSet *SPADES_END = SPADES_START + 12;

  extern RankSet ranks6[];
  RankSet *HEARTS_START = ranks6;
  RankSet *HEARTS_END = HEARTS_START + 867;
  RankSet *SYM_START = HEARTS_START + 848;

  extern RankSet suit4[];
  RankSet *DIAMONDS_START = suit4;
  RankSet *DIAMONDS_END = DIAMONDS_START + 714;

  extern RankSet suit3[];
  RankSet *CLUBS_START = suit3;
  RankSet *CLUBS_END = CLUBS_START + 285;

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
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (diamonds < DIAMONDS_END) {
      diamonds++;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts= HEARTS_START;
      factor = hearts < SYM_START ? 48 : 24;
    }
    else break;
    deals += factor;
    classes += 1;
  }
  end = clock();
  double time = (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%-9s %'18lu %'18lu %8.2f\n", "12-6-4-3", deals, classes, time);
  fclose(out);
}
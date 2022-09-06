#include <stdio.h>
#include "types.h"

void dist13444() {
  extern RankSet suit13[];
  extern RankSet suit4[];
  extern Cards13 spades13[];
  extern Cards4 hearts4[];
  RankSet *SPADES_START = suit13;
  RankSet *HEARTS_START = suit4;
  extern Cards4 diamonds4[];
  RankSet *DIAMONDS_START = suit4;
  extern Cards4 clubs4[];
  RankSet *CLUBS_START = suit4;
  RankSet *SPADES_END  = SPADES_START + 0;
  RankSet *HEARTS_END  = HEARTS_START + 714;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  long total = 0L;
  RankSet Phony = 0;
  while(1) {
    if (clubs < diamonds) {
      clubs++;
      if (hearts==clubs) factor = 4;
      else if (clubs==diamonds) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      goto compute;
    }
    if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts == diamonds) ? 12 : 24;
      goto compute;
    }
    if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = 12;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = 4;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds & *clubs;
  }

  printf("13-4-4-4: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
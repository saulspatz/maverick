#include <stdio.h>
#include "types.h"

void dist12733() {
  extern RankSet suit12[];
  extern RankSet suit7[];
  extern Cards12 spades12[];
  extern Cards7 hearts7[];
  extern RankSet suit3[];
  RankSet *SPADES_START = suit12;
  RankSet *HEARTS_START = suit7;
  extern Cards3 diamonds3[];
  RankSet *DIAMONDS_START = suit3;
  extern Cards3 clubs3[];
  RankSet *CLUBS_START = suit3;
  RankSet *SPADES_END  = SPADES_START + 12;
  RankSet *HEARTS_END  = HEARTS_START + 1715;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 285;
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
      factor = (clubs==diamonds) ? 12 : 24;
      goto compute;
    }
    if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = 24;
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
      factor = 12;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds & *clubs;
  }

  printf("12-7-3-3: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
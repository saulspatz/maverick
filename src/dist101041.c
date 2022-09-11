#include <stdio.h>
#include "types.h"

void dist101041() {
  extern RankSet suit10[];
  extern RankSet suit10[];
  extern Cards10 spades10[];
  extern Cards10 hearts10[];
  extern RankSet suit4[];
  extern RankSet suit1[];
  RankSet *SPADES_START = suit10;
  RankSet *HEARTS_START = suit10;
  extern Cards4 diamonds4[];
  RankSet *DIAMONDS_START = suit4;
  extern Cards1 clubs1[];
  RankSet *CLUBS_START = suit1;
  RankSet *SPADES_END  = SPADES_START + 285;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 714;
  RankSet *CLUBS_END  = CLUBS_START + 12;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  long total = 0L;
  RankSet Phony = 0;
  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      factor = (hearts==spades) ? 12 : 24;
      goto compute;
    }
    if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts==spades) ? 12 : 24;
      goto compute;
    }
    if (hearts < spades) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (hearts==spades) ? 12 : 24;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = 24;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds & *clubs;
  }

  printf("10-10-4-1: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
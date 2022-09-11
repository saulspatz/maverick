#include <stdio.h>
#include "types.h"

void dist8854() {
  extern RankSet suit8[];
  extern RankSet suit8[];
  extern Cards8 spades8[];
  extern Cards8 hearts8[];
  extern RankSet suit5[];
  extern RankSet suit4[];
  RankSet *SPADES_START = suit8;
  RankSet *HEARTS_START = suit8;
  extern Cards5 diamonds5[];
  RankSet *DIAMONDS_START = suit5;
  extern Cards4 clubs4[];
  RankSet *CLUBS_START = suit4;
  RankSet *SPADES_END  = SPADES_START + 1286;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 1286;
  RankSet *CLUBS_END  = CLUBS_START + 714;
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

  printf("8-8-5-4: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
#include <stdio.h>
#include "types.h"

void dist8755() {
  extern RankSet suit8[];
  extern RankSet suit7[];
  extern RankSet suit5[];
  RankSet *SPADES_START = suit8;
  RankSet *HEARTS_START = suit7;
  RankSet *DIAMONDS_START = suit5;
  RankSet *CLUBS_START = suit5;
  RankSet *SPADES_END  = SPADES_START + 1286;
  RankSet *HEARTS_END  = HEARTS_START + 1715;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 1286;
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

  printf("8-7-5-5: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
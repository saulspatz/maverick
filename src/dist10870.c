#include <stdio.h>
#include "types.h"

void dist10870() {
  extern RankSet suit10[];
  extern RankSet suit8[];
  extern RankSet suit7[];
  RankSet *SPADES_START = suit10;
  RankSet *HEARTS_START = suit8;
  RankSet *DIAMONDS_START = suit7;
  RankSet *SPADES_END  = SPADES_START + 285;
   RankSet *HEARTS_END  = HEARTS_START + 1286;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 1715;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;
  int factor;
  long total = 0L;
  RankSet Phony = 0;
  while(1) {
    if (diamonds < DIAMONDS_END) {
      diamonds++;
      factor = 24;
      goto compute;
    }
    if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = 24;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts= HEARTS_START;
      factor = 24;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds;
  }

  printf("10-8-7-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
#include <stdio.h>
#include "types.h"

void dist9880() {
  extern RankSet suit9[];
  extern RankSet suit8[];
  extern Cards9 spades9[];
  extern Cards8 hearts8[];
  RankSet *SPADES_START = suit9;
  RankSet *HEARTS_START = suit8;
  extern Cards8 diamonds8[];
  RankSet *DIAMONDS_START = suit8;
  RankSet *SPADES_END  = SPADES_START + 714;
  RankSet *HEARTS_END  = HEARTS_START + 1286;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START-1;
  int factor;
  long total = 0L;
  RankSet Phony = 0;
  while(1) {
    if (diamonds < hearts) {
      diamonds++;
      factor = (diamonds == hearts) ? 12 : 24;
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
      factor = 12;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds;
  }

  printf("9-8-8-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
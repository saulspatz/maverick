#include <stdio.h>
#include "types.h"

void dist9970() {
  extern RankSet suit9[];
  extern RankSet suit9[];
  extern Cards9 spades9[];
  extern Cards9 hearts9[];
  extern RankSet suit7[];
  RankSet *SPADES_START = suit9;
  RankSet *HEARTS_START = suit9;
  extern Cards7 diamonds7[];
  RankSet *DIAMONDS_START = suit7;
  RankSet *SPADES_END  = SPADES_START + 714;
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
      factor = (hearts == spades) ? 12 : 24;
      goto compute;
    }
    if (hearts < spades) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = (hearts == spades) ? 12 : 24;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = 24;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds;
  }

  printf("9-9-7-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
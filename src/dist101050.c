#include <stdio.h>
#include "types.h"

void dist101050() {
  extern RankSet suit10[];
  extern RankSet suit10[];
  extern RankSet suit5[];
  RankSet *SPADES_START = suit10;
  RankSet *HEARTS_START = suit10;
  RankSet *DIAMONDS_START = suit5;
  RankSet *SPADES_END  = SPADES_START + 285;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 1286;
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

  printf("10-10-5-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
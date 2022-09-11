#include <stdio.h>
#include "types.h"

void dist111130() {
  extern RankSet suit11[];
  extern RankSet suit11[];
  extern Cards11 spades11[];
  extern Cards11 hearts11[];
  extern RankSet suit3[];
  RankSet *SPADES_START = suit11;
  RankSet *HEARTS_START = suit11;
  extern Cards3 diamonds3[];
  RankSet *DIAMONDS_START = suit3;
  RankSet *SPADES_END  = SPADES_START + 77;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 285;
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

  printf("11-11-3-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
#include <stdio.h>
#include "types.h"

void dist11770() {
  extern RankSet suit11[];
  extern RankSet suit7[];
  extern Cards11 spades11[];
  extern Cards7 hearts7[];
  RankSet *SPADES_START = suit11;
  RankSet *HEARTS_START = suit7;
  extern Cards7 diamonds7[];
  RankSet *DIAMONDS_START = suit7;
  RankSet *SPADES_END  = SPADES_START + 77;
  RankSet *HEARTS_END  = HEARTS_START + 1715;
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

  printf("11-7-7-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
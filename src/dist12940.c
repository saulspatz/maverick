#include <stdio.h>
#include "types.h"

void dist12940() {
  extern RankSet suit12[];
  extern RankSet suit9[];
  extern RankSet suit4[];
  RankSet *SPADES_START = suit12;
  RankSet *HEARTS_START = suit9;
  RankSet *DIAMONDS_START = suit4;
  RankSet *SPADES_END  = SPADES_START + 12;
   RankSet *HEARTS_END  = HEARTS_START + 714;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 714;
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

  printf("12-9-4-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
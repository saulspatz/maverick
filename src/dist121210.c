#include <stdio.h>
#include "types.h"

void dist121210() {
  extern RankSet suit12[];
  extern RankSet suit12[];
  extern Cards12 spades12[];
  extern Cards12 hearts12[];
  extern RankSet suit1[];
  RankSet *SPADES_START = suit12;
  RankSet *HEARTS_START = suit12;
  extern Cards1 diamonds1[];
  RankSet *DIAMONDS_START = suit1;
  RankSet *SPADES_END  = SPADES_START + 12;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 12;
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

  printf("12-12-1-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
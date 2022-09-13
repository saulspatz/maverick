#include <stdio.h>
#include "types.h"

void dist131110() {
  extern RankSet ranks13[];
  extern RankSet suit11[];
  extern Cards13 swords13[];
  extern Cards11 hearts11[];
  extern RankSet suit1[];
  RankSet *SPADES_START = ranks13;
  RankSet *HEARTS_START = suit11;
  extern Cards1 diamonds1[];
  RankSet *DIAMONDS_START = suit1;
  RankSet *SPADES_END  = SPADES_START + 0;
  RankSet *SYM_START = SPADES_START +0;
  RankSet *HEARTS_END  = HEARTS_START + 77;
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
      factor = spades < SYM_START ? 48 : 24;
      goto compute;
    }
    if (hearts < HEARTS_END) {
      hearts++;
      diamonds = DIAMONDS_START;
      factor = spades < SYM_START ? 48 : 24;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      diamonds = DIAMONDS_START;
      hearts= HEARTS_START;
      factor = spades < SYM_START ? 48 : 24;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds;
  }

  printf("13-11-1-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
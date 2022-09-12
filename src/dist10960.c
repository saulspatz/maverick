#include <stdio.h>
#include "types.h"

void dist10960() {
  extern RankSet ranks10[];
  extern RankSet suit9[];
  extern Cards10 swords10[];
  extern Cards9 hearts9[];
  extern RankSet suit6[];
  RankSet *SPADES_START = ranks10;
  RankSet *HEARTS_START = suit9;
  extern Cards6 diamonds6[];
  RankSet *DIAMONDS_START = suit6;
  RankSet *SPADES_END  = SPADES_START + 145;
  RankSet *SYM_START = SPADES_START +140;
  RankSet *HEARTS_END  = HEARTS_START + 714;
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

  printf("10-9-6-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
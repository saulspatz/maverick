#include <stdio.h>
#include "types.h"

void dist11860() {
  extern RankSet ranks11[];
  extern RankSet suit8[];
  extern Cards11 swords11[];
  extern Cards8 hearts8[];
  extern RankSet suit6[];
  RankSet *SPADES_START = ranks11;
  RankSet *HEARTS_START = suit8;
  extern Cards6 diamonds6[];
  RankSet *DIAMONDS_START = suit6;
  RankSet *SPADES_END  = SPADES_START + 42;
  RankSet *SYM_START = SPADES_START +36;
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

  printf("11-8-6-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
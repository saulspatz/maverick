#include <stdio.h>
#include "types.h"

void dist111040() {
  extern RankSet ranks11[];
  extern RankSet suit10[];
  extern Cards11 swords11[];
  extern Cards10 hearts10[];
  extern RankSet suit4[];
  RankSet *SPADES_START = ranks11;
  RankSet *HEARTS_START = suit10;
  extern Cards4 diamonds4[];
  RankSet *DIAMONDS_START = suit4;
  RankSet *SPADES_END  = SPADES_START + 41;
  RankSet *SYM_START = SPADES_START +36;
  RankSet *HEARTS_END  = HEARTS_START + 285;
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

  printf("11-10-4-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
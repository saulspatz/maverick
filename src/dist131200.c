#include <stdio.h>
#include "types.h"

void dist131200() {
  extern RankSet ranks13[];
  extern RankSet suit12[];
  extern Cards13 swords13[];
  extern Cards12 hearts12[];
  RankSet *SPADES_START = ranks13;
  RankSet *HEARTS_START = suit12;
  RankSet *SPADES_END  = SPADES_START + 1;
  RankSet *SYM_START = SPADES_START +0;
  RankSet *HEARTS_END  = HEARTS_START + 12;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START-1;
  int factor;
  long total = 0L;
  RankSet Phony = 0;
  while(1) {
    if (hearts < HEARTS_END) {
      hearts++;
      factor = spades < SYM_START ? 24 : 12;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      hearts = HEARTS_START;
      factor = spades < SYM_START ? 24 : 12;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts;
  }

  printf("13-12-0-0: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
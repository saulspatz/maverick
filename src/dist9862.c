#include <stdio.h>
#include "types.h"

void dist9862() {
  extern RankSet ranks9[];
  extern RankSet suit8[];
  extern Cards9 swords9[];
  extern Cards8 hearts8[];
  extern RankSet suit6[];
  extern RankSet suit2[];
  RankSet *SPADES_START = ranks9;
  RankSet *HEARTS_START = suit8;
  extern Cards6 diamonds6[];
  RankSet *DIAMONDS_START = suit6;
  extern Cards2 clubs2[];
  RankSet *CLUBS_START = suit2;
  RankSet *SPADES_END  = SPADES_START + 365;
  RankSet *SYM_START = SPADES_START +350;
  RankSet *HEARTS_END  = HEARTS_START + 1286;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 1715;
  RankSet *CLUBS_END  = CLUBS_START + 77;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  long total = 0L;
  RankSet Phony = 0;
  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      factor = spades < SYM_START ? 48 : 24;
      goto compute;
    }
    if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = spades < SYM_START ? 48 : 24;
      goto compute;
    }
    if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = spades < SYM_START ? 48 : 24;
      goto compute;
    };
    if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = spades < SYM_START ? 48 : 24;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds & *clubs;
  }

  printf("9-8-6-2: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
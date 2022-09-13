#include <stdio.h>
#include "types.h"

void dist10843() {
  extern RankSet ranks10[];
  extern RankSet suit8[];
  extern Cards10 swords10[];
  extern Cards8 hearts8[];
  extern RankSet suit4[];
  extern RankSet suit3[];
  RankSet *SPADES_START = ranks10;
  RankSet *HEARTS_START = suit8;
  extern Cards4 diamonds4[];
  RankSet *DIAMONDS_START = suit4;
  extern Cards3 clubs3[];
  RankSet *CLUBS_START = suit3;
  RankSet *SPADES_END  = SPADES_START + 145;
  RankSet *SYM_START = SPADES_START +140;
  RankSet *HEARTS_END  = HEARTS_START + 1286;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 714;
  RankSet *CLUBS_END  = CLUBS_START + 285;
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

  printf("10-8-4-3: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
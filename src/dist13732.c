#include <stdio.h>
#include "types.h"

void dist13732() {
  extern RankSet ranks13[];
  extern RankSet suit7[];
  extern Cards13 swords13[];
  extern Cards7 hearts7[];
  extern RankSet suit3[];
  extern RankSet suit2[];
  RankSet *SPADES_START = ranks13;
  RankSet *HEARTS_START = suit7;
  extern Cards3 diamonds3[];
  RankSet *DIAMONDS_START = suit3;
  extern Cards2 clubs2[];
  RankSet *CLUBS_START = suit2;
  RankSet *SPADES_END  = SPADES_START + 0;
  RankSet *SYM_START = SPADES_START +0;
  RankSet *HEARTS_END  = HEARTS_START + 1715;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 285;
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

  printf("13-7-3-2: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
#include <stdio.h>
#include "types.h"

void dist121021() {
  extern RankSet ranks12[];
  extern RankSet suit10[];
  extern Cards12 swords12[];
  extern Cards10 hearts10[];
  extern RankSet suit2[];
  extern RankSet suit1[];
  RankSet *SPADES_START = ranks12;
  RankSet *HEARTS_START = suit10;
  extern Cards2 diamonds2[];
  RankSet *DIAMONDS_START = suit2;
  extern Cards1 clubs1[];
  RankSet *CLUBS_START = suit1;
  RankSet *SPADES_END  = SPADES_START + 6;
  RankSet *SYM_START = SPADES_START +6;
  RankSet *HEARTS_END  = HEARTS_START + 285;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 77;
  RankSet *CLUBS_END  = CLUBS_START + 12;
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

  printf("12-10-2-1: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
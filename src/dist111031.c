#include <stdio.h>
#include "types.h"

void dist111031() {
  extern RankSet ranks11[];
  extern RankSet suit10[];
  extern Cards11 swords11[];
  extern Cards10 hearts10[];
  extern RankSet suit3[];
  extern RankSet suit1[];
  RankSet *SPADES_START = ranks11;
  RankSet *HEARTS_START = suit10;
  extern Cards3 diamonds3[];
  RankSet *DIAMONDS_START = suit3;
  extern Cards1 clubs1[];
  RankSet *CLUBS_START = suit1;
  RankSet *SPADES_END  = SPADES_START + 41;
  RankSet *SYM_START = SPADES_START +36;
  RankSet *HEARTS_END  = HEARTS_START + 285;
  RankSet *DIAMONDS_END  = DIAMONDS_START + 285;
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

  printf("11-10-3-1: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
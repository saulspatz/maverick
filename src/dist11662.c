#include <stdio.h>
#include "types.h"

void dist11662() {
  extern RankSet suit11[];
  extern RankSet suit6[];
  extern Cards11 spades11[];
  extern Cards6 hearts6[];
  extern RankSet suit2[];
  RankSet *SPADES_START = suit11;
  RankSet *HEARTS_START = suit6;
  extern Cards6 diamonds6[];
  RankSet *DIAMONDS_START = suit6;
  extern Cards2 clubs2[];
  RankSet *CLUBS_START = suit2;
  RankSet *SPADES_END  = SPADES_START + 77;
  RankSet *HEARTS_END  = HEARTS_START + 1715;
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
      factor = (diamonds==hearts) ? 12 : 24;
      goto compute;
    }
    if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      goto compute;
    }
    if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = 12;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds & *clubs;
  }

  printf("11-6-6-2: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
#include <stdio.h>
#include "types.h"

void dist11554() {
  extern RankSet suit11[];
  extern RankSet suit5[];
  extern Cards11 spades11[];
  extern Cards5 hearts5[];
  extern RankSet suit4[];
  RankSet *SPADES_START = suit11;
  RankSet *HEARTS_START = suit5;
  extern Cards5 diamonds5[];
  RankSet *DIAMONDS_START = suit5;
  extern Cards4 clubs4[];
  RankSet *CLUBS_START = suit4;
  RankSet *SPADES_END  = SPADES_START + 77;
  RankSet *HEARTS_END  = HEARTS_START + 1286;
  RankSet *CLUBS_END  = CLUBS_START + 714;
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

  printf("11-5-5-4: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
#include <stdio.h>
#include "types.h"

void dist7666() {
  extern RankSet suit7[];
  extern RankSet suit6[];
  RankSet *SPADES_START = suit7;
  RankSet *HEARTS_START = suit6;
  RankSet *DIAMONDS_START = suit6;
  RankSet *CLUBS_START = suit6;
  RankSet *SPADES_END  = SPADES_START + 1715;
  RankSet *HEARTS_END  = HEARTS_START + 1715;
  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  long total = 0L;
  RankSet Phony = 0;
  while(1) {
    if (clubs < diamonds) {
      clubs++;
      if (hearts==clubs) factor = 4;
      else if (clubs==diamonds) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      goto compute;
    }
    if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts == diamonds) ? 12 : 24;
      goto compute;
    }
    if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = 12;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = 4;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds & *clubs;
  }

  printf("7-6-6-6: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
#include <stdio.h>
#include "types.h"

void dist10555() {
  extern RankSet suit10[];
  extern RankSet suit5[];
  RankSet *SPADES_START = suit10;
  RankSet *HEARTS_START = suit5;
  RankSet *DIAMONDS_START = suit5;
  RankSet *CLUBS_START = suit5;
  RankSet *SPADES_END  = SPADES_START + 285;
   RankSet *HEARTS_END  = HEARTS_START + 1286;
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

  printf("10-5-5-5: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
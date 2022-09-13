#include <stdio.h>
#include "types.h"

void dist7774() {
  extern RankSet suit7[];
  extern RankSet suit7[];
  extern RankSet suit4[];
  RankSet *SPADES_START = suit7;
  RankSet *HEARTS_START = suit7;
  RankSet *DIAMONDS_START = suit7;
  RankSet *CLUBS_START = suit4;
  RankSet *SPADES_END  = SPADES_START + 1715;
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
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      goto compute;
    }
    if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      goto compute;
    }
    if (hearts < spades) {
      hearts++;
      diamonds = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = (hearts == spades) ? 12 : 24;
      goto compute;
    }
    if (spades < SPADES_END) {
      spades++;
      hearts = HEARTS_START;
      diamonds  = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = 12;
    } else break;

compute:

    total += factor;
    Phony |= *spades & *hearts & *diamonds & *clubs;
  }

  printf("7-7-7-4: %ld\n", total);
  fprintf(stderr, "%d", Phony);
}
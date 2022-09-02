#include <stdio.h>
#include "types.h"
extern Spades9 spades9[];
extern Hearts7 hearts7[];
extern Diamonds6 diamonds6[];
extern Clubs3 clubs3[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist9763() {
  int factor;
  long total = 0L;
  int END_SPADES  = 714;
  int END_HEARTS  = 1715;
  int END_DIAMONDS  = 1715;
  int END_CLUBS  = 285;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < END_CLUBS) {
      index[CLUBS]++;
      factor = 24;
      goto compute;
    }
    if (index[DIAMONDS] < END_DIAMONDS) {
      index[DIAMONDS]++;
      index[CLUBS] = 0;
      factor = 24;
      goto compute;
    }
    if (index[HEARTS] < END_HEARTS) {
      index[HEARTS]++;
      index[CLUBS] = index[DIAMONDS] = 0;
      factor = 24;
      goto compute;
    };
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;
      factor = 24;
    } else break;

compute:

    total += factor;
  }

  printf("9-7-6-3: %ld\n", total);
}
#include <stdio.h>
#include "types.h"
extern Spades9 spades9[];
extern Hearts7 hearts7[];
extern Diamonds7 diamonds7[];
extern Clubs2 clubs2[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist9772() {
  int factor;
  long total = 0L;
  int END_SPADES  = 714;
  int END_HEARTS  = 1715;
  int END_CLUBS  = 77;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < END_CLUBS) {
      index[CLUBS]++;
      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;
      goto compute;
    }
    if (index[DIAMONDS] < index[HEARTS]) {
      index[DIAMONDS]++;
      index[CLUBS] = 0;
      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;
      goto compute;
    }
    if (index[HEARTS] < END_HEARTS) {
      index[HEARTS]++;
      index[CLUBS] = index[DIAMONDS] = 0;
      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;
      goto compute;
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;
      factor = 12;
    } else break;

compute:

    total += factor;
  }

  printf("9-7-7-2: %ld\n", total);
}
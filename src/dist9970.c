#include <stdio.h>
#include "types.h"
extern Spades9 spades9[];
extern Hearts9 hearts9[];
extern Diamonds7 diamonds7[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist9970() {
  int factor;
  long total = 0L;
  int END_SPADES  = 714;
  int END_DIAMONDS  = 1715;
  int index[4];
  index[DIAMONDS]=-1;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[DIAMONDS] < END_DIAMONDS) {
      index[DIAMONDS]++;
      factor = (index[HEARTS] == index[SPADES]) ? 12 : 24;
      goto compute;
    }
    if (index[HEARTS] < index[SPADES]) {
      index[HEARTS]++;
      index[DIAMONDS] = 0;
      factor = (index[HEARTS] == index[SPADES]) ? 12 : 24;
      goto compute;
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[DIAMONDS] = index[HEARTS] = 0;
      factor = 24;
    } else break;

compute:

    total += factor;
  }

  printf("9-9-7-0: %ld\n", total);
}
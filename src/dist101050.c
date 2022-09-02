#include <stdio.h>
#include "types.h"
extern Spades10 spades10[];
extern Hearts10 hearts10[];
extern Diamonds5 diamonds5[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist101050() {
  int factor;
  long total = 0L;
  int END_SPADES  = 285;
  int END_DIAMONDS  = 1286;
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

  printf("10-10-5-0: %ld\n", total);
}
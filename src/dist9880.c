#include <stdio.h>
#include "types.h"
extern Spades9 spades9[];
extern Hearts8 hearts8[];
extern Diamonds8 diamonds8[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist9880() {
  int factor;
  long total = 0L;
  int END_SPADES  = 714;
  int END_HEARTS  = 1286;
  int index[4];
  index[DIAMONDS]=-1;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[DIAMONDS] < index[HEARTS]) {
      index[DIAMONDS]++;
      factor = (index[DIAMONDS] == index[HEARTS]) ? 12 : 24;
      goto compute;
    }
    if (index[HEARTS] < END_HEARTS) {
      index[HEARTS]++;
      index[DIAMONDS] = 0;
      factor = 24;
      goto compute;
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[DIAMONDS] =index[HEARTS] = 0;
      factor = 12;
    } else break;

compute:

    total += factor;
  }

  printf("9-8-8-0: %ld\n", total);
}
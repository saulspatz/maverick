#include <stdio.h>
#include "types.h"
extern Spades13 spades13[];
extern Hearts10 hearts10[];
extern Diamonds2 diamonds2[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist131020() {
  int factor;
  long total = 0L;
  int END_SPADES  = 0;
  int END_HEARTS  = 285;
  int END_DIAMONDS  = 77;
  int index[4];
  index[DIAMONDS]=-1;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
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
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[CLUBS] = index[DIAMONDS] = index[HEARTS]= 0;
      factor = 24;
    } else break;

compute:

    total += factor;
  }

  printf("13-10-2-0: %ld\n", total);
}
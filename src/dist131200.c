#include <stdio.h>
#include "types.h"
extern Spades13 spades13[];
extern Hearts12 hearts12[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist131200() {
  int factor;
  long total = 0L;
  int END_SPADES  = 0;
  int END_HEARTS  = 12;
  int index[4];
  index[HEARTS]=-1;
  index[SPADES]=0;
  while(1) {
    if (index[HEARTS] < END_HEARTS) {
      index[HEARTS]++;
      factor = 12;
      goto compute;
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[HEARTS] = 0;
      factor = 12;
    } else break;

compute:

    total += factor;
  }

  printf("13-12-0-0: %ld\n", total);
}
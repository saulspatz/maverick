#include <stdio.h>
#include "types.h"
extern Spades12 spades12[];
extern Hearts10 hearts10[];
extern Diamonds3 diamonds3[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist121030() {
  int factor;
  long total = 0L;
  int END_SPADES  = 12;
  int END_HEARTS  = 285;
  int END_DIAMONDS  = 285;
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

  printf("12-10-3-0: %ld\n", total);
}
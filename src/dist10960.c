#include <stdio.h>
#include "types.h"
extern Spades10 spades10[];
extern Hearts9 hearts9[];
extern Diamonds6 diamonds6[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist10960() {
  int factor;
  long total = 0L;
  int END_SPADES  = 285;
  int END_HEARTS  = 714;
  int END_DIAMONDS  = 1715;
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

  printf("10-9-6-0: %ld\n", total);
}
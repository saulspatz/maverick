#include <stdio.h>
#include "types.h"
extern Spades13 spades13[];
extern Hearts11 hearts11[];
extern Diamonds1 diamonds1[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist131110() {
  int factor;
  long total = 0L;
  int END_SPADES  = 0;
  int END_HEARTS  = 77;
  int END_DIAMONDS  = 12;
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

  printf("13-11-1-0: %ld\n", total);
}
#include <stdio.h>
#include "types.h"
extern Spades11 spades11[];
extern Hearts11 hearts11[];
extern Diamonds3 diamonds3[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist111130() {
  int factor;
  long total = 0L;
  int END_SPADES  = 77;
  int END_DIAMONDS  = 285;
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

  printf("11-11-3-0: %ld\n", total);
}
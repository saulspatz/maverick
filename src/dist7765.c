#include <stdio.h>
#include "types.h"
extern Spades7 spades7[];
extern Hearts7 hearts7[];
extern Diamonds6 diamonds6[];
extern Clubs5 clubs5[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist7765() {
  int factor;
  long total = 0L;
  int END_SPADES  = 1715;
  int END_DIAMONDS  = 1715;
  int END_CLUBS  = 1286;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < END_CLUBS) {
      index[CLUBS]++;
      factor = (index[HEARTS]==index[SPADES]) ? 12 : 24;
      goto compute;
    }
    if (index[DIAMONDS] < END_DIAMONDS) {
      index[DIAMONDS]++;
      index[CLUBS] = 0;
      factor = (index[HEARTS]==index[SPADES]) ? 12 : 24;
      goto compute;
    }
    if (index[HEARTS] < index[SPADES]) {
      index[HEARTS]++;
      index[CLUBS] = index[DIAMONDS] = 0;
      factor = (index[HEARTS]==index[SPADES]) ? 12 : 24;
      goto compute;
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;
      factor = 24;
    } else break;

compute:

    total += factor;
  }

  printf("7-7-6-5: %ld\n", total);
}
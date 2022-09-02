#include <stdio.h>
#include "types.h"
extern Spades10 spades10[];
extern Hearts6 hearts6[];
extern Diamonds6 diamonds6[];
extern Clubs3 clubs3[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist10663() {
  int factor;
  long total = 0L;
  int END_SPADES  = 285;
  int END_HEARTS  = 1715;
  int END_CLUBS  = 285;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < END_CLUBS) {
      index[CLUBS]++;
      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;
      goto compute;
    }
    if (index[DIAMONDS] < index[HEARTS]) {
      index[DIAMONDS]++;
      index[CLUBS] = 0;
      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;
      goto compute;
    }
    if (index[HEARTS] < END_HEARTS) {
      index[HEARTS]++;
      index[CLUBS] = index[DIAMONDS] = 0;
      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;
      goto compute;
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;
      factor = 12;
    } else break;

compute:

    total += factor;
  }

  printf("10-6-6-3: %ld\n", total);
}
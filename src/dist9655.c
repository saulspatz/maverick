#include <stdio.h>
#include "types.h"
extern Spades9 spades9[];
extern Hearts6 hearts6[];
extern Diamonds5 diamonds5[];
extern Clubs5 clubs5[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist9655() {
  int factor;
  long total = 0L;
  int END_SPADES  = 714;
  int END_HEARTS  = 1715;
  int END_DIAMONDS  = 1286;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < index[DIAMONDS]) {
      index[CLUBS]++;
      factor = (index[CLUBS]==index[DIAMONDS]) ? 12 : 24;
      goto compute;
    }
    if (index[DIAMONDS] < END_DIAMONDS) {
      index[DIAMONDS]++;
      index[CLUBS] = 0;
      factor = 24;
      goto compute;
    }
    if (index[HEARTS] < END_HEARTS) {
      index[HEARTS]++;
      index[CLUBS] = index[DIAMONDS] = 0;
      factor = 12;
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

  printf("9-6-5-5: %ld\n", total);
}
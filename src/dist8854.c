#include <stdio.h>
#include "types.h"
extern Spades8 spades8[];
extern Hearts8 hearts8[];
extern Diamonds5 diamonds5[];
extern Clubs4 clubs4[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist8854() {
  int factor;
  long total = 0L;
  int END_SPADES  = 1286;
  int END_DIAMONDS  = 1286;
  int END_CLUBS  = 714;
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

  printf("8-8-5-4: %ld\n", total);
}
#include <stdio.h>
#include "types.h"
extern Spades10 spades10[];
extern Hearts8 hearts8[];
extern Diamonds4 diamonds4[];
extern Clubs3 clubs3[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist10843() {
  int factor;
  long total = 0L;
  int END_SPADES  = 285;
  int END_HEARTS  = 1286;
  int END_DIAMONDS  = 714;
  int END_CLUBS  = 285;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < END_CLUBS) {
      index[CLUBS]++;
      factor = 24;
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
      factor = 24;
      goto compute;
    };
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;
      factor = 24;
    } else break;

compute:

    total += factor;
  }

  printf("10-8-4-3: %ld\n", total);
}
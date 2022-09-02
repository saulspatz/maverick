#include <stdio.h>
#include "types.h"
extern Spades11 spades11[];
extern Hearts7 hearts7[];
extern Diamonds5 diamonds5[];
extern Clubs2 clubs2[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist11752() {
  int factor;
  long total = 0L;
  int END_SPADES  = 77;
  int END_HEARTS  = 1715;
  int END_DIAMONDS  = 1286;
  int END_CLUBS  = 77;
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

  printf("11-7-5-2: %ld\n", total);
}
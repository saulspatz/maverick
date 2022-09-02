#include <stdio.h>
#include "types.h"
extern Spades13 spades13[];
extern Hearts5 hearts5[];
extern Diamonds4 diamonds4[];
extern Clubs3 clubs3[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist13543() {
  int factor;
  long total = 0L;
  int END_SPADES  = 0;
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

  printf("13-5-4-3: %ld\n", total);
}
#include <stdio.h>
#include "types.h"
extern Spades8 spades8[];
extern Hearts8 hearts8[];
extern Diamonds8 diamonds8[];
extern Clubs1 clubs1[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist8881() {
  int factor;
  long total = 0L;
  int END_SPADES  = 1286;
  int END_CLUBS  = 12;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < END_CLUBS) {
      index[CLUBS]++;
      if (index[SPADES]==index[DIAMONDS]) factor = 4;
      else if (index[SPADES]==index[HEARTS]) factor = 12;
      else if (index[HEARTS]==index[DIAMONDS]) factor = 12;
      else factor = 24;
      goto compute;
    }
    if (index[DIAMONDS] < index[HEARTS]) {
      index[DIAMONDS]++;
      index[CLUBS] = 0;
      if (index[SPADES]==index[DIAMONDS]) factor = 4;
      else if (index[SPADES]==index[HEARTS]) factor = 12;
      else if (index[HEARTS]==index[DIAMONDS]) factor = 12;
      else factor = 24;
      goto compute;
    }
    if (index[HEARTS] < index[SPADES]) {
      index[HEARTS]++;
      index[DIAMONDS] = index[CLUBS] = 0;
      factor = (index[HEARTS] == index[SPADES]) ? 12 : 24;
      goto compute;
    }
    if (index[SPADES] < END_SPADES) {
      index[SPADES]++;
      index[HEARTS] = index[DIAMONDS]  = index[CLUBS] = 0;
      factor = 12;
    } else break;

compute:

    total += factor;
  }

  printf("8-8-8-1: %ld\n", total);
}
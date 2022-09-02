#include <stdio.h>
#include "types.h"
extern Spades7 spades7[];
extern Hearts6 hearts6[];
extern Diamonds6 diamonds6[];
extern Clubs6 clubs6[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist7666() {
  int factor;
  long total = 0L;
  int END_SPADES  = 1715;
  int END_HEARTS  = 1715;
  int index[4];
  index[CLUBS]=-1;
  index[DIAMONDS]=0;
  index[HEARTS]=0;
  index[SPADES]=0;
  while(1) {
    if (index[CLUBS] < index[DIAMONDS]) {
      index[CLUBS]++;
      if (index[HEARTS]==index[CLUBS]) factor = 4;
      else if (index[CLUBS]==index[DIAMONDS]) factor = 12;
      else if (index[HEARTS]==index[DIAMONDS]) factor = 12;
      else factor = 24;
      goto compute;
    }
    if (index[DIAMONDS] < index[HEARTS]) {
      index[DIAMONDS]++;
      index[CLUBS] = 0;
      factor = (index[HEARTS] == index[DIAMONDS]) ? 12 : 24;
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
      index[CLUBS] = index[DIAMONDS] =index[HEARTS] = 0;
      factor = 4;
    } else break;

compute:

    total += factor;
  }

  printf("7-6-6-6: %ld\n", total);
}
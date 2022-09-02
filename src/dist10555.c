#include <stdio.h>
#include "types.h"
extern Spades10 spades10[];
extern Hearts5 hearts5[];
extern Diamonds5 diamonds5[];
extern Clubs5 clubs5[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist10555() {
  int factor;
  long total = 0L;
  int END_SPADES  = 285;
  int END_HEARTS  = 1286;
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

  printf("10-5-5-5: %ld\n", total);
}
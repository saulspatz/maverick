#include <stdio.h>
#include "types.h"
extern Spades13 spades13[];
extern Hearts4 hearts4[];
extern Diamonds4 diamonds4[];
extern Clubs4 clubs4[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist13444() {
  int factor;
  long total = 0L;
  int END_SPADES  = 0;
  int END_HEARTS  = 714;
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

  printf("13-4-4-4: %ld\n", total);
}
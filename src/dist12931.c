#include <stdio.h>
#include "types.h"
extern Spades12 spades12[];
extern Hearts9 hearts9[];
extern Diamonds3 diamonds3[];
extern Clubs1 clubs1[];
enum {SPADES, HEARTS, DIAMONDS, CLUBS};

void dist12931() {
  int factor;
  long total = 0L;
  int END_SPADES  = 12;
  int END_HEARTS  = 714;
  int END_DIAMONDS  = 285;
  int END_CLUBS  = 12;
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

  printf("12-9-3-1: %ld\n", total);
}
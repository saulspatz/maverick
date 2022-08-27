#include <stdio.h>
#include "../include/spades13.h"
#include "../include/hearts4.h"
#include "../include/diamonds4.h"
#include "../include/clubs4.h"

int main() {
  int index[4];
  index[0] = 0;
  index[1] = 0;
  index[2] = 0;
  index[3] = 0;
  long total = 4L;
  while(1) {
    if (index[3] < index[2]) {
      index[3]++;
      if (index[1]==index[3]) total += 4;
      else if (index[3]==index[2]) total += 12;
      else if (index[1]==index[2]) total += 12;
      else total += 24;
      continue;
    }
    if (index[2] < index[1]) {
      index[2]++;
      index[3] = 0;
      total += (index[1] == index[2]) ? 12 : 24;
      continue;
    }
    if (index[1] < END1) {
      index[1]++;
      index[3] = index[2] = 0;
      total += 12;
      continue;
    }
    if (index[0] < END0) {
      index[0]++;
      index[3] = index[2] =index[1] = 0;
      total += 4;
      continue;
    } else break;
  }

  printf("%ld\n", total);
  return 0;
}
#include <stdio.h>
#include "../include/spades13.h"
#include "../include/hearts8.h"
#include "../include/diamonds3.h"
#include "../include/clubs1.h"

int main() {
  int index[4];
  index[0] = 0;
  index[1] = 0;
  index[2] = 0;
  index[3] = 0;
  long total = 24L;
  while(1) {
    if (index[3] < END3) {
      index[3]++;
      total += 24;
      continue;
    }
    if (index[2] < END2) {
      index[2]++;
      index[3] = 0;
      total += 24;
      continue;
    }
    if (index[1] < END1) {
      index[1]++;
      index[3] = index[2] = 0;
      total += 24;
      continue;
    };
    if (index[0] < END0) {
      index[0]++;
      index[3] = index[2] = index[1] = 0;
      total += 24;
      continue;
    } else break;
  }

  printf("%ld\n", total);
  return 0;
}
#include <stdio.h>

int main() {
  int index[4];
  index[0] = 0;
  index[1] = 0;
  index[2] = -1;

  int factor;
  long total = 0L;
  int END0  = 0;
  int END1  = 1715;
  while(1) {
    if (index[2] < index[1]) {
      index[2]++;
      factor = (index[2] == index[1]) ? 12 : 24;
      goto compute;
    }
    if (index[1] < END1) {
      index[1]++;
      index[2] = 0;
      factor = 24;
      goto compute;
    }
    if (index[0] < END0) {
      index[0]++;
      index[2] =index[1] = 0;
      factor = 12;
    } else break;

compute:

    total += factor;
  }

  printf("13-6-6: %ld\n", total);
}
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

void dist_10_7_7_1() {
  extern RankSet suit7[];
  RankSet *HEARTS_START = suit7;
  RankSet *HEARTS_END = HEARTS_START + 1715;

  extern RankSet suit7[];
  RankSet *DIAMONDS_START = suit7;
  extern RankSet ranks10[];
  RankSet *SPADES_START = ranks10;
  RankSet *SPADES_END = SPADES_START + 145;
  RankSet *SYM_START = SPADES_START + 140;

  extern RankSet suit1[];
  RankSet *CLUBS_START = suit1;
  RankSet *CLUBS_END = CLUBS_START + 12;

  RankSet *spades = SPADES_START;
  RankSet *hearts = HEARTS_START;
  RankSet *diamonds = DIAMONDS_START;
  RankSet *clubs = CLUBS_START-1;
  int factor;
  unsigned long exhaustC = 0L;
  unsigned long heurC = 0L;
  unsigned long skipC = 0L;
  unsigned long exhaustD = 0L;
  unsigned long heurD = 0L;
  unsigned long skipD = 0L;
  unsigned long solutions = 0L;
  double begin, end;
  begin = clock();
  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (hearts < HEARTS_END) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (diamonds==hearts) ? 12 : 24;
      if (spades < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = (spades < SYM_START) ? 24 : 12;
    }
    else break;
    int result = solver(*spades, *hearts, *diamonds, *clubs);
    exhaustC += 1;
    exhaustD += factor;
    if (result == 1)      solutions += factor;
  }
  end = clock();
  double time = (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts.log", "a");
  setlocale(LC_ALL, "");
  fprintf(out, "%-9s %'18lu %'18lu %'18lu %'18lu %'18lu %'18lu %'18lu\n",
      "10-7-7-1", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions);
   fprintf(stderr, "%.2f", time);
  fclose(out);
}
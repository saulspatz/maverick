#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);

void dist_9_9_5_2() {
  extern RankSet suit9[];
  RankSet *SPADES_START = suit9;
  RankSet *SPADES_END = SPADES_START + 714;

  extern RankSet suit9[];
  RankSet *HEARTS_START = suit9;
  extern RankSet ranks5[];
  RankSet *DIAMONDS_START = ranks5;
  RankSet *DIAMONDS_END = DIAMONDS_START + 650;
  RankSet *SYM_START = DIAMONDS_START + 636;

  extern RankSet suit2[];
  RankSet *CLUBS_START = suit2;
  RankSet *CLUBS_END = CLUBS_START + 77;

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
  while (1) {
    if (clubs < CLUBS_END) {
      clubs++;
      factor = (hearts==spades) ? 12 : 24;
      if (diamonds < SYM_START) factor *= 2;
    }
    else if (diamonds < DIAMONDS_END) {
      diamonds++;
      clubs = CLUBS_START;
      factor = (hearts==spades) ? 12 : 24;
      if (diamonds < SYM_START) factor *= 2;
    }
    else if (hearts < spades) {
      hearts++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      factor = (hearts==spades) ? 12 : 24;
      if (diamonds < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      clubs = CLUBS_START;
      diamonds = DIAMONDS_START;
      hearts = HEARTS_START;
      factor = (diamonds < SYM_START) ? 48 : 24;
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
      "9-9-5-2", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions);
   fprintf(stderr, "%.2f", time);
  fclose(out);
}
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "types.h"

extern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);
int backup = 0;
void sig_handler(int signum){
  backup = 1;
  alarm(3600);  // Schedule a new alarm after an hour
}

void dist_8_8_8_1() {
  extern RankSet suit8[];
  RankSet *SPADES_START = suit8;
  RankSet *SPADES_END = SPADES_START + 1286;

  extern RankSet suit8[];
  RankSet *HEARTS_START = suit8;
  extern RankSet suit8[];
  RankSet *DIAMONDS_START = suit8;
  extern RankSet ranks1[];
  RankSet *CLUBS_START = ranks1;
  RankSet *CLUBS_END = CLUBS_START + 6;
  RankSet *SYM_START = CLUBS_START + 6;
  RankSet *spades;
  RankSet *hearts;
  RankSet *diamonds;
  RankSet *clubs;


  int factor;
  unsigned long exhaustC;  // classes
  unsigned long heurC;
  unsigned long skipC;
  unsigned long exhaustD;   // deals
  unsigned long heurD;
  unsigned long skipD;
  unsigned long solutions;
  double begin, end, elapsed;

  // check whether to continue an interrupted run
  FILE *saved = NULL;
  if (access("dist_8_8_8_1.sav1", F_OK))
    saved = fopen("dist_8_8_8_1.sav1", "r");
  else if (access("dist_8_8_8_1.sav2", F_OK))
    saved = fopen("dist_8_8_8_1.sav2", "r");
  if (saved) {
    unsigned long cc, dd, hh, ss;
    fscanf(saved, "%lu, %lu, %lu, %lu", &cc, &dd, &hh, &ss);
    fscanf(saved, "%lu %lu %lu %lu %lu %lu %lu %lf", 
                  &exhaustC, &heurC, &skipC, 
                  &exhaustD, &heurD, &skipD, 
                  &solutions, &elapsed);
    clubs = CLUBS_START + cc;
    diamonds = DIAMONDS_START + dd;
    hearts = HEARTS_START + hh;
    spades = SPADES_START + ss;
    if (spades >= SPADES_END)
      return;      //calculation already completed      
  }  
  else {         // initial run
    spades = SPADES_START;
    hearts = HEARTS_START;
    diamonds = DIAMONDS_START;
    clubs = CLUBS_START-1;
    exhaustC = 0L;
    exhaustD = 0L;
    heurC = 0L;
    heurD = 0L;
    skipC = 0L;
    skipD = 0L;
    solutions = 0L;
    elapsed = 0;
  }   
  signal(SIGALRM,sig_handler); // Register signal handler
  alarm(3600);                 // schedule a backup in an hour
  begin = clock();
  while(1) {
    if (clubs < CLUBS_END) {
      clubs++;
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (diamonds < hearts) {
      diamonds++;
      clubs = CLUBS_START;
      if (spades==diamonds) factor = 4;
      else if (spades==hearts) factor = 12;
      else if (hearts==diamonds) factor = 12;
      else factor = 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (hearts < spades) {
      hearts++;
      diamonds = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = (hearts == spades) ? 12 : 24;
      if (clubs < SYM_START) factor *= 2;
    }
    else if (spades < SPADES_END) {
      spades++;
      hearts = HEARTS_START;
      diamonds  = DIAMONDS_START;
      clubs = CLUBS_START;
      factor = (clubs < SYM_START) ? 24 : 12;
    }
    else break;
    int result = solver(*spades, *hearts, *diamonds, *clubs);
    exhaustC += 1;
    exhaustD += factor;
    if (result == 1) solutions += factor;
    if (backup) {
        backup = 0;
        end = clock();
        elapsed += (end-begin)/CLOCKS_PER_SEC;
        if (access("dist_8_8__1.sav2",  F_OK))  // 2nd generation backup exists
          unlink("dist_8_8_8_1.sav2");
        if (access("dist_8_8__1.sav1", F_OK))  // 1st generation backup exists
          rename("dist_8_8_8_1.sav1", "dist_8_8_8_1.sav2");
        FILE *back = fopen("dist_8-8-8_1.sav1", "w'");
        fprintf(back, "%lu %lu %lu %lu\n",clubs-CLUBS_START, 
                 diamonds-DIAMONDS_START, hearts-HEARTS_START,spades-SPADES_START);
        fprintf(back, "%lu %lu %lu %lu %lu %lu %lu %.2f\n", exhaustC, heurC, skipC,
                   exhaustD, heurD, skipD, solutions, elapsed);
        fclose(back);
        begin = clock();
      }
  }
  end = clock();
  double time = elapsed + (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts1.log", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\n",
       "8-8-8-1", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions, time);
  fputs(buffer, out);
  fclose(out);
  // Final backup, showing calculation complete
  FILE *back = fopen("dist_*-*-*_1.sav1", "w'");
  fprintf(back, "%lu %lu %lu %lu\n",clubs-CLUBS_START, 
            diamonds-DIAMONDS_START, hearts-HEARTS_START,spades-SPADES_START);
  fprintf(back, "%lu %lu %lu %lu %lu %lu %lu %.2f\n", exhaustC, heurC, skipC,
              exhaustD, heurD, skipD, solutions, elapsed);
  fclose(back);
}
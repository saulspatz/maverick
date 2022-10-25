#include <string.h>
#include <stdio.h>
#include "straights.h" // all possible straights

int bitcount(RankSet n);

int hasStraight4(RankSet spades, RankSet hearts, RankSet diamonds, RankSet clubs) {
  // Pre: all suits have more than 5 cards
  int bs = bitcount(spades);
  int bh = bitcount(hearts);
  int bd = bitcount(diamonds);
  int bc = bitcount(clubs);

  int reqS = bs - 5;
  int reqH = bh - 5;
  int reqD = bd - 5;
  int reqC = bc - 5;

  RankSet join = spades | hearts | diamonds | clubs;
  for (int m =0; m < 10; ++m) {
    if ((join & straights[m]) != straights[m])
      continue;
    RankSet straight = straights[m];
    RankSet s = spades & straight;
    RankSet h = hearts & straight;
    RankSet d = diamonds & straight;
    RankSet c = clubs & straight;
    if (bs < reqS || bh < reqH || bd < reqD || bc < reqC)
      continue;
    if ( bs == reqS && bh == reqH && (spades & hearts))
      continue;  
    if ( bs == reqS && bd == reqD && (spades & diamonds))
      continue;
    if ( bs == reqS && bc == reqC && (spades & clubs))
      continue;
    if ( bh == reqH && bd == reqD && (hearts & diamonds))
      continue;
    if ( bh == reqH && bc == reqC && (hearts & clubs))
      continue;
    if ( bd == reqD && bc == reqC && (diamonds & clubs))
      continue; 
    int cards[5];
    memset(cards, 0, sizeof(cards)); 
    RankSet st = straight;
    // which ranks of the straight are in each suit?
    for (int j = 0; j < 5; j++)  {  // for each bit 
      RankSet st1 = st & (st-1);   // clear lsb
      RankSet card = st & (~st1);  // isolate the bit
      st = st1;                    // remaining cards
      if (s & card) cards[j] |= 8;
      if (h & card) cards[j] |= 4;
      if (d & card) cards[j] |= 2;
      if (c & card) cards[j] |= 1;
    } 
    int available[5];
    int used[5][4];
    int choice[5];
    memset(used, 0, sizeof(used));
    available[0] = cards[0];
    int k = 0;
    while (k >= 0) {
        while (available[k]) {
          if (1 & available[k]) {
            available[k] &= ~1;
            choice[k] = 0;
          }
          else if (2 & available[k]) {
            available[k] &= ~2;
            choice[k] = 1;
          }
          else if (4 & available[k]) {
            available[k] &= ~4;
            choice[k] = 2;
          }

          else {
            available[k] &= ~8;
            choice[k] = 3;
          }
          
        k++;
        if (k == 5) {
          fprintf(stderr, "%x %x %x %x %x\n", spades,hearts,diamonds,clubs,straight);
          return 1;
        }
        available[k] = cards[k];
        memcpy(&used[k], &used[k-1], sizeof(used[k]));
        used[k][choice[k-1]] += 1;
        if (used[k][0]== reqC)
          available[k] &= ~1;
        if (used[k][1]== reqD)
          available[k] &= ~2;
        if (used[k][2]== reqH)
          available[k] &= ~4;
        if (used[k][3] == reqS)
          available[k] &= ~8;
      }
      k--;
    }
  }
  fprintf(stderr, "%x %x %x %x fail\n", spades, hearts, diamonds, clubs);
  return 0;
}

int hasStraight3(RankSet spades, RankSet hearts, RankSet diamonds) {
  // Pre: all suits have more than 5 cards
  int bs = bitcount(spades);
  int bh = bitcount(hearts);
  int bd = bitcount(diamonds);

  int reqS = bs - 5;
  int reqH = bh - 5;
  int reqD = bd - 5;

  RankSet join = spades | hearts | diamonds;
  for (int m =0; m < 10; ++m) {
    if ((join & straights[m]) != straights[m])
      continue;
    RankSet straight = straights[m];
    RankSet s = spades & straight;
    RankSet h = hearts & straight;
    RankSet d = diamonds & straight;
    if (bs < reqS || bh < reqH || bd < reqD)
      continue;
    if ( bs == reqS && bh == reqH && (spades & hearts))
      continue;  
    if ( bs == reqS && bd == reqD && (spades & diamonds))
      continue;
    if ( bh == reqH && bd == reqD && (hearts & diamonds))
      continue;
    int cards[5];
    memset(cards, 0, sizeof(cards)); 
    RankSet st = straight;
    // which ranks of the straight are in each suit?
    for (int j = 0; j < 5; j++)  {  // for each bit 
      RankSet st1 = st & (st-1);   // clear lsb
      RankSet card = st & (~st1);  // isolate the bit
      st = st1;                    // remaining cards
      if (s & card) cards[j] |= 4;
      if (h & card) cards[j] |= 2;
      if (d & card) cards[j] |= 1;
    } 
    int available[5];
    int used[5][3];
    int choice[5];
    memset(used, 0, sizeof(used));
    available[0] = cards[0];
    int k = 0;
    while (k >= 0) {
        while (available[k]) {
          if (1 & available[k]) {
            available[k] &= ~1;
            choice[k] = 0;
          }
          else if (2 & available[k]) {
            available[k] &= ~2;
            choice[k] = 1;
          }
          else {
            available[k] &= ~4;
            choice[k] = 2;
          }
          
        k++;
        if (k == 5) {
          fprintf(stderr, "%x %x %x %x\n", spades, hearts, diamonds, straight);
          return 1;
        }
        available[k] = cards[k];
        memcpy(&used[k], &used[k-1], sizeof(used[k]));
        used[k][choice[k-1]] += 1;
        if (used[k][0]== reqD)
          available[k] &= ~1;
        if (used[k][1]== reqH)
          available[k] &= ~2;
        if (used[k][2] == reqS)
          available[k] &= ~4;
      }
      k--;
    }
  }
  fprintf(stderr, "%x %x %x fail\n", spades, hearts, diamonds);
  return 0;
}

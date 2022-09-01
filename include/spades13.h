#ifndef SPADES13_H
#define SPADES13_H
#include "card.h"
typedef struct {
  RankSet ranks;
  Card cards[13];} Spades13;
Spades13 spades13[1] = {
  {16382,{{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
};
#endif

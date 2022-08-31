#ifndef DIAMONDS1_H
#define DIAMONDS1_H
#include "card.h"
typedef struct {
  RankSet ranks;
  Card cards[1];} Diamonds1;
Diamonds1 diamonds1[13] = {
  {2,{{1, 2},}},
  {4,{{2, 2},}},
  {8,{{3, 2},}},
  {16,{{4, 2},}},
  {32,{{5, 2},}},
  {64,{{6, 2},}},
  {128,{{7, 2},}},
  {256,{{8, 2},}},
  {512,{{9, 2},}},
  {1024,{{10, 2},}},
  {2048,{{11, 2},}},
  {4096,{{12, 2},}},
  {8192,{{13, 2},}},
};
#endif
#ifndef HEARTS13_H
#define HEARTS13_H
#include "card.h"
typedef struct {
  RankSet ranks;
  Card cards[13];} Hearts13;
Hearts13 hearts13[1] = {
  {16382,{{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},}},
};
#endif

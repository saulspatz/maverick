#ifndef SPADES11_H
#define SPADES11_H
#include "card.h"
typedef struct {
  RankSet ranks;
  Card cards[11];} Spades11;
Spades11 spades11[78] = {
  {4094,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},}},
  {6142,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{12, 0},}},
  {10238,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{13, 0},}},
  {7166,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{11, 0},{12, 0},}},
  {11262,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{11, 0},{13, 0},}},
  {13310,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{12, 0},{13, 0},}},
  {7678,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{10, 0},{11, 0},{12, 0},}},
  {11774,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{10, 0},{11, 0},{13, 0},}},
  {13822,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{10, 0},{12, 0},{13, 0},}},
  {14846,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{11, 0},{12, 0},{13, 0},}},
  {7934,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12030,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14078,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15102,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15614,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {8062,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12158,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{8, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14206,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{8, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15230,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{8, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15742,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{8, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {15998,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {8126,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12222,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14270,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{7, 0},{8, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15294,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{7, 0},{8, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15806,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{7, 0},{8, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16062,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{7, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16190,{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {8158,{1, 0},{2, 0},{3, 0},{4, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12254,{1, 0},{2, 0},{3, 0},{4, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14302,{1, 0},{2, 0},{3, 0},{4, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15326,{1, 0},{2, 0},{3, 0},{4, 0},{6, 0},{7, 0},{8, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15838,{1, 0},{2, 0},{3, 0},{4, 0},{6, 0},{7, 0},{8, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16094,{1, 0},{2, 0},{3, 0},{4, 0},{6, 0},{7, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16222,{1, 0},{2, 0},{3, 0},{4, 0},{6, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16286,{1, 0},{2, 0},{3, 0},{4, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {8174,{1, 0},{2, 0},{3, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12270,{1, 0},{2, 0},{3, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14318,{1, 0},{2, 0},{3, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15342,{1, 0},{2, 0},{3, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15854,{1, 0},{2, 0},{3, 0},{5, 0},{6, 0},{7, 0},{8, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16110,{1, 0},{2, 0},{3, 0},{5, 0},{6, 0},{7, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16238,{1, 0},{2, 0},{3, 0},{5, 0},{6, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16302,{1, 0},{2, 0},{3, 0},{5, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16334,{1, 0},{2, 0},{3, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {8182,{1, 0},{2, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12278,{1, 0},{2, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14326,{1, 0},{2, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15350,{1, 0},{2, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15862,{1, 0},{2, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16118,{1, 0},{2, 0},{4, 0},{5, 0},{6, 0},{7, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16246,{1, 0},{2, 0},{4, 0},{5, 0},{6, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16310,{1, 0},{2, 0},{4, 0},{5, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16342,{1, 0},{2, 0},{4, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16358,{1, 0},{2, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {8186,{1, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12282,{1, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14330,{1, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15354,{1, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15866,{1, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16122,{1, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16250,{1, 0},{3, 0},{4, 0},{5, 0},{6, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16314,{1, 0},{3, 0},{4, 0},{5, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16346,{1, 0},{3, 0},{4, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16362,{1, 0},{3, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16370,{1, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {8188,{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},}},
  {12284,{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{13, 0},}},
  {14332,{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{12, 0},{13, 0},}},
  {15356,{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{11, 0},{12, 0},{13, 0},}},
  {15868,{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16124,{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16252,{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16316,{2, 0},{3, 0},{4, 0},{5, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16348,{2, 0},{3, 0},{4, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16364,{2, 0},{3, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16372,{2, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
  {16376,{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{8, 0},{9, 0},{10, 0},{11, 0},{12, 0},{13, 0},}},
};
#endif

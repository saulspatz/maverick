#ifndef TYPES_H
#define TYPES_H
typedef struct {
  unsigned char rank;
  unsigned char suit;
} Card;

typedef unsigned int RankSet; typedef struct {
  Card cards[7];
  RankSet ranks;} Spades7;

typedef struct {
  Card cards[8];
  RankSet ranks;} Spades8;

typedef struct {
  Card cards[9];
  RankSet ranks;} Spades9;

typedef struct {
  Card cards[10];
  RankSet ranks;} Spades10;

typedef struct {
  Card cards[11];
  RankSet ranks;} Spades11;

typedef struct {
  Card cards[12];
  RankSet ranks;} Spades12;

typedef struct {
  Card cards[13];
  RankSet ranks;} Spades13;

typedef struct {
  Card cards[4];
  RankSet ranks;} Hearts4;

typedef struct {
  Card cards[5];
  RankSet ranks;} Hearts5;

typedef struct {
  Card cards[6];
  RankSet ranks;} Hearts6;

typedef struct {
  Card cards[7];
  RankSet ranks;} Hearts7;

typedef struct {
  Card cards[8];
  RankSet ranks;} Hearts8;

typedef struct {
  Card cards[9];
  RankSet ranks;} Hearts9;

typedef struct {
  Card cards[10];
  RankSet ranks;} Hearts10;

typedef struct {
  Card cards[11];
  RankSet ranks;} Hearts11;

typedef struct {
  Card cards[12];
  RankSet ranks;} Hearts12;

typedef struct {
  Card cards[1];
  RankSet ranks;} Diamonds1;

typedef struct {
  Card cards[2];
  RankSet ranks;} Diamonds2;

typedef struct {
  Card cards[3];
  RankSet ranks;} Diamonds3;

typedef struct {
  Card cards[4];
  RankSet ranks;} Diamonds4;

typedef struct {
  Card cards[5];
  RankSet ranks;} Diamonds5;

typedef struct {
  Card cards[6];
  RankSet ranks;} Diamonds6;

typedef struct {
  Card cards[7];
  RankSet ranks;} Diamonds7;

typedef struct {
  Card cards[8];
  RankSet ranks;} Diamonds8;

typedef struct {
  Card cards[1];
  RankSet ranks;} Clubs1;

typedef struct {
  Card cards[2];
  RankSet ranks;} Clubs2;

typedef struct {
  Card cards[3];
  RankSet ranks;} Clubs3;

typedef struct {
  Card cards[4];
  RankSet ranks;} Clubs4;

typedef struct {
  Card cards[5];
  RankSet ranks;} Clubs5;

typedef struct {
  Card cards[6];
  RankSet ranks;} Clubs6;

#endif

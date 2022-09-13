#ifndef TYPES_H
#define TYPES_H

// count{n} =  13 choose n
#define count1 13
#define count2 78
#define count3 286
#define count4 715
#define count5 1287
#define count6 1716
#define count7 count6
#define count8 count5
#define count9 count4
#define count10 count3
#define count11 count2
#define count12 count1
#define count13 1

typedef unsigned short RankSet;

typedef RankSet Suit1[count1];
typedef RankSet Suit2[count2];
typedef RankSet Suit3[count3];
typedef RankSet Suit4[count4];
typedef RankSet Suit5[count5];
typedef RankSet Suit6[count6];
typedef RankSet Suit7[count7];
typedef RankSet Suit8[count8];
typedef RankSet Suit9[count9];
typedef RankSet Suit10[count10];
typedef RankSet Suit11[count11];
typedef RankSet Suit12[count12];
typedef RankSet Suit13[count13];

#define ACE 1
#define JACK 11
#define QUEEN 12
#define KING 13
#define HIGH_ACE 14 

#endif

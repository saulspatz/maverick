/*  dance2.h
* Solve using Knuth's DLX1 algorithm.  If we consider the pat hands as subsets
* of the deal, then this becomes a set exact cover problem.  In Knuth's terminology,
* the cards in the deal are the items and the pat hands that can be constructed in the
* deal are the options. Since every option has five items, we don't need spacers.   
*/

typedef struct Node {
  int up;
  int down;
  int item;  // aliased to "length" in the header nodes 
  int mod;   // index from 0 to 4    
} Node; 

typedef struct Item {
  char name[4];                         // symbolic identification of the item for printing
  int left;
  int right;
} Item;

#define length item     // for use in the header nodes

Item items[26];         // one extra for the root
Node nodes[26000];      // the ones in the matrix (and the header nodes)
int choice[5];          // the hand chosen on each level
char rankCode[] = " A23456789TJQK";
char suitCode[] = "CDHS";


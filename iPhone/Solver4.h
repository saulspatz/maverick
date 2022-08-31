//
//  Solver.h
//  Maverick
//
//  Created by Saul Spatz on 8/30/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
// Solve using Knuth's DLX algorithm.  If we consider the pat hands as subsets
// of the deal, then this becomes a set exact cover problem.  In Knuth's terminology,
// the cards in the deal become the columns of a 0-1 matrix, the hands are the rows, 
// and a entry is 1 if and only if the card corresponding to the column occurs in
// the hand crresponding to the row.  Much of the code here, and many of the comments, are
// copied from the dance.w program available on Knuth's website.


#include "Hand.h"

// Each column of the input matrix is represented by a column struct,
// and each row is represented as a linked list of node structs. There's one
// node for each nonzero entry in the matrix.

// More precisely, the nodes are linked circularly within each row, in
// both directions. The nodes are also linked circularly within each column;
// the column lists each include a header node, but the row lists do not.
// Column header nodes are part of a column struct, which
// contains further info about the column.

// Each node contains five fields. Four are the pointers of doubly linked lists,
// already mentioned; the fifth points to the column containing the node.

struct col_struct;  // Forward declaration needed because node_struct 
                    // and col_struct refer to one another.  

typedef struct node_struct {
  struct node_struct *left,*right; /* predecessor and successor in row */
  struct node_struct *up,*down; /* predecessor and successor in column */
  struct col_struct *col; /* the column containing this node */
} node;

// Each column struct contains six fields:
// The head is a node that stands at the head of its list of nodes;
// the len tells the length of that list of nodes, not counting the header;
// the name is an identifier;
// order is an integer used to communiacte the solution to the view
// next and prev point to adjacent columns, when this
// column is part of a doubly linked list.

// As backtracking proceeds, nodes
// will be deleted from column lists when their row has been blocked by
// other rows in the partial solution.
// But when backtracking is complete, the data structures will be
// restored to their original state.


typedef struct col_struct {
  node head;                        // the list header 
  int len;                          // the number of non-header items currently in this column's list 
  int order;                        // for communicating solution to view 
  char name[4];                     // symbolic identification of the column, for printing 
  struct col_struct *prev,*next;    // neighbors of this column 
} column;

// gateway to the unsettled columns 
#define root colArray[0] 


NSMutableArray* deal;
column colArray[26];            // one extra for the root
node nodeArray[16384];          // the ones in the matrix
node* curNode;                  // next node to allocate
node *choice[5];                // the row and column chosen on each level


setDeal: (NSMutableArray*) _deal;
- (void) findAllFlushes;
- (void) findFlushes: (NSMutableArray*) suit;
- (void) findPatHands;
- (void) addHand: (Hand*) hand;
- (void) coverColumn: (column*) col;
- (void) uncoverColumn: (column*) col;
- (void) recordSolution;
- (BOOL) solve;
- (void) printSolution;
- (void) dealloc;


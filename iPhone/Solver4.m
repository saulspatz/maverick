//
//  Solver4.m
//  Maverick
//
//  Created by Saul Spatz on 8/30/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Solver4.h"
#import "Hand.h"
@class Hand;
@class Card;

int solution[5][5];

BOOL okay(NSMutableArray* theCards, int length) {
    // True if the first length cards in theCards can be part of a 
    // full house or straight
    
    static BOOL full[5];
    static BOOL straight[5];
    static ranks rank[5];
    
    switch (length) {
    case 1: 
        full[0] = straight[0] = YES;
        break;
    case 2:
        rank[0]  = [[theCards objectAtIndex:0] getRank];
        rank[1]  = [[theCards objectAtIndex:1] getRank];
        full[1] = rank[0] == rank[1];
        straight[1] = rank[1] - rank[0] == 1;
        break;
    case 3:
        rank[2]  = [[theCards objectAtIndex:2] getRank];
        full[2] = full[1];
        straight[2] = straight[1] && ( rank[2] - rank[1] == 1);
        break;
    case 4:
        rank[3]  = [[theCards objectAtIndex:3] getRank];
        full[3] = full[2] && rank[3] != rank[0] && 
				( rank[2] == rank[1] || rank[2] == rank[3] );
        straight[3] = straight[2] && ( rank[3] - rank[2] == 1);
        break;
    case 5:
        rank[4]  = [[theCards objectAtIndex:4] getRank];
        full[4] = full[3] && rank[4] == rank[3];
        straight[4] = straight[3] && ( rank[4] - rank[3] == 1 || ( rank[4] == ACE && rank[3] == FIVE) );
        break;
    }
    return full[length-1] || straight[length-1];
}    
        
@implementation Solver

- (id)   init {
    self = [super init];
    curNode = nodeArray;
    return self;
}

- (void) setDeal: (NSMutableArray*) _deal {
    column* curCol = colArray+1;
    Card *card;
    NSEnumerator* theCards;
    
    curNode = nodeArray;
    deal = [NSMutableArray arrayWithArray:_deal];
    [deal sortUsingSelector:@selector(compareByRank:)];  // column orders will increase
    theCards = [deal objectEnumerator];
    while ( card = [theCards nextObject] ) {
        curCol->name =  [card string];
        curCol->order   = [card getOrder]; 
        curCol->head.up = curCol->head.down = &curCol->head;
        curCol->prev = curCol-1;
        (curCol-1)->next = curCol;
        curCol->len = 0;
        curCol += 1;
    }
    (curCol-1)->next = &root;
    root.prev = curCol-1;
    root.name = nil;    // root is the only column with no name
    root.order = -1;    // or with negative order
}

- (void) addHand: (Hand*) hand {
    // Pre: The cards in both the deal and the hand are sorted in increasing
    // order of the order, that is, first by rank and then by suit.
    
    int k;
    int order;
    node* theNode =curNode;
    column* curCol = colArray+1;
    NSMutableArray* theCards = [hand getCards];
     
    for ( k = 0; k < 5; k++ )  { 
        theNode->left = theNode-1;
        theNode->right = theNode+1;
        order = [[theCards objectAtIndex: k] getOrder];
        while ( curCol->order != order )
            curCol++;
        theNode->col = curCol;
        theNode->up = curCol->head.up;
        curCol->head.up->down = theNode;
        curCol->head.up = theNode; 
        theNode->down = &curCol->head;
        curCol->len++;
        theNode++; 
    }
    // To circularly link the row, we have to adjust the leftmost left
    // and the rightmost right pointers.
    theNode -= 1;
    theNode->right = curNode;
    curNode->left = theNode;
    curNode += 5;   
}

- (void) findAllFlushes {

    // Find all flushes that can be made from deal and put them into matrix
    
    NSMutableArray* allSuits = [[NSMutableArray alloc] init];
    NSEnumerator*   allCards = [deal objectEnumerator];
    Card* theCard;
    suits suit;
    for ( suit = CLUBS; suit <= SPADES; suit++ )
        [allSuits addObject: [[NSMutableArray alloc] init]];
    
    // separate deal into suits
     
    while ( theCard = [allCards nextObject] )
        [[allSuits objectAtIndex:[theCard getSuit]] addObject: theCard];
        
    for ( suit = CLUBS; suit <= SPADES; suit++ ) {
        [self findFlushes: [allSuits objectAtIndex:suit]];
        [ [allSuits objectAtIndex:suit] release];
    }
    [allSuits release];
}

- (void) findFlushes: (NSMutableArray*) suit {
    int j[5];     // loop counters
    int k;        // level
    NSMutableArray *theCards;
     
    if ( [suit count] < 5 )
        return;
        
    theCards = [[NSMutableArray alloc] init];
    for ( k = 0; k < 5; k++ ) {
        j[k] = k;
        [theCards addObject: [suit objectAtIndex:j[k]]];
    }
    while (k >= 0) {
        // save the newly constructed flush
        Hand* hand = [[Hand alloc] init];
        [hand setHandFromCards:theCards];
        [hand evaluate];
        [self addHand: hand];
        [hand release];
        
        // construct the next flush
        // find rightmost counter not at maximum value
        k = 4;
        while ( j[k] ==  [suit count] - 5 + k )
			k -= 1;
        if ( k >= 0 )
		{	j[k] += 1;
			[theCards replaceObjectAtIndex:k withObject:[suit  objectAtIndex:j[k]]];
			while ( k < 4 )
			{	k += 1;
			    j[k] = j[k-1] + 1;
				[theCards replaceObjectAtIndex:k withObject:[suit objectAtIndex:j[k]]];
			}
		}
    }
    [theCards release];
}

- (void) findPatHands {

    // Find all pat poker hands that can be constructed from the  
	// cards in the deal, and store in the patHands array.
	// All flushes come first, in arbitrary order,
	// then the non-flushes, in dictionary order.
	// We use the fact that the deal has been sorted by rank and then by
	// suit.  Most of the logic is hidden in okay()
        
    int  next[5];   // index in deal of next card to try at each level 
	int  level;
    int numCards = [deal count];
    NSMutableArray *theCards = [[NSMutableArray alloc] init];
    handValues value;
    
    [self findAllFlushes];
    level = 0;
	next[0] = 0;
    while ( level >= 0 ) {
    	if ( next[level] <= numCards- 5 + level ) {
            [theCards insertObject:[deal objectAtIndex:next[level]]  atIndex:level];
            if ( ! okay(theCards, level+1) ) {
                [theCards removeLastObject];
                next[level] += 1;
                continue;
            }
            if ( level == 4 ) { 
                // found a pat hand                 
                Hand* hand = [[Hand alloc] init];
                [hand setHandFromCards:theCards];
                [hand evaluate];
                // Don't double count straight flushes
                value = [hand getValue];
                if ( value != LOWSTFLUSH && value != STFLUSH && value != ROYAL ) 
                    [self addHand:hand];
                [hand release];
                next[4] += 1;
                [theCards removeLastObject];
                continue;
            }
            else           // next level
			{	next[level + 1] = next[level] + 1;
				level += 1;
				continue;
			}
        }
        level -= 1;     // back up a level
        if ( level >= 0 ) {
            [theCards removeLastObject];
            next[level] += 1;
        }
    }
    [theCards release];
}

//- ( BOOL ) solve {
    // Return true if and only deal can be partitioned into
    // disjoint pat hands.
    // Here is where we use the dancing links algorithm
    
    //Backtracking.
    //Our strategy for generating all exact covers will be to repeatedly
    //choose always the column that appears to be hardest to cover, namely the
    //column with shortest list, from all columns that still need to be covered.
    //And we explore all possibilities via depth-first search.

    //The neat part of this algorithm is the way the lists are maintained.
    //Depth-first search means last-in-first-out maintenance of data structures;
    //and it turns out that we need no auxiliary tables to undelete elements from
    //lists when backing up. The nodes removed from doubly linked lists remember
    //their former neighbors, because we do no garbage collection.

    //The basic operation is ``covering a column.'' This means removing it
    //from the list of columns needing to be covered, and ``blocking'' its
    //rows: removing nodes from other lists whenever they belong to a row of
    //a node in this column's list.

    //Backtrack through all solutions
- ( BOOL ) solve {    
    column *bestCol;  // column chosen for branching 
    node *pp;         // traverses a row
    int level;        // number of choices in current partial solution 
    column* curCol;
    int minLen; 
    
    [self findPatHands];
    level=0;
forward:              //Set best_col to the best column for branching
    minLen = 100000;  // minLen = infinity
    
    for ( curCol = root.next; curCol != &root; curCol=curCol->next) 
      if (curCol->len < minLen) { 
        bestCol = curCol; 
        minLen = curCol->len;
    }
    [self coverColumn: bestCol];
    curNode = choice[level] = bestCol->head.down;
advance:
    if ( curNode == &(bestCol->head) ) goto backup;

    //Cover all other columns of cur_node
    for (pp = curNode->right; pp != curNode; pp = pp->right) 
        [self coverColumn: pp->col];
    
    if ( root.next == &root ) {  // Record solution and return YES;
        [self recordSolution];
        return YES;
    }
    level++;
    goto forward;
backup: [self uncoverColumn: bestCol];
    if (level==0)
        return NO;
    level--;
    curNode = choice[level];
    bestCol = curNode->col;
    
    // Uncover all other columns of curNode
    // We included left links, thereby making the rows doubly linked, so
    // that columns would be uncovered in the correct LIFO order in this
    // part of the program. (The uncover routine itself could have done its
    // job with right links only.) (Think about it.)

    for (pp = curNode->left; pp != curNode; pp = pp->left) 
        [self uncoverColumn: pp->col];

    curNode = choice[level] = curNode->down;
    goto advance;
}

- (void) coverColumn: (column*) col {
    // When a row is blocked, it leaves all lists except the list of the
    // column that is being covered. Thus a node is never removed from a list
    // twice.

    column *l,*r;
    node *rr,*nn,*uu,*dd;

    l = col->prev;
    r = col->next;
    l->next = r;
    r->prev = l;
    for ( rr = col->head.down; rr != &(col->head); rr = rr->down)
    for (nn = rr->right; nn != rr; nn = nn->right) {
        uu = nn->up;  
        dd = nn->down;
        uu->down = dd;
        dd->up = uu;
        nn->col->len--;
    }
}

- (void) uncoverColumn: (column*) col {
    // Uncovering is done in precisely the reverse order. The pointers thereby
    // execute an exquisitely choreo\-graphed dance which returns them almost
    // magically to their former state.
    
    column *l,*r;
    node *rr,*nn,*uu,*dd;
    for (rr = col->head.up; rr != &(col->head); rr = rr->up)
    for (nn = rr->left; nn != rr; nn = nn->left) {
        uu = nn->up;
        dd = nn->down;
        uu->down = dd->up=nn;
        nn->col->len++;
    }
    l = col->prev;
    r = col->next;
    l->next = r->prev = col;
}

- (void) recordSolution {
    int level, k;
    node* p;

    for ( level = 0; level < 5; level++ ) {
        p = choice[level];
        for ( k = 0; k < 5; k++ ) {
            solution[level][k] = p->col->order;
            p = p->right;
        }
    }
}

- (void) printSolution {
    // For debugging
    int level, k;
    node* p;
    char solnString[128];
    char* cursor = solnString;
    
    for ( level = 0; level < 5; level++ ) {
        p = choice[level];
        for ( k = 0; k < 5; k++ ) {
            *cursor++ = [p->col->name characterAtIndex:0];
            *cursor++ = [p->col->name characterAtIndex:1];
            *cursor++ = ' ';
            p = p->right;
        }
    }
    *cursor++ = '\n';
    *cursor++ = '\n';
    *cursor = '\0';
    printf("%s", solnString);    
}
            
- (void) dealloc {
    [deal removeAllObjects];
    [deal release];
    [super dealloc];
}

@end


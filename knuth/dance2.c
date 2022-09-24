#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // for memset
#include <assert.h>
#include "dance2.h"
#include "types.h" //for RankSet

typedef struct {  // for testing only
    int flushes;
    int straights;
    int fullHouses;
} Value;

enum {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

int cards[16][5];    // no rank 0; room for high Ace, rank and suit totals
int inverted[53];    // inverted list of the column headers  
#define SUIT_TOTAL 15
#define RANK_TOTAL 4

void addHand(int hand[]);

int findFlushes() {
    // find all flushes
    int flushes = 0;
    for (int s = CLUBS; s <= SPADES; ++s) {
        int length = cards[SUIT_TOTAL][s];
        if (length < 5)
            continue;
        int suit[length];
        int k = 0;
        for (int r = ACE; r <= KING; r++) {
            if (cards[r][s]) {
                suit[k] = cards[r][s];
                k++;
            }
        }

        int hand[5];
        for (int i0 = 0; i0 < length - 4; i0++) {
            hand[0] = suit[i0];        
            for (int i1 = i0 + 1; i1 < length - 3; i1++) {
                hand[1] = suit[i1];
                for (int i2 = i1 + 1; i2 < length - 2; i2++) {
                    hand[2] = suit[i2];
                    for (int i3 = i2 + 1; i3 < length - 1; i3++) {
                        hand[3] = suit[i3];
                        for (int i4 = i3 + 1; i4 < length; i4++) {
                            hand[4] = suit[i4];
                            addHand(hand);
                            flushes++;
                        }
                    }
                }
            }
        }
    }
    return flushes;
}

int findFullHouses() {
    // find all full houses

    // Bring all cards to the front of the row
    for (int r = ACE; r <= KING; r++) {
        if (cards[r][RANK_TOTAL]==0) continue;
        for (int k = 2; k >=0; k--) {
            if (cards[r][k]==0 && cards[r][k+1] != 0) {
                for (int j = k; j < 3; j++)
                    cards[r][j] = cards[r][j+1];
            }
        }
        // Don't have to worry about duplicates left behind,
        // because cards[RANK_TOTAL] tells us how many cards 
        // of rank r there are in the deal. 
    }
    int f = 0; // number of fours of a kind
    int t = 0; // number of trips
    int p = 0; // number of pairs
    int fulls = 0;
    for (int k = ACE; k <= KING; ++k) {
        if (cards[k][RANK_TOTAL] == 4)
            f++;
        else if (cards[k][RANK_TOTAL] == 3)
            t++;
        else if (cards[k][RANK_TOTAL] == 2)
            p++;
    }
    int T = 4*f + t;
    int P = 6*f + 3*t + p;
    int trips[T][3];
    int pairs[P][2];

    memset(trips, 0, sizeof(trips));
    memset(pairs, 0, sizeof(pairs));

    t = 0;
    p = 0;
    for (int r = ACE; r <= KING; r++) {
        int length = cards[r][RANK_TOTAL];
        if (length == 4) {
            for (int j0 = 0; j0<2; j0++)
            for (int j1 = j0+1; j1 < 3; j1++)
            for( int j2 = j1+1; j2 < 4; j2++) {
                trips[t][0] = cards[r][j0];
                trips[t][1] = cards[r][j1];
                trips[t][2] = cards[r][j2];
                t++;
            }
            for (int j0 = 0; j0<3; j0++)
            for (int j1 = j0+1; j1 < 4; j1++) {
                pairs[p][0] = cards[r][j0];
                pairs[p][1] = cards[r][j1];
                p++;
            }
        }
        else if (length == 3) {
            for (int j = 0; j < 3; j++) 
                trips[t][j] = cards[r][j];
            t++;
            for (int j0 = 0; j0 < 2; j0++)
            for (int j1 = j0+1; j1 < 3; j1++) {
                pairs[p][0] = cards[r][j0];
                pairs[p][1] = cards[r][j1];
                p++;
            }                
        }
        else if (length == 2) {
            for (int j = 0; j < 2; j++) 
                pairs[p][j] = cards[r][j];
            p++;
        }
    }
    
    for (int t = 0; t < T; t++) {
        int hand[5];
        hand[0] =trips[t][0];
        hand[1] =trips[t][1];
        hand[2] =trips[t][2];
        for (int p = 0; p < P; p++) {
            if ((trips[t][0] - pairs[p][0]) % 13 == 0)
                continue;  // trips and pair can't have same rank
            hand[3] = pairs[p][0];
            hand[4] = pairs[p][1];
            addHand(hand);
            fulls++;
        }
    }
    return fulls;
}

int findStraights() {
    // Find the straights.  First, add a high Ace,
    // if there is an Ace in the suit
    /************ TODO *********
    *   
    * Exclude straight flushes
    * 
    *  ************************/ 

    int straights = 0;
    for (int s = CLUBS; s <= SPADES; s++)
        if (cards[ACE][s]) 
        cards[14][s] = cards[ACE][s];
    cards[14][RANK_TOTAL] = cards[ACE][RANK_TOTAL];

    #define none(r) (cards[(r)][RANK_TOTAL]==0)
    for (int low = ACE; low <= 10; low++) {
        if (none(low) || none(low+1) || none(low+2) || none(low+3) || none(low+4))
            continue;
        int hand[5];
        int i[5];
        for (i[0]=0; i[0]<cards[low][RANK_TOTAL]; i[0]++) {
            hand[0] = cards[low][i[0]];
            for (i[1]=0; i[1]<cards[low+1][RANK_TOTAL]; i[1]++) { 
                hand[1] = cards[low+1][i[1]]; 
                for (i[2]=0; i[2]<cards[low+2][RANK_TOTAL]; i[2]++) { 
                    hand[2] = cards[low+2][i[2]];
                    for (i[3]=0; i[3]<cards[low+3][RANK_TOTAL]; i[3]++) {
                        hand[3] = cards[low+3][i[3]];
                        for (i[4]=0; i[4]<cards[low+4][RANK_TOTAL]; i[4]++) {
                            hand[4] = cards[low+4][i[4]]; 
                            addHand(hand);
                            straights++;
                        }
                    }
                }
            }
        }
     }
    return straights;
}      

// Dancing links starts here

int currentNode;
void print_row(int p) {
    //for debugging 
    int q = p - nodes[p].mod;
    int stop = q + 5;
    for (; q != stop; q++) {
        Node qq = nodes[q];
        fprintf(stderr, "node %d: %s up: %d down: %d\n", q, items[qq.item].name, qq.up, qq.down);
    }
    fprintf(stderr, "\n\n");
}

void print_items() {
    //for debugging 

    int i = items[0].right;
    while (i != 0) {
        printf("%s ", items[i].name);
        i = items[i].right;
    }
    printf("\n\n");
 }

void cover(int i) { 
    // cover item i
    int before = items[i].left;
    int after = items[i].right;
    items[before].right = after;
    items[after].left = before;
    for (int rr = nodes[i].down; rr != i; rr = nodes[rr].down) { 
        int nn = rr - nodes[rr].mod;
        int stop = nn+5;
        for (; nn != stop; nn++) {
            if (nn == rr) continue ;
            int above = nodes[nn].up;
            int below = nodes[nn].down;
            int ii = nodes[nn].item;
            nodes[above].down = below;
            nodes[below].up = above;
            nodes[ii].length -= 1;
        }
    }
}

void uncover(int i) {
    //uncover item i
    for (int rr = nodes[i].up; rr != i; rr = nodes[rr].up) { 
        int nn = rr +4 - nodes[rr].mod;
        int stop = nn - 5;
        for (; nn != stop ; nn--) {
            if (nn == rr) continue;
            int above = nodes[nn].up;
            int below = nodes[nn].down;
            int ii = nodes[nn].item;
            nodes[above].down = nodes[below].up = nn;
            nodes[ii].length += 1;
        }
    }
    int before = items[i].left;
    int after = items[i].right;
    items[before].right = items[after].left = i;
}

void pips(int card, char buffer[]) {
    int rank = (card - 1)% 13 +1;
    int suit = (card -1) / 13;
    buffer[0] = rankCode[rank];
    buffer[1] = suitCode[suit];
    buffer[2] = '\0';    
}

void addHand(int hand[]) {
    for (int k = 0; k < 5; k++) {
        int i = inverted[hand[k]];
        nodes[i].length = nodes[i].length+1;
        nodes[currentNode].item = i;
        nodes[currentNode].up = nodes[i].up;
        nodes[nodes[i].up].down = currentNode;
        nodes[i].up = currentNode;
        nodes[currentNode].down = i;
        nodes[currentNode].mod = k;
        currentNode++;
    }
}

int solver(RankSet spades, RankSet hearts,
            RankSet diamonds, RankSet clubs, Value *value) {

    RankSet bitsets[4];
    bitsets[0] = clubs;
    bitsets[1] = diamonds;
    bitsets[2] = hearts;
    bitsets[3] = spades; 

    #define RANK_TOTAL 4

    memset(cards, 0, sizeof(cards));

    for (int s = CLUBS; s <= SPADES; s++) 
    for (int r = ACE; r <= KING; r++) {
        int mask = (1 << r);
        if (mask & bitsets[s]) {
            cards[r][s] = 13*s + r;
            cards[r][RANK_TOTAL] += 1;
            cards[SUIT_TOTAL][s] += 1;
        }
    }
    
    // Make the item headers and an inverted list of them
    // Also make the header nodes 
  
    int currentItem = 1;    //skip root
    currentNode = 1;        //nodes[0] is unused 
   
    for (int s = CLUBS; s <= SPADES; s++) 
    for (int r = ACE; r <= KING; r++){
        if (cards[r][s] == 0)
            continue;   
        nodes[currentItem].up = nodes[currentItem].down = currentItem;
        nodes[currentItem].length = 0;
        items[currentItem].left = currentItem - 1;
        pips(cards[r][s], items[currentItem].name);
        inverted[cards[r][s]] = currentItem;
        items[currentItem - 1].right = currentItem;
        currentItem++;
        currentNode++;
    }

    items[25].right = 0;
    items[0].left = 25;
    
    int flushes = findFlushes();
    int fulls = findFullHouses();
    int straights = findStraights();

    value->flushes = flushes;
    value->straights = straights;
    value->fullHouses = fulls;
    
    // Matrix constructed.  Find a solution, if one exists.

    int level = 0;
    int bestItem = 1; // best item for branching has minimum length
    int minLength;

forward:

    minLength = 100000; // infinity
    for (currentItem = items[0].right; currentItem != 0; currentItem = items[currentItem].right) {
        if (nodes[currentItem].length < minLength) {
            bestItem = currentItem;
            minLength = nodes[currentItem].length;
        }
    }
    cover(bestItem);
    currentNode = choice[level] = nodes[bestItem].down;

advance:

    if (currentNode <= 25)
        goto backup;
    int pp = currentNode - nodes[currentNode].mod;
    int stop = pp + 5;
    for (; pp != stop; pp++) {
        if (pp == currentNode) continue;
        cover(nodes[pp].item);
    }

    if (items[0].right == 0) 
        return 1;     // all columns covered
    level++;
    goto forward;

backup:

    uncover(bestItem);
    if (level == 0) 
        return 0;  // we'd have short-circuited had there been a solution
    level--;
    currentNode = choice[level];
    bestItem = nodes[currentNode].item;

    pp = currentNode + 4 - nodes[currentNode].mod; 
    stop = pp -5;
    for (; pp != stop; pp--) {
        if (pp == currentNode) continue;
        uncover(nodes[pp].item);
    }
    currentNode = choice[level] = nodes[currentNode].down;
    goto advance;
}
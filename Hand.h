//
//  Hand.h
//  Maverick
//
//  Created by Saul Spatz on 8/25/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//


typedef enum {CLUBS, DIAMONDS, HEARTS, SPADES} suits;
typedef enum {DEUCE, TREY, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE} ranks;
typedef enum  {BUST, PAIR, TWOPAIR, TRIPS, LOWSTRAIGHT, STRAIGHT, FLUSH, FULL, 
               FOURS, LOWSTFLUSH, STFLUSH, ROYAL} handValues;
      
@class Hand;

struct Card {
    suits            suit;
    ranks            rank;
    int              order;
};

- (id)                 initWithRank: (ranks) theRank andSuit: (suits) theSuit;
- (int)                getOrder;
- (suits)              getSuit;
- (ranks)              getRank;
- (NSComparisonResult) compareByRank: (Card *) otherCard;
- (NSComparisonResult) compareBySuit: (Card *) otherCard;
- (NSString*)          string;
- (void)               dealloc;
@end

// A hand is a set of cards, perhaps fewer or more than five.
// If there are exactly five cards, it is considered a poker hand.

@interface Hand : NSObject {
    NSMutableArray *cards;   // the cards in the hand
    handValues value;        // BUST if not a poker hand
}
- (id)                 init;
- (int)                numRanks;
- (int)				   count;
- (handValues)         flush;
- (handValues)         straight;
- (handValues)         pairs;
- (void)               evaluate;
- (ranks)              minRank;
- (ranks)              maxRank;
- (NSMutableArray*)    getCards;
- (handValues)         getValue;
- (NSString*)          string;
- (int)                numCardsWithRank: (ranks) theRank;
- (BOOL)               isPat;
- (BOOL)               isEmpty;
- (BOOL)               isFlush;
- (BOOL)               containsCard: (Card *) theCard;
- (BOOL)               isDisjointFrom: (Hand*) otherHand;
- (void)               sort;
- (void)               setHandFromCards:(NSMutableArray *) theCards;
- (void)               removeCard: theCard;
- (void)               addCard: theCard;
- (void)               removeAllCards;
- (void)               dealloc;  

@end

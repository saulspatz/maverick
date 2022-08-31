//
//  Hand.m
//  Maverick
//
//  Created by Saul Spatz on 8/25/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Hand.h"

char rankString[] = "23456789TJQKA";
char suitString[] ="CDHS";

@implementation Card

- (id) initWithRank: (ranks) theRank andSuit: (suits) theSuit {
    self = [super init];
    suit = theSuit;
    rank = theRank;
    order = 4*rank + suit;
    return self;
}

- (int) getOrder {
    return order;
}

- (suits) getSuit {
    return suit;
}

- (ranks) getRank {
    return rank;
}

- (NSComparisonResult) compareByRank: (Card *) otherCard {

    ranks otherRank = [otherCard getRank];
    suits otherSuit = [otherCard getSuit];
    
    if ( rank < otherRank )
        return NSOrderedAscending;
    if ( rank > otherRank )
        return NSOrderedDescending;
    if ( suit < otherSuit )
        return NSOrderedAscending;
    if ( suit > otherSuit )
        return NSOrderedDescending;        
    return NSOrderedSame;
}

- (NSComparisonResult) compareBySuit: (Card *) otherCard {

    ranks otherRank = [otherCard getRank];
    suits otherSuit = [otherCard getSuit];
    
    if ( suit < otherSuit )
        return NSOrderedAscending;
    if ( suit > otherSuit )
        return NSOrderedDescending;
    if ( rank < otherRank )
        return NSOrderedAscending;
    if ( rank > otherRank )
        return NSOrderedDescending;        
    return NSOrderedSame;
}


- (NSString*) string {
    NSMutableString* answer = [[NSMutableString alloc] init];
    
    [answer appendFormat:@"%c%c (%d)", rankString[rank], suitString[suit], [self getOrder]];
    
    [answer autorelease];
    
    return answer;
}

- (void) dealloc {
    [super dealloc];
}
    
@end

@implementation Hand

- (id) init {
    self = [super init];
    cards = [[NSMutableArray alloc] init];
    value = BUST;
    return self;
}

- (int) count {
    return [cards count];
}

- (int) numRanks {
    int rankArray[13];
    int index;         // loop counter
    int answer = 0;
    NSEnumerator *allCards = [cards objectEnumerator];
    id theCard;
    
    for (index = 0; index < 13; index++)
        rankArray[index] = 0;
        
    while ( theCard = [allCards nextObject] )
        rankArray[ [theCard getRank] ] += 1;
        
    for ( index = 0; index < 13; index++ )
        if ( rankArray[index] != 0 ) answer += 1;
    
    return answer;
}

- (ranks) minRank {
    ranks        answer;
    NSEnumerator *allCards = [cards objectEnumerator];
    ranks         theRank;
    id            theCard;
    
      
    answer =  [ [cards objectAtIndex:0] getRank];
    while ( theCard = [allCards nextObject] ) {
        theRank = [theCard getRank];
            if ( theRank < answer ) 
                answer = theRank; 
    }
    return answer;
}

- (ranks) maxRank {
    ranks   answer;
    NSEnumerator *allCards = [cards objectEnumerator];
    ranks         theRank;
    id            theCard;
    
    answer =  [ [cards objectAtIndex:0] getRank];
    while ( theCard = [allCards nextObject] ) {
        theRank = [theCard getRank];
        if ( theRank > answer ) 
            answer = theRank; 
    }
    return answer;
}

- (handValues) flush {
    handValues   answer;
    suits        theSuit;
    NSEnumerator *allCards = [cards objectEnumerator];
    id           theCard;
     
    theSuit =  [ [cards objectAtIndex:0] getSuit];
    while ( theCard = [allCards nextObject] ) {
        if ( [theCard getSuit] != theSuit )
            return BUST;
    }
    answer = [self straight];
    if ( answer == BUST )
        return FLUSH;
    if ( answer == LOWSTRAIGHT )
        return LOWSTFLUSH;
    if ( [self minRank] == TEN )
        return ROYAL;
    return STFLUSH;
}

- (handValues) straight {
    handValues  lowCard;
    handValues  highCard;
    
    if ( [self numRanks] != 5 )
        return BUST;
    lowCard = [self minRank];
    highCard = [self maxRank];
    if ( highCard - lowCard == 4 )
        return STRAIGHT;
    if ( lowCard == DEUCE && highCard == ACE ) {
        ranks rank2 = DEUCE;
        int card;
        
        for ( card = 0; card < 5; card++ ) {
            ranks r = [[cards objectAtIndex:card] getRank];
            if ( r > rank2 && r != ACE )
                rank2 = r;
        }
        if ( rank2 == FIVE )
            return LOWSTRAIGHT;
    }
    return BUST;
}

- (int) numCardsWithRank: (ranks) theRank {
    int          answer = 0;
    NSEnumerator *allCards = [cards objectEnumerator];
    id           theCard;
    
    while ( theCard = [allCards nextObject] ) {
        if ( [theCard getRank] == theRank )
            answer += 1;
    }
    return answer;
}

- (handValues) pairs {
    int   numRanks;
    ranks lowCard;
    ranks highCard;
    int   lowCount;
    int   highCount;
    
    numRanks = [self numRanks];
    if ( numRanks == 5 )
        return BUST;
    if ( numRanks == 4 )
        return PAIR;
    lowCard = [self minRank];
    lowCount = [self numCardsWithRank: lowCard];
  
    if ( numRanks == 2 )  {           // four of a kind or full house
        if ( lowCount == 1 || lowCount == 4 )
            return FOURS;
        return FULL;
    }
    
    // three of a kind or two pair
    
    if ( lowCount == 3 )
        return TRIPS;
    if ( lowCount == 2 )
        return TWOPAIR;
    
    // lowCount must have been 1
    // so if it's two pair, both pairs are left
    
    highCard = [self maxRank];
    highCount = [self numCardsWithRank: highCard];
    if ( highCount == 2 )
        return TWOPAIR;
    return TRIPS;
}    

- (void) evaluate {
    handValues temp;
    
    if ( [cards count] != 5 )
        value = BUST;
    else {
        temp = [self pairs];
        if ( temp == BUST )
            temp = [self flush];
        if ( temp == BUST )
            temp = [self straight];
        value = temp;
    }
}

- (BOOL) isPat {
        // Pre: evaluate has been called to set value
        
    return value == LOWSTRAIGHT || value == STRAIGHT || value == FLUSH || value == FULL ||
           value == LOWSTFLUSH  || value == STFLUSH  || value == ROYAL;
}

- (BOOL) isEmpty {
    return [cards count] == 0;
}

- (BOOL) isFlush {
    return value == FLUSH || value == STFLUSH || value == LOWSTFLUSH || value == ROYAL;
}

- (void) sort {
       // Sorts cards in increasing order of rank, except that for LOWSTRAIGHT and LOWSTFLUSH,
       // ACE is counted as low
       // Pre: evaluate has been called to set value
    
    int index;
    
    [cards sortUsingSelector:@selector(compareByRank:)];
    if ( value == LOWSTRAIGHT || value == LOWSTFLUSH ) {
        for ( index = 4; index > 0; index -= 1 )
            [ cards exchangeObjectAtIndex:index withObjectAtIndex:index-1 ];
    }
}
 
 - (BOOL) containsCard: (Card *) theCard {
    NSEnumerator* allCards = [[self getCards] objectEnumerator];
    Card* otherCard;
    
    while ( otherCard = [allCards nextObject] ) {
        if ( theCard == otherCard )
            return YES;
    }
    return NO;
}

- (BOOL) isDisjointFrom: (Hand*) otherHand {
    NSEnumerator* theCards = [[otherHand getCards] objectEnumerator];
    Card* otherCard;
    
    while ( otherCard = [theCards nextObject] ) {
        if ( [ self containsCard: otherCard ] )
            return NO;
    }
    return YES;
}

- (NSString*) string {
    NSMutableString * answer = [[NSMutableString alloc] init];
    NSArray* theCards = [self getCards];
    
    [answer appendString:@"["];
    
    for ( Card * card in theCards ) {
        [answer appendString:[card string]];
        [answer appendString:@" "];
    }
    [answer appendString:@"]"];

    [answer autorelease];
    
    return answer;
}

- (void) setHandFromCards:(NSMutableArray *) theCards {
    [cards removeAllObjects];
    [cards addObjectsFromArray: theCards];
}

- (void) removeCard: theCard {
    [ cards removeObjectIdenticalTo:theCard];
}

- (void) addCard: theCard {
    [ cards addObject:theCard];
}

- (void) removeAllCards {
    [cards removeAllObjects];
}

- (NSMutableArray*) getCards {
    return cards;
}

- (handValues) getValue {
    return value;
}

- (void) dealloc {
    [cards removeAllObjects];
    [cards release];
    [super dealloc];
}
        
@end

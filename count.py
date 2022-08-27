# count.py

import cProfile
from functools import reduce
from typing import Callable, Iterator
from itertools import combinations

first = {suit: tuple(range(suit)) for suit in range(1,14)}
maxSuit = {length:tuple(range(13-length, 13)) for length in range(1,14)}
nextSuit = {}
for length in range(1,13):
    suits = combinations(range(13), length)
    curr = next(suits)
    while curr != maxSuit[length]:
        new = next(suits)
        nextSuit[curr] = (new,)  # facilitate concatenation
        curr = new 

Pattern = tuple[int]
Suit = tuple[int]
Hand = tuple[Suit]  # 25 cards

product = lambda seq: reduce(lambda x,y : x*y, seq, 1)

'''
The processing logic is different depending on whether
or not there are duplicated suit lengths in the hand 
pattern.  We'll have 4 different counting functions,
one for the case of no duplicates, one for the case of
2 equal lengths in 3-suited hands, one for the case of
2 equal lengths in 4-suited hands, and one for 3 equal 
lengths.  This last can only occcur in a 4-suited hand. 
'''

def handGenerator(nextHand:Callable[[Hand],Hand])->Callable[[Pattern], Iterator[Hand]]:
    def allHands(pattern: Pattern)->Iterator[Hand]:
        hand = tuple(tuple(range(suit)) for suit in pattern)
        yield hand
        while (hand := nextHand(hand)) is not None:
            yield hand
    return allHands
    
def count_different(pattern:Pattern)->int:
    '''
    Return value is the number of hands matching the pattern.
    '''
    assert len(pattern) == len(set(pattern)) and sum(pattern) == 25

    factor = 12 if len(pattern)==2 else 24
    handLength = len(pattern)

    def nextHand(hand:Hand)->Hand:
        # Find the first suit, starting from clubs, that
        # can be increased

        for idx, suit in enumerate(hand[::-1]):
            index = handLength - 1 - idx   #index from front of hand
            if suit != maxSuit[pattern[index]]:
                break
        else:
            return None  
        
        answer = hand[:index]
        length = pattern[index]
        new = nextSuit[suit]
        while pattern[index] == length:
            answer += new
            index += 1
            if index == handLength:
                break
        else:
            answer += tuple(first[suit] for suit in pattern[index:])
        return answer

    allHands = handGenerator(nextHand)

    answer = 0
    for _ in allHands(pattern):
        answer += 1
    return factor * answer

def count_dup3(pattern:Pattern)->int:
    '''
    Return value is the number of hands matching the pattern.
    Pattern is a 3-suited hand with one duplicate: either aab or abb
    '''
    assert len(pattern) == 3 and len(set(pattern)) == 2 and sum(pattern) == 25
    factor0 = 24
    factor1 = 12

    def nextHand(hand:Hand)->Hand:
        # Find the first suit, starting from clubs, that
        # can be increased
        
        for idx, suit in enumerate(hand[::-1]):
            index = 2 - idx   #index from front of hand
            if suit != maxSuit[pattern[index]]:
                break
        else:
            return None  
        
        answer = hand[:index]
        length = pattern[index]
        new = nextSuit[suit]
        while len(hand[index]) == length:
            answer += new
            index += 1
            if index == len(hand):
                break
        else:
            answer += tuple(first[suit] for suit in pattern[index:])
        return answer

    allHands = handGenerator(nextHand)

    answer = 0
    for hand in allHands(pattern):
        if hand[1] in (hand[0], hand[2]):
            answer += factor1
        else:
            answer += factor0
    return answer

def count_dup4(pattern:Pattern)->int:
    '''
    Return value is the number of hands matching the pattern.
    Pattern is a 4-suited hand with one duplicate: either aabc or abbc or abcc
    '''
    
    assert len(pattern) == 4 and len(set(pattern)) == 3 and sum(pattern) == 25
    factor0 = 24
    factor1 = 12
    
    def nextHand(hand:Hand)->Hand:
        # Find the first suit, starting from clubs, that
        # can be increased
    
        for idx, suit in enumerate(hand[::-1]):
            index = 3 - idx   #index from front of hand
            if suit != maxSuit[[pattern][index]]:
                break
        else:
            return None  
        
        answer = hand[:index]
        length = pattern[index]
        new = nextSuit[suit]
        while pattern[index] == length:
            answer += new
            index += 1
            if index == 4:
                break
        else:
            answer += tuple(first[suit] for suit in pattern[index:])
        return answer

    allHands = handGenerator(nextHand)
    answer = 0
    for hand in allHands(pattern):
        if hand[1] in (hand[0], hand[2]) or hand[2] in (hand[1], hand[3]):
            answer += factor1
        else:
            answer += factor0
    return answer

def count_trips(pattern:Pattern)->int:
    '''
    Return value is the number of hands matching the pattern.
    Pattern is a 4-suited hand with 3 equal suits: abbb or aaab
    '''
    
    assert len(pattern) == 4 and len(set(pattern)) == 2 and sum(pattern) == 25
    factor0 = 24
    factor1 = 12
    factor3 = 4

    def nextHand(hand:Hand)->Hand:
        # Find the first suit, starting from clubs, that
        # can be increased
        
        for idx, suit in enumerate(hand[::-1]):
            index = 3 - idx   #index from front of hand
            if suit != maxSuit[pattern[index]]:
                break
        else:
            return None  
        answer = hand[:index]
        length = pattern[index]
        new = nextSuit[suit]
        while pattern[index] == length:
            answer += new
            index += 1
            if index == 4:
                break
        else:
            answer += tuple(first[suit] for suit in pattern[index:])
        return answer

    allHands = handGenerator(nextHand)
    answer = 0
    for hand in allHands(pattern):
        if hand[0] == hand[2] or hand[1] == hand[3]:
            answer += factor3
        elif hand[1] in (hand[0], hand[2]) or hand[2] in (hand[1], hand[3]):
            answer += factor1
        else:
            answer += factor0
    return answer

def test():
    a = count_trips((13,4,4,4))
    print('{:,}'.format(a))

#cProfile.run('test()')
test()


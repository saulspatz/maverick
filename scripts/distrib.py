# distrib.py

'''
Generate all posible hands in Maverick solitaire, up to symmetries.
The suits are monotoniaclly decreasing in length, that is,
len(spades) >= len(hearts) >= len(diamonds) >= len(clubs). The
partitions function takes care of this.

When two suits have the same length, the cards in the second suit
will always be at least as good as the cards in the first suit.
For example, in a given hand, an 8-card heart suit will never be 
worse than an 8-card spade suit.
'''

from typing import Generator
#from partitions import partitions

Hand = tuple[tuple[int]]  # 25 cards

def first(p:tuple[int])->Hand:
    # Given a hand pattern p, construct
    # the first hand with pattern p.
    
    return tuple(tuple(range(suit)) for suit in p)

def maxSuit(length:int)->tuple[int]:
    # Maximum possible suit of this
    # length and this suit. 
    return tuple(range(13-length, 13))

def incrSuit(suit:tuple[int])->tuple[int]:
    # Next suit in order
    for idx, k in enumerate(suit[::-1]):
        if k != 12 - idx:
            break
    index = len(suit)-1-idx  # index from the front
    answer = suit[:index]
    answer += tuple(range(k+1, k+1+len(suit)-index))
    return answer

def nextHand(hand:Hand)->Hand:
    # Find the first suit, starting from clubs, that
    # can be increased
    pattern = tuple(len(suit) for suit in hand)
    for idx, suit in enumerate(hand[::-1]):
        if suit != maxSuit(len(suit)):
            break
    else:
        return None  
    index = len(hand) - 1 - idx   #index from front of hand
    answer = hand[:index]
    length = pattern[index]
    new = (incrSuit(suit),)
    while len(hand[index]) == length:
        answer += new
        index += 1
        if index == len(hand):
            break
    else:
        answer += first(pattern[index:])
    return answer

def allHands(pattern: tuple[int])->Generator[Hand, None, None]:
    hand = first(pattern)
    yield hand
    while (hand := nextHand(hand)) is not None:
        yield hand

if __name__ == '__main__':
    print(nextHand(((0,1,2,3,4,5,6,7,8,9),(1,2,3,4,5),(8,9,10,11,12),(8,9,10,11,12))))

# Solve a deal of Maverick Solitaire#
#         ********* ACE IS LOW ************
#

from itertools import combinations, product
import random
import sys

ranks = (ACE, DEUCE, TREY, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK,
         QUEEN, KING) = range(1,14)
suits = (CLUB, DIAMOND, HEART, SPADE) = range(4)

class Solver:
    def __init__(self, *args):
        self.dist = args
    def findPatHands(self):

        # patHands is a list of all possible pathands.

        # Find all possible pat hands.
        # First, the flushes (including straight flushes)

        deal = self.deal
        patHands = []
        clubs =    [card for card in deal if card[1] == CLUB]
        diamonds = [card for card in deal if card[1] == DIAMOND]
        hearts =   [card for card in deal if card[1] == HEART]
        spades =   [card for card in deal if card[1] == SPADE]

        for suit in (clubs, diamonds, hearts, spades):
            patHands += list(combinations(suit, 5))
        flushes = self.flushes = len(patHands) 

        ranks = [[]]+[[card for card in deal if card[0] == rank]
                  for rank in range(ACE, KING+1)]

        # Get the straights  
        # Straight flushes are duplicated, 
        # but that doesn't matter

        for rank in range(ACE,TEN):
            theRanks = ranks[rank:rank+5]
            if all(theRanks):
                patHands += product(*theRanks)

        # Now the high straights

        theRanks = ranks[TEN:] + [ranks[ACE]] 
        if all(theRanks):
            patHands += product(*theRanks)

        straights = self.straights = len(patHands) - flushes    

        # Full houses

        ranks = [card[0] for card in deal]
        pairs = [rank for rank in range(ACE,KING+1) if ranks.count(rank) == 2]
        trips = [rank for rank in range(ACE,KING+1) if ranks.count(rank) == 3]
        fours = [rank for rank in range(ACE,KING+1) if ranks.count(rank) == 4]

        ranks = [tuple([card for card in deal if card[0] == rank])
                 for rank in range(0,KING+1)]

        for t in trips:
            T = ranks[t]
            for p in pairs:
                P = ranks[p]
                patHands.append(T+P)

        tp = len(patHands) -straights - flushes

        for f in fours:
            F = ranks[f]
            for p in pairs:
                P = ranks[p]
                patHands += [P + s for s in combinations(F, 3)]

        fp = len(patHands) -straights - flushes -tp

        for f in fours:
            F = ranks[f]
            for t in trips:
                T = ranks[t]
                patHands += [s1 + s2 for s1 in combinations(F, 3)
                             for s2 in combinations(T, 2)]
                patHands += [T +  s2 for s2 in combinations(F, 2)]

        ft = len(patHands) -straights - flushes -tp -fp

        for t1 in trips:
            T1 = ranks[t1]
            for t2 in trips:
                T2 = ranks[t2]
                if t1 != t2:
                    patHands += [T1 + p for p in combinations(T2, 2)]

        tt = len(patHands) -straights - flushes -tp -fp -ft

        for f1 in fours:
            F1 = ranks[f1]
            for f2 in fours:
                F2 = ranks[f2]
                if f1 != f2:
                    patHands += [t + p for t in combinations(F1, 3)
                                 for p in combinations(F2, 2)]
        ff = len(patHands) -straights - flushes -tp -fp -ft -tt

        self.fullHouses = len(patHands) - flushes - straights
        self.patHands = patHands

    def run(self):
        sample = random.sample
        ranks = range(ACE, KING+1)
        if not self.dist:
            self.sample = sample(range(1, 53), 25)
            self.sample.sort()
        else:
            dist = self.dist
            self.sample =   [c for c in sample(ranks, dist[0])]
            self.sample +=  [13+c for c in sample(ranks, dist[1])]
            self.sample +=  [26+c for c in sample(ranks, dist[2])]
            self.sample +=  [39+c for c in sample(ranks, dist[3])]
        deal = self.deal = [((c-1)%13+1,(c-1)//13) for c in self.sample]
        
        self.findPatHands()

        # At this point, we have found all the possible pat hands.
        # We find all pat hands containing each individual card, and
        # sort the deck so that cards occurring in the fewest pat
        # hands come first

        pats = {}
        for card in deal:
            pats[card] = [set(pat) for pat in self.patHands if card in pat]

        deal.sort(key = lambda c: len(pats[c]))

        # Try to find 5 pairwise disjoint pat hands.
        # We search for hands containing the rarest cards first

        for hand0 in pats[deal[0]]:
            card1 = [card for card in deal if card not in hand0][0]
            for hand1 in pats[card1]:
                if any([c in hand1 for c in hand0]):
                    continue
                used1 = hand0.union(hand1)
                card2 = [card for card in deal if card not in used1][0]
                for hand2 in pats[card2]:
                    if any([c in hand2 for c in used1]):
                        continue
                    used2 = used1.union(hand2)
                    card3 = [card for card in deal if card not in used2][0]
                    for hand3 in pats[card3]:
                        if any([c in hand3 for c in used2]):
                            continue
                        used3 = used2.union(hand3)
                        card4 = [card for card in deal if card not in used3][0]
                        for hand4 in pats[card4]:
                            if all([card not in used3 for card in hand4]):
                                self.solution = 1
                                return
        self.solution = 0

if __name__ == '__main__':
    args = sys.argv[1:]
    if not args:
        print('Number of trials is a required parameter')
        exit()
    trials = int(args[0])
    args = args[1:]
    if sum(args) not in (0,25) or not all(0<=c<=13 for c in args):
        print("invalid distribution", args)
    solver = Solver(*args)
    with open("problems.txt", "w") as fout1:
        with open("answers.txt", "w") as fout2:
            for _ in range(trials):
                solver.run()
                for card in solver.sample:
                    fout1.write(f'{card} ')
                fout1.write('\n')
                fout2.write(f'{solver.flushes} {solver.straights} {solver.fullHouses} {solver.solution}\n')  
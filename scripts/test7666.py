from itertools import combinations
lineNum = 0

def hex2Hand(x):
    answer = []
    for k in range(13):
        if (1<<k) & x:
            answer.append(k+1)
    return answer

def hasFull(spades, hearts, diamonds, clubs):
    for s in combinations(spades, 2):
        for h in combinations(hearts, 1):
            for d in combinations(diamonds, 1):
                for c in combinations(clubs, 1):
                    hand = s + h + d + c
                    ranks = len(set(hand))
                    if ranks == 2:
                        m = hand.count(hand[0])
                        if m in (2,3): return 1         
    return 0

def hasStraight(spades, hearts, diamonds, clubs):
    for s in combinations(spades, 2):
        for h in combinations(hearts, 1):
            for d in combinations(diamonds, 1):
                for c in combinations(clubs, 1):
                    hand = s + h + d + c
                    if len(set(hand)) != 5:
                        continue
                    if max(hand)-min(hand) == 4:
                        return 1
                    if sorted(hand) == [1,10,11,12,13]:
                        return 1
    return 0




with open('../build/test7666.txt') as fin:
    for line in fin:
        lineNum += 1
        items = line.strip().split()
        if items[0] == 'full':
            s, h, d, c = [int(item, 16) for item in items[1:5]]
            spades = hex2Hand(s)
            hearts = hex2Hand(h)
            diamonds = hex2Hand(d)
            clubs = hex2Hand(c)
            if not hasFull(spades, hearts, diamonds, clubs):
                print(f"Error at {lineNum}")
                continue
        elif len(items) == 9:
            s, h, d, c = [int(item, 16) for item in items[0:4]]
            spades = hex2Hand(s)
            hearts = hex2Hand(h)
            diamonds = hex2Hand(d)
            clubs = hex2Hand(c)
            choice = [int(item) for item in items[4:]]
            if hasStraight(spades, hearts, diamonds, clubs) != 1:
                print(f"Error at {lineNum}")
                continue
            if choice.count(8) != 2 or not all(choice.count(x)==1 for x in (1,2,4)):
                print(f"Error at {lineNum}")
                continue



            
            
        
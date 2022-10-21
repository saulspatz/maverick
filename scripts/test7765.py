from itertools import combinations
lineNum = 0

def hex2Hand(x):
    answer = []
    for k in range(13):
        if (1<<k) & x:
            answer.append(k+1)
    return answer

def hasPat(spades, hearts, diamonds):
    for s in combinations(spades, 2):
        for h in combinations(hearts, 2):
            for d in combinations(diamonds, 2):
                hand = s + h + d
                ranks = len(set(hand))
                if ranks == 2:
                    return 1
                if ranks != 5:
                    return 0
                if max(hand)-min(hand) == 4:
                    return 2
                if sorted(hand) == [1,10,11,12,13]:
                    return 2                   
    return 0

with open('../build/test2.log') as fin:
    for line in fin:
        lineNum += 1
        items = line.strip().split()
        if len(items) == 3:  # no straight
            s, h, d = [int(item, 16) for item in items]
            spades = hex2Hand(s)
            hearts = hex2Hand(h)
            diamonds = hex2Hand(d)
            value = hasPat(spades, hearts, diamonds)
            if value == 2:
                print(f"Full house at line {lineNum}")
            if value ==1:
                print(f"straight at line {lineNum}")
           
        elif len(items) == 9:
            s, h, d, t = [int(item, 16) for item in items[:4]]
            choice = map(int, items[4:])
            spades = hex2Hand(s)
            hearts = hex2Hand(h)
            diamonds = hex2Hand(d)
            suits = list(map(hex2Hand, (d,h,s)))
            straight = hex2Hand(t)
            for k,c in zip(range(5), choice):
                if straight[k] not in suits[c]:
                    print(f"Error at line {lineNum}")
                    break


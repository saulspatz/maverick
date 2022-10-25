from itertools import combinations
lineNum = 0

def hex2Hand(x):
    answer = []
    for k in range(13):
        if (1<<k) & x:
            answer.append(k+1)
    return answer

def hasStraight(spades, hearts, diamonds):
    for s in combinations(spades, 3):
        for h in combinations(hearts, 1):
            for d in combinations(diamonds, 1):
                hand = s + h + d
                ranks = len(set(hand))
                if ranks != 5:
                    continue
                if max(hand)-min(hand) == 4:
                    return 1
                if sorted(hand) == [1,10,11,12,13]:
                    return 1                   
    return 0

if __name__ == '__main__':
    lineNum = 0
    with open("../release/heur8665.log") as fin:
        for line in fin:
            lineNum += 1
            items = line.strip().split()
            s, h, d = [int(item, 16) for item in items[:3]]
            spades = hex2Hand(s) 
            hearts = hex2Hand(h) 
            diamonds = hex2Hand(d) 
            value = hasStraight(spades, hearts, diamonds)
            if value == 1 and items[3] == 'fail':
                print(f'Problem at line {lineNum}')
            elif value == 0 and items[3] != 'fail':
                print(f'Error at line {lineNum}') 

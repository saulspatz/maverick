# partitions.py

'''
Determine the effects of symmteries on the hands in Maverick
solitaire.
'''

from math import factorial
from functools import reduce

def binomial(n,m):
    return factorial(n)//(factorial(m)*factorial(n-m))

product = lambda seq: reduce(lambda x,y : x*y, seq, 1)

def partitions(n: int, m: int, k: int) -> int:
    '''
    Generate partitions of n things into at most
    m parts of size at most k
    '''

    if n == 0:
        yield ()
    if n < 0 or m * k < n:
        return
    for j in range(k, 0, -1):
        for p in partitions(n-j, m-1, j):
            yield (j,) + p


def main():
    '''
    partitions(25, 4, 13) should give the number of
    possible hand patterns.  As a check, we use
    them to count the number of suit distributions. 
    '''
    comps = 0
    for p in partitions(25, 4, 13):
        match p:
            case (s,h):
                comps += 12    # two suits    
            case (s, h, d) if len(set(p)) == 2:
                comps += 12    # 3 suits, 2 alike
            case (s, h, d) if len(set(p)) == 3:
                comps += 24    # 3 distinct suits
            case (s, h, d, c) if len(set(p)) == 4:
                comps += 24    # 4 distinct suits
            case (s, h, d, c) if len(set(p)) == 2:
                comps += 4     # 3 equal suits
            case (s, h, d, c) if len(set(p)) == 3:
                comps += 12   # 2 equal suits
            case (s, h, d, c):
                raise ValueError(str(p))

    assert comps == binomial(28, 3) - 4 * binomial(14, 3)

    '''
    Admittedly, it might be more efficient to write:

    comps = {(2,2):12, (3,2):12, (3,3):24, (4,4):24, (4,2):4, (4,3):12 }
    assert sum(comps[len(p), len(set(p))] for p in partitions(25,4,13)) == \
        binomial(28, 3) - 4 * binomial(14, 3)

    but that's because the whole thing can be determined by the number of
    suits and the number of distinct suits. The matching is much more flexible
    because the variables are bound when the pattern is matched.  In another
    context, I could write

    case (s,h,d,c) if s == c+3:

    for example.
    '''

    # ------------------------

    '''
    For each partion, count the number of hands
    it represents.  This is straight-forward
    when the suit lengths are distinct, but when
    two or more are the same, we muts be careful 
    not to count deals where two suits have the
    same cards more than once.

    We may have two or three suits of the same
    length.  Since 25 is even, we cannot have
    all suits the same length nor two pairs
    of equal-length suits.

    The total should come out to the precomputed total.
    '''
    def dist(p):
        while len(p) < 4:
            p += (0,)
        return '-'.join(str(x) for x in p)
    
    total = binomial(52, 25)
    found = 0

    results = {}
    for p in partitions(25, 4, 13):
        match p:
            case (s, h):
                hands = 12 * product(binomial(13,x) for x in p)

            case (s, h, d) if len(set(p)) == 3:
                hands = 24 * product(binomial(13,x) for x in p)

            case (s, h, d) if  len(set(p)) == 2:
                c2 = binomial(13, h)
                c1 = binomial(13, d if h == s else s)
                hands = 12 * c1 * c2 * (c2 - 1) # all suits different
                hands += 12 * c1 * c2           # two suits identical

            case (s, h, d, c) if len(set(p)) == 4:
                hands = 24 * product(binomial(13,x) for x in p)

            case (s, h, d, c) if len(set(p)) == 3:
                s2 = h if h in (s,d) else d
                c2 = binomial(13, s2)
                hands =  12 * product(binomial(13,t) for t in set(p)) * (c2-1)  # all suits different
                hands += 12 * product(binomial(13,t) for t in set(p))           # two suits identical

            case (s, h, d, c) if len(set(p)) == 2:
                s3,s1 = (s,c) if s==h else (c,s) 
                c3 = binomial(13, s3)
                c1 = binomial(13, s1)
                hands =  4 * c1 * c3 * (c3 - 1) * (c3 - 2)  # all suits different
                hands += 12 * c1 * c3 * (c3 - 1)  # exactly two suits the same
                hands += 4 * c1 * c3              # three suits identical

        found += hands
        results[p] = hands
    
    # partitions.txt sorted lexicographically by partitions 
    with open('partitions.txt', 'w') as fout:
        for p, hands in sorted(list(results.items()), reverse=True):
            fout.write(f'{str(p):14} {"{:,}".format(hands):>18} {hands/total:>9.5%}\n')

    # partitions2.txt is in the same format as test runs, for easy comaprison
    with open('partitions2.txt', 'w') as fout:
        for p, hands in sorted(list(results.items()), key = lambda x:x[1], reverse=True):
            fout.write(f'{dist(p):14} {"{:,}".format(hands):>18}\n')

    assert found == total

if __name__ == '__main__':
    main() 

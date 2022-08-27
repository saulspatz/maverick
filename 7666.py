from itertools import product, combinations
from random import sample
from collections import Counter 

universe = range(13)

trials = 100
successes = 0

for _ in range(trials):
    spades = sorted(sample(universe, 7))
    hearts = sorted(sample(universe, 6))
    diamonds = sorted(sample(universe, 6))
    clubs = sorted(sample(universe, 6))
    other = hearts + diamonds + clubs
    s3 = [s for s in spades if other.count(s) >= 2]
    s2 = [s for s in spades if other.count(s) >= 1] 
    found = False
    for two in product(s3,s2):
        if two[0] == two[1]: continue
        if found: break
        for three in product(hearts, diamonds, clubs):
            if len(set(three)) == three: continue
            c = Counter(two+three)
            if set((c[0], c[1])) == {2,3}:
                successes += 1
                found = True
                break
print(f'{successes} successes in {trials} trials')
# equiv2.py
'''
Compute exactly how many hands would have to be generated, 
taking account of symmetries. Exclude cases where two
suits have the same number of cards
'''
from partitions import partitions, product, binomial

suits = {n: binomial(13,n) for n in range(14)}
total = 19906139282588  # computed in earlier run

classes = 0
for p in partitions(25, 4, 13):
    match p:
        case (s,h):
            hands = product(suits[n] for n in p)
        case (s,h,d) if s > h > d:
            hands = product(suits[n] for n in p)
        case (s,h,d,c) if s > h > d > c:
            hands = product(suits[n] for n in p)
        case _:
            continue
    classes += hands
    print(f'{str(p):14} {"{:,}".format(hands):>18} {hands/total:>9.5%} ')

print('\n{:,} equivalence classes'.format(classes) )
print(f'{classes/total:>9.5%}')


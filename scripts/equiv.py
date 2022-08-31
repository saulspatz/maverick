# exact.py
'''
Compute exactly how many hands would have to be generated, 
taking account of symmetries. 
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
        case (s, h, d) if h == s:
            k = suits[h]
            hands = sum(suits[d]*binomial(k,j) for j in (1,2))
        case (s, h, d) if h == d:
            k = suits[h]
            hands = sum(suits[s]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s==h>d:
            k = suits[h]
            hands = sum(suits[d]*suits[c]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s > h == d > c:
            k = suits[h]
            hands = sum(suits[s]*suits[c]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if h > d == c:
            k = suits[d]
            hands = sum(suits[s]*suits[h]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s == d:
            k = suits[s]
            hands = sum(suits[c]*binomial(k,j) for j in (1,2,3))
        case (s,h,d,c) if h == c:
            k = suits[h]
            hands = sum(suits[s]*binomial(k,j) for j in (1,2,3))
        case _:
            print(f'{p} not matched')
    classes += hands
    print(f'{str(p):14} {"{:,}".format(hands):>18} {hands/total:>9.5%} ')

print('\n{:,} equivalence classes'.format(classes))


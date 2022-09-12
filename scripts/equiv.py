# equiv.py
'''
Compute exactly how many deals would have to be generated, 
taking account of symmetries. 
'''
from partitions import partitions, product, binomial

fout = open('equiv.txt', 'w')

suits = {n: binomial(13,n) for n in range(14)}
equal = {n: binomial(6, n//2) for n in range(14)}
swords = {n: (suits[n]+equal[n])//2 for n in range(14)}

deals = {}
for p in partitions(25, 4, 13):
    match p:
        case (s,h):
            deals[p] = swords[s]*suits[h]
        case (s,h,d) if s > h > d:
            deals[p] = swords[s]* product(suits[n] for n in p[1:])
        case (s,h,d,c) if s > h > d > c:
            deals[p] = swords[s]*product(suits[n] for n in p[1:])
        case (s, h, d) if h == s:
            k = suits[h]
            deals[p] = sum(suits[d]*binomial(k,j) for j in (1,2))
        case (s, h, d) if h == d:
            k = suits[h]
            deals[p] = sum(suits[s]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s==h>d:
            k = suits[h]
            deals[p] = sum(suits[d]*suits[c]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s > h == d > c:
            k = suits[h]
            deals[p] = sum(suits[s]*suits[c]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if h > d == c:
            k = suits[d]
            deals[p] = sum(suits[s]*suits[h]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s == d:
            k = suits[s]
            deals[p] = sum(suits[c]*binomial(k,j) for j in (1,2,3))
        case (s,h,d,c) if h == c:
            k = suits[h]
            deals[p] = sum(suits[s]*binomial(k,j) for j in (1,2,3))
        case _:
            print(f'{p} not matched')
classes = sum(deals.values())
for p, deal in sorted(deals.items(), key=lambda x:x[1], reverse=True):
    while len(p) < 4:
        p+= (0,)
    fout.write(f'{"-".join(str(x) for x in p)} : {deal}\n')

fout.write('\n{:,} equivalence classes\n'.format(classes))
fout.close()


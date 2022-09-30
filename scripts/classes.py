# equiv2.py
'''
Compute exactly how many deals would have to be generated, 
taking account of symmetries. 
'''
from partitions import partitions, product, binomial

def best(*args):
    return min(args, key= lambda x: abs(13-2*x))

fout = open('classes.txt', 'w')

suits = {n: binomial(13,n) for n in range(14)}
equal = {n: binomial(6, n//2) for n in range(14)}
swords = {n: (suits[n]+equal[n])//2 for n in range(14)}

deals = {}
for p in partitions(25, 4, 13):
    match p:
        case (10,5,5,5) | (10,10,5) | (13,12) | (12,12,1) | (13,6,6) | (13,11,1):
            deals[p] = 0
        case (s,h,d) if s > h > d != 5:
            m = best(s,h,d)
            deals[p] = product(suits[n] for n in p if n != m)*swords[m]
        case (s,h,5) if s > h:
            m = best(s,h)
            M = s if m == h else h
            deals[p] = suits[M]*suits[5]*swords[m]
        case (s,h,d,c) if s > h > d > c != 5:
            m = best(s,h,d,c)
            deals[p] = product(suits[n] for n in p if n != m)*swords[m]
        case (s,h,d,5) if s > h > d > 5:
            m = best(s,h,d)
            deals[p] = product(suits[n] for n in p[:-1] if n != m)*suits[5]*swords[m] 
        case (s, h, 5) if h == s:
            k = suits[h]
            deals[p] = sum(binomial(k,j) for j in (1,2))*suits[d]
        case (s, h, d) if h==s > d !=5:
            k = suits[h]
            deals[p] = sum(binomial(k,j) for j in (1,2))*swords[d] 
        case (s, h, d) if h == d:
            k = suits[h]
            deals[p] = sum(binomial(k,j) for j in (1,2))*swords[s]
        case (s,h,d,5) if s==h>d:
            k = suits[h]
            deals[p] = sum(swords[d]*suits[5]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s==h>d>c!=5:
            k = suits[h]
            m = best(d,c)
            M = d if c==m else c
            deals[p] = swords[m]*suits[M] * sum(binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s > h == d > c != 5:
            k = suits[h]
            m = best(s,c)
            M = s if c == m else c
            deals[p] = suits[M]*swords[m]*sum(binomial(k,j) for j in (1,2))
        case (s,h,d,5) if s > h == d > c:
            k = suits[h]
            deals[p] = suits[5]*swords[s]*sum(binomial(k,j) for j in (1,2))

        case (s,h,d,c) if h > d == c:
            m = best(s,h)
            M = s if m == h else h
            k = suits[d]
            deals[p] = suits[M]*swords[m]* sum(binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s == d:
            k = suits[s]
            deals[p] = swords[c]*sum(binomial(k,j) for j in (1,2,2,3))
        case (s,h,d,c) if h == c:
            k = suits[h]
            deals[p] = sum(swords[s]*binomial(k,j) for j in (1,2,2,3))
        case _:
            print(f'{p} not matched')
classes = sum(deals.values())
for p, deal in sorted(deals.items(), key=lambda x:x[1], reverse=True):
    while len(p) < 4:
        p+= (0,)
    fout.write(f'{"-".join(str(x) for x in p):14} {"{:,}".format(deal):>18}\n')
    #fout.write(f'{str(p):14} {"{:,}".format(hands):>18} {hands/total:>9.5%}\n')

fout.write('\n{:,} equivalence classes\n'.format(classes))
fout.close()


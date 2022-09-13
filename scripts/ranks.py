# Spade suit with rank symmetry applied

from functools import reduce
from itertools import combinations
from math import factorial
from os import system

def bits(seq):
    return reduce(lambda x,y: x | (1<<(y-1)), seq, 0)

def choose(n,m):
    return factorial(n)//(factorial(m)*factorial(n-m))

count = lambda n : choose(13,n)

def flipped(ranks):
    low = 2
    high = 1 << 12
    while high > low:
        if (ranks & high) and not (ranks & low):
            return 1
        if (ranks & low) and not (ranks & high):
            return -1
        high >>= 1
        low <<= 1
    return 0 

for n in range(7, 14):
    eq = choose(6,n//2)    
    fout1 = open(f'../include/ranks{n}.h', 'w')
    fout3 = open(f'../include/equal{n}.h', 'w')
    fout1.write(f'#ifndef RANKS{n}_H\n')
    fout1.write(f'#define RANKS{n}_H\n')
    fout1.write('#include "types.h"\n')
    fout1.write(f'RankSet ranks{n}[{(count(n)+eq)//2}] = {{\n')
    for c in combinations(range(1,14), n):
        b = bits(c)
        flip = flipped(b)
        if flip == -1: continue
        if flip == 1:
            fout1.write(f'  {hex(b)},\n')
        elif flip == 0:
            fout3.write(f'  {hex(b)},\n')
    
    fout3.write('};')
    fout3.write('\n#endif\n')
    for fout in (fout1,fout3):
        fout.close()
    system(f"cat ../include/equal{n}.h>>../include/ranks{n}.h")
    system(f'rm ../include/equal{n}.h')





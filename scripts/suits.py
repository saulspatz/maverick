from itertools import combinations
from math import factorial
from functools import reduce

def bits(seq):
    return reduce(lambda x,y: x | (1<<y), seq, 0)

def count(n):
    return factorial(13)//(factorial(n)*factorial(13-n))

def typedefs(fout, n, suit):
    fout.write(f'#ifndef {suit.upper()}{n}_H\n')
    fout.write(f'#define {suit.upper()}{n}_H\n')
    fout.write('#include "card.h"\n')
    fout.write('typedef struct {\n')
    fout.write('  RankSet ranks;\n')
    fout.write(f'  Card cards[{n}];}} {suit}{n};\n')

for n in range(7,14):
    fstr = n*'{%d, 0},' 
    with open(f'../include/spades{n}.h', 'w') as fout:
        typedefs(fout, n, 'Spades')
        fout.write(f'Spades{n} spades{n}[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{bits(c)},{{{fstr % c}}}}},\n')
        assert idx ==count(n)-1
        fout.write('};')
        fout.write('\n#endif\n')

for n in range(4,14):
    fstr = n*'{%d, 1},'
    with open(f'../include/hearts{n}.h', 'w') as fout:
        typedefs(fout, n, 'Hearts')
        fout.write(f'Hearts{n} hearts{n}[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{bits(c)},{{{fstr % c}}}}},\n')
        assert idx ==count(n)-1
        fout.write('};')
        fout.write('\n#endif\n')

for n in range(1,9):
    fstr = n*'{%d, 2},' 
    with open(f'../include/diamonds{n}.h', 'w') as fout:
        typedefs(fout, n, 'Diamonds')
        fout.write(f'Diamonds{n} diamonds{n}[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{bits(c)},{{{fstr % c}}}}},\n')
        assert idx ==count(n)-1
        fout.write('};')
        fout.write('\n#endif')

for n in range(1,7):
    fstr = n*'{%d, 3},' 
    with open(f'../include/clubs{n}.h', 'w') as fout:
        typedefs(fout, n, 'Clubs')
        fout.write(f'Clubs{n} clubs{n}[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{bits(c)},{{{fstr % c}}}}},\n')
        assert idx ==count(n)-1
        fout.write('};')
        fout.write('\n#endif\n')

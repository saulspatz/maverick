from itertools import combinations
from math import factorial
from functools import reduce

def bits(seq):
    return reduce(lambda x,y: x | (1<<y), seq, 0)

def count(n):
    return factorial(13)//(factorial(n)*factorial(13-n))

def typedefs(fout, n):
    fout.write(f'#ifndef SUIT{n}_H\n')
    fout.write(f'#define SUIT{n}_H\n')
    fout.write('#include "types.h"\n')

for n in range(1,14):
    with open(f'../include/suit{n}.h', 'w') as fout:
        typedefs(fout, n)
        fout.write(f'RankSet suit{n}[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {bits(c)},\n')
        assert idx ==count(n)-1
        fout.write('};')
        fout.write('\n#endif\n')


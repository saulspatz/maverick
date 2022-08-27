from itertools import combinations
from math import factorial

def count(n):
    return factorial(13)//(factorial(n)*factorial(13-n))

def typedefs(fout, n, suit):
    if suit == 'Spades':
        fout.write('typedef struct {\n')
        fout.write('  unsigned char rank;\n')
        fout.write('  unsigned char suit;\n')
        fout.write('} Card;\n\n')
    fout.write(f'typedef Card {suit}[{n}];\n\n')
for n in range(1,14):
    fstr = n*'{%d, 0},' 
    with open(f'include/spades{n}.h', 'w') as fout:
        typedefs(fout, n, 'Spades')
        fout.write(f'int END0 = {count(n)-1};\n\n')
        fout.write(f'Spades spades[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{fstr % c}}},\n')
        assert idx ==count(n)-1
        fout.write('};')

for n in range(1,14):
    fstr = n*'{%d, 1},'
    with open(f'include/hearts{n}.h', 'w') as fout:
        typedefs(fout, n, 'Hearts')
        fout.write(f'int END1 = {count(n)-1};\n\n')
        fout.write(f'Hearts hearts[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{fstr % c}}},\n')
        assert idx ==count(n)-1
        fout.write('};')

for n in range(1,9):
    fstr = n*'{%d, 2},' 
    with open(f'include/diamonds{n}.h', 'w') as fout:
        typedefs(fout, n, 'Diamonds')
        fout.write(f'int END2 = {count(n)-1};\n\n')
        fout.write(f'Diamonds diamonds[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{fstr % c}}},\n')
        assert idx ==count(n)-1
        fout.write('};')

for n in range(1,7):
    fstr = n*'{%d, 3},' 
    with open(f'include/clubs{n}.h', 'w') as fout:
        typedefs(fout, n, 'Clubs')
        fout.write(f'int END3 = {count(n)-1};\n\n')
        fout.write(f'Clubs clubs[{count(n)}] = {{\n')
        for idx, c in enumerate(combinations(range(1,14), n)):
            fout.write(f'  {{{fstr % c}}},\n')
        assert idx ==count(n)-1
        fout.write('};')


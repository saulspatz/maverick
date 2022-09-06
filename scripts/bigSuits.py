from itertools import combinations

for s in range(7, 14):
    with open(f'../include/spades{s}.h','w') as fout:
        fout.write(f'#ifndef SPADES{s}_H\n')
        fout.write(f'#define SPADES{s}_H\n')
        fout.write('#include "types.h"\n')
        fout.write(f'Cards{s} spades{s}[] = {{\n')
        for c in combinations(range(1,14),s):
            fout.write('  {')
            for x in c:
                fout.write(f'{{{x}, 3}},')
            fout.write('},\n')
        fout.write('};\n')
        fout.write('#endif')

for h in range(4, 13):
    with open(f'../include/hearts{h}.h','w') as fout:
        fout.write(f'#ifndef HEARTS{h}_H\n')
        fout.write(f'#define HEARTS{h}_H\n')
        fout.write('#include "types.h"\n')
        fout.write(f'Cards{h} hearts{h}[] = {{\n')
        for c in combinations(range(1,14),h):
            fout.write('  {')
            for x in c:
                fout.write(f'{{{x}, 2}},')
            fout.write('},\n')
        fout.write('};\n')
        fout.write('#endif')

for d in range(9):
    with open(f'../include/diamonds{d}.h','w') as fout:
        fout.write(f'#ifndef DIAMONDS{d}_H\n')
        fout.write(f'#define DIAMONDS{d}_H\n')
        fout.write('#include "types.h"\n')
        fout.write(f'Cards{d} diamonds{d}[] = {{\n')
        for c in combinations(range(1,14),d):
            fout.write('  {')
            for x in c:
                fout.write(f'{{{x}, 1}},')
            fout.write('},\n')
        fout.write('};\n')
        fout.write('#endif')

for c in range(7):
    with open(f'../include/clubs{c}.h','w') as fout:
        fout.write(f'#ifndef CLUBS{c}_H\n')
        fout.write(f'#define CLUBS{c}_H\n')
        fout.write('#include "types.h"\n')
        fout.write(f'Cards{c} clubs{c}[] = {{\n')
        for z in combinations(range(1,14),c):
            fout.write('  {')
            for x in z:
                fout.write(f'{{{x}, 0}},')
            fout.write('},\n')
        fout.write('};\n')
        fout.write('#endif')

 

'''
Generate programs to count deals in Maverick solitaire,
by generating the equivalence classes one-by-one and
mutliplying by the appropriate factors.

There are 10 patterns that the distribution can have.
This script deals with the 3 patterns where no two non-void
suits are of the same length.  See hands.py for the
case of equal lengths. 
'''

from math import factorial

def choose(n,m):
    return factorial(n)//(factorial(m)*factorial(n-m))

count = lambda n: choose(13,n)

def genhands(s, h, d=0, c=0):
    with open(f'../src/dist{s}{h}{d}{c}.c', 'w') as fout:
        eq = choose(6,s//2)   # number of self-symmetric spade suits
        fout.write('#include <stdio.h>\n')
        fout.write('#include "types.h"\n')
        name = f'dist{s}{h}{d}{c}'
        fout.write(f'\nvoid {name}() {{\n')
        fout.write(f'  extern RankSet ranks{s}[];\n')
        fout.write(f'  extern RankSet suit{h}[];\n')
        fout.write(f'  extern Cards{s} swords{s}[];\n')
        fout.write(f'  extern Cards{h} hearts{h}[];\n')
        if d:
            fout.write(f'  extern RankSet suit{d}[];\n')
        if c:
            fout.write(f'  extern RankSet suit{c}[];\n')
        fout.write(f'  RankSet *SPADES_START = ranks{s};\n')
        fout.write(f'  RankSet *HEARTS_START = suit{h};\n')
        if d:
            fout.write(f'  extern Cards{d} diamonds{d}[];\n')
            fout.write(f'  RankSet *DIAMONDS_START = suit{d};\n')
        if c:
            fout.write(f'  extern Cards{c} clubs{c}[];\n')
            fout.write(f'  RankSet *CLUBS_START = suit{c};\n')
        fout.write(f'  RankSet *SPADES_END  = SPADES_START + {(count(s)+eq)//2};\n')
        fout.write(f'  RankSet *SYM_START = SPADES_START +{(count(s)-eq)//2};\n')
        fout.write(f'  RankSet *HEARTS_END  = HEARTS_START + {count(h)-1};\n')
        if d:
            fout.write(f'  RankSet *DIAMONDS_END  = DIAMONDS_START + {count(d)-1};\n')
        if c:
            fout.write(f'  RankSet *CLUBS_END  = CLUBS_START + {count(c)-1};\n')
        fout.write('  RankSet *spades = SPADES_START;\n')
        if d:
            fout.write('  RankSet *hearts = HEARTS_START;\n')
        else:
            fout.write('  RankSet *hearts = HEARTS_START-1;\n')
        if d and c:
            fout.write('  RankSet *diamonds = DIAMONDS_START;\n')
        elif d:
            fout.write('  RankSet *diamonds = DIAMONDS_START-1;\n')
        if c:
            fout.write('  RankSet *clubs = CLUBS_START-1;\n')
        fout.write('  int factor;\n')
        fout.write('  long total = 0L;\n')
        fout.write('  RankSet Phony = 0;\n')

        if s > h > d > c > 0:                                   #abcd
            fout.write('  while(1) {\n')
            fout.write('    if (clubs < CLUBS_END) {\n')
            fout.write('      clubs++;\n')
            fout.write('      factor = spades < SYM_START ? 48 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (diamonds < DIAMONDS_END) {\n')
            fout.write('      diamonds++;\n')
            fout.write('      clubs = CLUBS_START;\n')
            fout.write('      factor = spades < SYM_START ? 48 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (hearts < HEARTS_END) {\n')
            fout.write('      hearts++;\n')
            fout.write('      clubs = CLUBS_START;\n') 
            fout.write('      diamonds = DIAMONDS_START;\n')
            fout.write('      factor = spades < SYM_START ? 48 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    };\n') 

            fout.write('    if (spades < SPADES_END) {\n')
            fout.write('      spades++;\n')
            fout.write('      clubs = CLUBS_START;\n')
            fout.write('      diamonds = DIAMONDS_START;\n') 
            fout.write('      hearts = HEARTS_START;\n')
            fout.write('      factor = spades < SYM_START ? 48 : 24;\n')
            fout.write('    } else break;\n') 

        if s > h > d > c == 0:                         # abc
            fout.write('  while(1) {\n')
            fout.write('    if (diamonds < DIAMONDS_END) {\n')
            fout.write('      diamonds++;\n')
            fout.write('      factor = spades < SYM_START ? 48 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (hearts < HEARTS_END) {\n')
            fout.write('      hearts++;\n')
            fout.write('      diamonds = DIAMONDS_START;\n')
            fout.write('      factor = spades < SYM_START ? 48 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (spades < SPADES_END) {\n')
            fout.write('      spades++;\n')
            fout.write('      diamonds = DIAMONDS_START;\n')
            fout.write('      hearts= HEARTS_START;\n')
            fout.write('      factor = spades < SYM_START ? 48 : 24;\n')
            fout.write('    } else break;\n')

        if s > h and d == c == 0:
            fout.write('  while(1) {\n')                                  # ab
            fout.write('    if (hearts < HEARTS_END) {\n')
            fout.write('      hearts++;\n')
            fout.write('      factor = spades < SYM_START ? 24 : 12;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (spades < SPADES_END) {\n')
            fout.write('      spades++;\n')
            fout.write('      hearts = HEARTS_START;\n')
            fout.write('      factor = spades < SYM_START ? 24 : 12;\n')
            fout.write('    } else break;\n')
            
        fout.write('\ncompute:\n\n    total += factor;\n')
        fout.write('    Phony |= *spades & *hearts')
        if d:
            fout.write(' & *diamonds')
        if c:
            fout.write(' & *clubs')
        fout.write(';\n')       
        fout.write('  }\n\n')
        fout.write(f'  printf("{s}-{h}-{d}-{c}: %ld\\n", total);\n')
        fout.write(f'  fprintf(stderr, "%d", Phony);\n')
        fout.write('}')    
        

genhands(13, 9, 2, 1)
genhands(13,10,2)
genhands(13,12)



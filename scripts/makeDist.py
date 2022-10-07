'''
Generate programs to count deals in Maverick solitaire,
by generating the equivalence classes one-by-one and
mutliplying by the appropriate factors.

There are 9 patterns that the distribution can have, since
don't consider 13-12-0-0, which is always solvable.  Some
of the patterns break into two cases, depending on whether or
not the shortes suit has exactly 5 cards. 
'''

from partitions import partitions, product, binomial
import argparse

count = {n: binomial(13,n) for n in range(14)}
equal = {n: binomial(6, n//2) for n in range(14)}
swords = {n: (count[n]+equal[n])//2 for n in range(14)}
syms = {n: (count[n]-equal[n])//2 for n in range(14)}

def best(*args):
    return min(args, key= lambda x: abs(13-2*x))

def dominatedSuit(name, n, fout):
    fout.write(f'  extern RankSet suit{n}[];\n')
    fout.write(f'  RankSet *{name}_START = suit{n};\n')

def plainSuit(name, n, fout):
    fout.write(f'  extern RankSet suit{n}[];\n')
    fout.write(f'  RankSet *{name}_START = suit{n};\n')
    fout.write(f'  RankSet *{name}_END = {name}_START + {count[n]-1};\n\n')

def symSuit(name, n, fout):
    fout.write(f'  extern RankSet ranks{n}[];\n')
    fout.write(f'  RankSet *{name}_START = ranks{n};\n')
    fout.write(f'  RankSet *{name}_END = {name}_START + {swords[n]-1};\n')
    fout.write(f'  RankSet *SYM_START = {name}_START + {syms[n]};\n\n')

def start(s,h,d,c,fout):
    fout.write('  RankSet *spades = SPADES_START;\n')
    fout.write('  RankSet *hearts = HEARTS_START;\n')
    if c:
        fout.write('  RankSet *diamonds = DIAMONDS_START;\n')
        fout.write('  RankSet *clubs = CLUBS_START-1;\n')
    else:
        fout.write('  RankSet *diamonds = DIAMONDS_START-1;\n\n')
    fout.write('  int factor;\n')
    fout.write('  unsigned long exhaustC = 0L;  // classes\n')
    fout.write('  unsigned long heurC = 0L;\n')
    fout.write('  unsigned long skipC = 0L;\n')
    fout.write('  unsigned long exhaustD = 0L;   // deals\n')
    fout.write('  unsigned long heurD = 0L;\n')
    fout.write('  unsigned long skipD = 0L;\n')
    fout.write('  unsigned long solutions = 0L;\n')
    fout.write('  double begin, end;\n')
    fout.write('  begin = clock();\n'  )

def prolog(fout):
    fout.write('#include <stdio.h>\n')
    fout.write('#include <time.h>\n')
    fout.write('#include "types.h"\n')
    fout.write('\nextern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);\n')

def skip(c, d, fout):
    suit = 'clubs' if c==5 else 'diamonds'
    if (c == 0):
        end = 'DIAMONDS_END'
    elif (d == 5):
        end = 'diamonds - 1'
    else: 
        end = 'CLUBS_END'
    if not (c == d == 5):
        fout.write('    if (result == 5) {\n')
        fout.write(f'      int skipped = {end} - {suit};\n')
        fout.write('      skipC += skipped;\n')
        fout.write('      skipD += factor*skipped;\n')
        fout.write('      solutions += (skipped+1)*factor;\n')
        fout.write(f'      {suit} = {end};\n')    
        fout.write('    }\n')
    else:
        fout.write('    if (result == 5) {\n')
        fout.write(f'      int skipped = {end} - {suit};\n')
        fout.write('       if skipped >= 0 {\n')
        fout.write('         skipC += skipped;\n')
        fout.write('         skipD += factor*skipped;\n')
        fout.write('         solutions += (skipped+1)*factor;\n')
        fout.write(f'        {suit} = {end};\n')    
        fout.write('       }\n')
        fout.write('    else result = 1;  // ignore flush\n')
        fout.write('    }\n')


def epilog(fout, title):
    fout.write('    if (result == 1)')
    fout.write('      solutions += factor;\n')
    fout.write('  }\n')
    fout.write('  end = clock();\n')
    fout.write('  double time = (end-begin)/CLOCKS_PER_SEC;\n')
    fout.write('  FILE* out = fopen("counts2.log", "a");\n')
    fout.write('  char buffer[256];\n')
    fout.write('  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\\n",\n')
    fout.write(f'       "{title}", exhaustC, heurC, skipC, exhaustD, heurD, skipD, solutions, time);\n')
    fout.write('  fputs(buffer, out);\n')
    fout.write('  fclose(out);\n')
    fout.write('}')

def genHand_abc(s, h, d, c=0):
    with open(f'../src/dist_{s}_{h}_{d}_0.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        fout.write(f'\nvoid {name}() {{\n')
        m = best(s,h,d) if d != 5 else best(s,h)
        
        if m == s:
            symSuit('SPADES', s, fout)
            plainSuit('HEARTS',h,fout)
            plainSuit('DIAMONDS',d,fout)
            sym = 'spades'
        elif m == h:
            plainSuit('SPADES', s, fout)
            symSuit('HEARTS',h,fout)
            plainSuit('DIAMONDS',d,fout)
            sym = 'hearts'
        else:
            plainSuit('SPADES', s, fout)
            plainSuit('HEARTS',h,fout)
            symSuit('DIAMONDS',d,fout)
            sym = 'diamonds'
        start(s,h,d,0,fout)
        fout.write('  while(1) {\n')
        fout.write('    if (diamonds < DIAMONDS_END) {\n')
        fout.write('      diamonds++;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n')
        
        fout.write('    else if (hearts < HEARTS_END) {\n')
        fout.write('      hearts++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n')                  

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      hearts= HEARTS_START;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n') 
        fout.write('    else break;\n')

        fout.write('    int result = solver(*spades, *hearts, *diamonds, 0);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (d==5): skip(0, d, fout)
        
        epilog(fout, title)

def genHand_abcd(s,h,d,c):
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        name = f'dist_{s}_{h}_{d}_{c}'
        title =f'{s}-{h}-{d}-{c}'
        fout.write(f'\nvoid {name}() {{\n')
        m = best(s,h,d,c) if c != 5 else best(s,h,d)
        if m == s:
            symSuit('SPADES', s, fout)
            plainSuit('HEARTS',h,fout)
            plainSuit('DIAMONDS',d,fout)
            plainSuit('CLUBS', c, fout)
            sym = 'spades'
        elif m == h:
            plainSuit('SPADES', s, fout)
            symSuit('HEARTS',h,fout)
            plainSuit('DIAMONDS',d,fout)
            plainSuit('CLUBS', c, fout)
            sym = 'hearts'
        elif m == d:
            plainSuit('SPADES', s, fout)
            plainSuit('HEARTS',h,fout)
            symSuit('DIAMONDS',d,fout)
            plainSuit('CLUBS', c, fout)
            sym = 'diamonds'
        else:
            plainSuit('SPADES', s, fout)
            plainSuit('HEARTS',h,fout)
            plainSuit('DIAMONDS',d,fout)
            symSuit('CLUBS', c, fout)
            sym = 'clubs'
        start(s,h,d,c,fout)
        fout.write('  while(1) {\n')
        fout.write('    if (clubs < CLUBS_END) {\n')
        fout.write('      clubs++;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n')

        fout.write('    else if (diamonds < DIAMONDS_END) {\n')
        fout.write('      diamonds++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < HEARTS_END) {\n')
        fout.write('      hearts++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n') 

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      hearts= HEARTS_START;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n') 
        fout.write('    else break;\n')

        fout.write('    int result = solver(*spades, *hearts, *diamonds, *clubs);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')

        epilog(fout, title)
        if (c==5): skip(c, d, fout)

def genHand_aab(s,h,d, c=0):
    assert h == s
    with open(f'../src/dist_{s}_{h}_{d}_0.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        fout.write(f'\nvoid {name}() {{\n')
        plainSuit('SPADES', s, fout)
        dominatedSuit('HEARTS', h, fout)
        symSuit('DIAMONDS', d, fout)
        sym = 'diamonds'
        start(s,h,d,0,fout)

        fout.write('  while (1) {\n')
        fout.write('    if (diamonds < DIAMONDS_END) {\n')
        fout.write('      diamonds++;\n')
        fout.write('    factor = (hearts == spades) ? 12 : 24;\n')
        fout.write(f'    if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < spades) {\n')
        fout.write('      hearts++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      factor = (hearts == spades) ? 12 : 24;\n')
        fout.write(f'    if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n') 
        fout.write('      hearts = HEARTS_START;\n')
        fout.write(f'      factor = {sym} < SYM_START ? 48 : 24;\n')
        fout.write('    }\n')
        fout.write('    else break;\n')

        fout.write('    int result = solver(*spades, *hearts, *diamonds, 0);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (d==5): skip(0, d, fout)

        epilog(fout, title)

def genHand_abb(s,h,d,c=0):
    assert h==d
    with open(f'../src/dist_{s}_{h}_{d}_0.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        fout.write(f'\nvoid {name}() {{\n')
        symSuit('SPADES',s,fout)
        plainSuit('HEARTS', h, fout)
        dominatedSuit('DIAMONDS',d,fout)
        sym = 'spades'
        start(s,h,d,0,fout)

        fout.write('  while (1) {\n')
        fout.write('    if (diamonds < hearts) {\n')
        fout.write('      diamonds++;\n')
        fout.write('      factor = (diamonds == hearts) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < HEARTS_END) {\n')
        fout.write('      hearts++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write(f'      factor = ({sym} < SYM_START) ? 48 : 24;\n')
        fout.write('    }\n')

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      hearts = HEARTS_START;\n')
        fout.write(f'     factor = ({sym} < SYM_START) ? 24 : 12;\n')
        fout.write('    }\n')
        fout.write('    else break;\n')

        fout.write('    int result = solver(*spades, *hearts, *diamonds, 0);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (d==5): skip(0, d, fout)

        epilog(fout, title)

def genHand_aabc(s,h,d,c):
    assert s == h
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        name = f'dist_{s}_{h}_{d}_{c}'
        title = f'{s}-{h}-{d}-{c}'
        fout.write(f'\nvoid {name}() {{\n')
        m = best(d,c) if c!=5 else d
        plainSuit('SPADES', s, fout)
        dominatedSuit('HEARTS', h, fout)
        if m == d:
            symSuit('DIAMONDS', d,  fout)
            plainSuit('CLUBS', c, fout)
            sym = 'diamonds'
        else:
            plainSuit('DIAMONDS', d,  fout)
            symSuit('CLUBS', c, fout)
            sym = 'clubs'            
        start(s,h,d,c,fout)

        fout.write('  while (1) {\n')
        fout.write('    if (clubs < CLUBS_END) {\n')
        fout.write('      clubs++;\n')
        fout.write('      factor = (hearts==spades) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (diamonds < DIAMONDS_END) {\n')
        fout.write('      diamonds++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      factor = (hearts==spades) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < spades) {\n')
        fout.write('      hearts++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      factor = (hearts==spades) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      diamonds = DIAMONDS_START;\n') 
        fout.write('      hearts = HEARTS_START;\n')
        fout.write(f'      factor = ({sym} < SYM_START) ? 48 : 24;\n')
        fout.write('    }\n')
        fout.write('    else break;\n')

        fout.write('    int result = solver(*spades, *hearts, *diamonds, *clubs);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHand_abbc(s,h,d,c):
    assert h==d
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        fout.write(f'\nvoid {name}() {{\n')
        m = best(s,c) if c!=5 else s
        plainSuit('HEARTS', h, fout)
        dominatedSuit('DIAMONDS', d, fout)
        if m == s:
            symSuit('SPADES', s,  fout)
            plainSuit('CLUBS', c, fout)
            sym = 'spades'
        else:
            plainSuit('SPADES', s,  fout)
            symSuit('CLUBS', c, fout)
            sym = 'clubs'            
        start(s,h,d,c,fout)

        fout.write('  while(1) {\n')
        fout.write('    if (clubs < CLUBS_END) {\n')
        fout.write('      clubs++;\n')
        fout.write('      factor = (diamonds==hearts) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (diamonds < hearts) {\n')
        fout.write('      diamonds++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      factor = (diamonds==hearts) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < HEARTS_END) {\n')
        fout.write('      hearts++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      factor = (diamonds==hearts) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')   

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      clubs = CLUBS_START;\n') 
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      hearts = HEARTS_START;\n')
        fout.write(f'      factor = ({sym} < SYM_START) ? 24 : 12;\n')
        fout.write('    }\n')     
        fout.write('    else break;\n') 

        fout.write('    int result = solver(*spades, *hearts, *diamonds, *clubs);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHands_abcc(s,h,d,c):
    assert d == c
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        fout.write(f'\nvoid {name}() {{\n')
        m = best(s,h)
        dominatedSuit('CLUBS', c, fout)
        plainSuit('DIAMONDS', d, fout)
        if m == s:
            symSuit('SPADES', s,  fout)
            plainSuit('HEARTS', h, fout)
            sym = 'spades'
        else:
            plainSuit('SPADES', s,  fout)
            symSuit('HEARTS', h, fout)
            sym = 'hearts'            
        start(s,h,d,c,fout)

        fout.write('  while(1) {\n')
        fout.write('    if (clubs < diamonds) {\n')
        fout.write('      clubs++;\n')
        fout.write('      factor = (diamonds==clubs) ? 12 : 24;\n')
        fout.write(f'      if ({sym} < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (diamonds < DIAMONDS_END) {\n')
        fout.write('      diamonds++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write(f'      factor = ({sym} < SYM_START) ? 48 : 24;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < HEARTS_END) {\n')
        fout.write('      hearts++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write(f'      factor = ({sym} < SYM_START) ? 24 : 12;\n')
        fout.write('    }\n')   

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      clubs = CLUBS_START;\n') 
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      hearts = HEARTS_START;\n')
        fout.write(f'      factor = ({sym} < SYM_START) ? 24 : 12;\n')
        fout.write('    }\n')     
        fout.write('    else break;\n') 

        fout.write('    int result = solver(*spades, *hearts, *diamonds, *clubs);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHands_aaab(s,h,d,c):
    assert s == h == d
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        name = f'dist_{s}_{h}_{d}_{c}'
        title = f'{s}-{h}-{d}-{c}'
        fout.write(f'\nvoid {name}() {{\n')
        plainSuit('SPADES', s, fout)
        dominatedSuit('HEARTS', h, fout)
        dominatedSuit('DIAMONDS', d,  fout)
        symSuit('CLUBS', c, fout)           
        start(s,h,d,c,fout)

        fout.write('  while(1) {\n')
        fout.write('    if (clubs < CLUBS_END) {\n')
        fout.write('      clubs++;\n')
        fout.write('      if (spades==diamonds) factor = 4;\n')
        fout.write('      else if (spades==hearts) factor = 12;\n')
        fout.write('      else if (hearts==diamonds) factor = 12;\n')
        fout.write('      else factor = 24;\n')
        fout.write('      if (clubs < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (diamonds < hearts) {\n')
        fout.write('      diamonds++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      if (spades==diamonds) factor = 4;\n')
        fout.write('      else if (spades==hearts) factor = 12;\n')
        fout.write('      else if (hearts==diamonds) factor = 12;\n')
        fout.write('      else factor = 24;\n')
        fout.write('      if (clubs < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < spades) {\n')
        fout.write('      hearts++;\n')
        fout.write('      diamonds = DIAMONDS_START;\n') 
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      factor = (hearts == spades) ? 12 : 24;\n')
        fout.write('      if (clubs < SYM_START) factor *= 2;\n')
        fout.write('    }\n')
          
        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      hearts = HEARTS_START;\n') 
        fout.write('      diamonds  = DIAMONDS_START;\n') 
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      factor = (clubs < SYM_START) ? 24 : 12;\n')
        fout.write('    }\n')
        fout.write('    else break;\n')

        fout.write('    int result = solver(*spades, *hearts, *diamonds, *clubs);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)
    

def genHands_abbb(s,h,d,c):
    assert h==d==c
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        name = f'dist_{s}_{h}_{d}_{c}'
        title = f'{s}-{h}-{d}-{c}'
        fout.write(f'\nvoid {name}() {{\n')
        symSuit('SPADES', s, fout)
        plainSuit('HEARTS', h, fout)
        dominatedSuit('DIAMONDS', d,  fout)
        dominatedSuit('CLUBS', c, fout)               
        start(s,h,d,c,fout)

        fout.write('  while(1) {\n')
        fout.write('    if (clubs < diamonds) {\n')
        fout.write('      clubs++;\n')
        fout.write('      if (hearts==clubs) factor = 4;\n')
        fout.write('      else if (clubs==diamonds) factor = 12;\n')
        fout.write('      else if (hearts==diamonds) factor = 12;\n')
        fout.write('      else factor = 24;\n')
        fout.write('      if (spades < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (diamonds < hearts) {\n')
        fout.write('      diamonds++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      factor = (hearts == diamonds) ? 12 : 24;\n')
        fout.write('      if (spades < SYM_START) factor *= 2;\n')
        fout.write('    }\n')

        fout.write('    else if (hearts < HEARTS_END) {\n')
        fout.write('      hearts++;\n')
        fout.write('      clubs = CLUBS_START;\n')
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      factor = 12;\n')
        fout.write('      if (spades < SYM_START) factor *= 2;\n')
        fout.write('    }\n') 

        fout.write('    else if (spades < SPADES_END) {\n')
        fout.write('      spades++;\n')
        fout.write('      clubs = CLUBS_START;\n') 
        fout.write('      diamonds = DIAMONDS_START;\n')
        fout.write('      hearts = HEARTS_START;\n')
        fout.write('      factor = (spades < SYM_START) ? 8 : 4;\n')
        fout.write('    }\n')
        fout.write('    else break;\n')

        fout.write('    int result = solver(*spades, *hearts, *diamonds, *clubs);\n')
        fout.write('    exhaustC += 1;\n')
        fout.write('    exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHand(p):
    match p:
        case (10,5,5,5) | (10,10,5) | (13,12) | (12,12,1) | (13,6,6) | (13,11,1) | (13,7,5):
            return
        case (s,h,d,0) if s > h > d:
            genHand_abc(*p)
        case (s,h,d,c) if s > h > d > c != 0:
            genHand_abcd(*p)
        case (s,h,d,0) if h==s > d:
            genHand_aab(*p)
        case (s,h,d,0) if h == d:
            genHand_abb(*p)
        case (s,h,d,c) if s==h>d>c!=0:
            genHand_aabc(*p)
        case (s,h,d,c) if s > h == d > c != 0:
            genHand_abbc(*p)
        case (s,h,d,c) if h > d == c:
            genHands_abcc(*p)
        case (s,h,d,c) if s == d:
            genHands_aaab(*p)
        case (s,h,d,c) if h == c:
            genHands_abbb(*p)
        case _:
            print(f'{p} not matched')        

def main():
    parser = argparse.ArgumentParser(description='Create dists from makeDist.txt')
    parser.add_argument('--all', action='store_true', help='Create all dists')
    args = parser.parse_args()
    if args.all:
        for p in partitions(25, 4, 13):
            genHand(p)
    else:
        text = open('makeDist.txt').readlines()
        for line in text:
            line = line.strip()
            p = tuple(int(x) for x in line.split())
            genHand(p)

if __name__ == '__main__':
    main()

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
    fout.write(f'  RankSet *{name}_END = suit{n} + {count[n]-1};\n\n')

def symSuit(name, n, fout):
    fout.write(f'  extern RankSet ranks{n}[];\n')
    fout.write(f'  RankSet *{name}_START = ranks{n};\n')
    fout.write(f'  RankSet *{name}_END = ranks{n} + {swords[n]-1};\n')
    fout.write(f'  RankSet *SYM_START = ranks{n} + {syms[n]};\n\n')

def start(s,h,d,c,fout):
    fout.write('  RankSet *spades = SPADES_START;\n')
    fout.write('  RankSet *hearts = HEARTS_START;\n')
    if c:
        fout.write('  RankSet *diamonds = DIAMONDS_START;\n')
        fout.write('  RankSet *clubs = CLUBS_START-1;\n')
    else:
        fout.write('  RankSet *diamonds = DIAMONDS_START-1;\n\n')
    fout.write('  State state;\n')
    fout.write('  int factor;\n')
    fout.write('  double begin, end;\n')
    fout.write('''
  // check whether to continue an interrupted run
  int completed = restoreState(&state, SPADES_END);
  if (completed) return;\n\n''')
    if c:
        fout.write('  clubs = CLUBS_START + state.cc;\n')
    fout.write('''
  diamonds = DIAMONDS_START + state.dd;
  hearts = HEARTS_START + state.hh;
  spades = SPADES_START + state.ss;
     
  signal(SIGALRM,sig_handler); // Register signal handler
  alarm(interval);             // schedule a backup in an hour
  begin = clock();\n''')

def prolog(fout):
    fout.write('#include <stdio.h>\n')
    fout.write('#include <time.h>\n')
    fout.write('#include <signal.h>\n')
    fout.write('#include <unistd.h>\n')
    fout.write('#include "types.h"\n')
    fout.write('\nextern int solver(RankSet spades, RankSet hearts,RankSet diamonds, RankSet clubs);\n')
    fout.write('''
typedef struct {
  unsigned long exhaustC;  // classes
  unsigned long heurC;
  unsigned long skipC;
  unsigned long exhaustD;   // deals
  unsigned long heurD;
  unsigned long skipD;
  unsigned long solutions;
  double   elapsed;
  unsigned long cc;         // "loop counters"
  unsigned long dd;
  unsigned long hh;
  unsigned long ss; 
} State;
int backup = 0;
int interval = 3600;

void sig_handler(int signum){
  if (signum == SIGALRM) {
    backup = 1;
    alarm(interval);  // Schedule a new alarm after an hour
  }
}''')
    
    
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
        fout.write('      state.skipC += skipped;\n')
        fout.write('      state.skipD += factor*skipped;\n')
        fout.write('      state.solutions += (skipped+1)*factor;\n')
        fout.write(f'      {suit} = {end};\n')    
        fout.write('    }\n')
    else:
        fout.write('    if (result == 5) {\n')
        fout.write(f'      int skipped = {end} - {suit};\n')
        fout.write('      if (skipped >= 0) {\n')
        fout.write('        state.skipC += skipped;\n')
        fout.write('        state.skipD += factor*skipped;\n')
        fout.write('        state.solutions += (skipped+1)*factor;\n')
        fout.write(f'        {suit} = {end};\n')    
        fout.write('       }\n')
        fout.write('    else result = 1;  // ignore flush\n')
        fout.write('    }\n')


def epilog(fout, title):
    fout.write(f'''
    if (result == 1) state.solutions += factor;
    if (backup) {{
        end = clock();
        state.elapsed += (end-begin)/CLOCKS_PER_SEC;
        saveState(&state);
        begin = clock();        
      }}
  }}
  end = clock();
  state.elapsed += (end-begin)/CLOCKS_PER_SEC;
  FILE* out = fopen("counts1.log", "a");
  char buffer[256];
  sprintf(buffer,"%-9s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %.2f\\n",  
        "{title}", 
        state.exhaustC, 
        state.heurC, 
        state.skipC, 
        state.exhaustD, 
        state.heurD, 
        state.skipD, 
        state.solutions, 
        state.elapsed);
  fputs(buffer, out);
  fclose(out);
  saveState(&state);  // last backup shows calculation complete
}}\n''')

def backup(fout, name, c):
    fout.write('''
RankSet *spades;
RankSet *hearts;
RankSet *diamonds;
''')
    if c: fout.write('RankSet *clubs;\n')
    fout.write('int restoreState(State *state, RankSet *stop) {\n')
    fout.write('  FILE *saved = NULL;\n')
    fout.write(f'  if (access("{name}.sav1", F_OK)==0)\n')
    fout.write(f'    saved = fopen("{name}.sav1", "r");\n')
    fout.write(f'  else if (access("{name}.sav2", F_OK)==0)\n')
    fout.write(f'    saved = fopen("{name}.sav2", "r");\n')
    fout.write('''  if (saved) {
    fscanf(saved, "%lu, %lu, %lu, %lu", &state->cc, &state->dd, &state->hh, &state->ss);
    fscanf(saved, "%lu %lu %lu %lu %lu %lu %lu %lf", 
                  &state->exhaustC, &state->heurC, &state->skipC, 
                  &state->exhaustD, &state->heurD, &state->skipD, 
                  &state->solutions, &state->elapsed);
    if (spades >= stop)
      return 1;      //calculation already completed
  }
  else {             // initial run
    state->exhaustC = 0L;
    state->exhaustD = 0L;
    state->heurC = 0L;
    state->heurD = 0L;
    state->skipC = 0L;
    state->skipD = 0L;
    state->solutions = 0L;
    state->elapsed = 0;\n''')
    if c: 
        fout.write('    state->cc =-1;\n')
        fout.write('    state->dd = 0;\n')
    else:
        fout.write('    state->dd = -1;\n')
    fout.write('''    state->hh = 0;
    state->ss = 0;
  }   
  return 0;
}\n\n''')
    fout.write('void saveState(State *state) {\n')
    fout.write(f'if (access("{name}",  F_OK)==0)  // 2nd generation backup exists\n')
    fout.write(f'    unlink("{name}.sav2");\n')
    fout.write(f'  if (access("{name}.sav1", F_OK)==0)  // 1st generation backup exists\n')
    fout.write(f'    rename("{name}.sav1", "{name}.sav2");\n')
    fout.write(f'  FILE *back = fopen("{name}.sav1", "w");\n')
    fout.write('  fprintf(back, "%lu %lu %lu %lu\\n",\n')
    if c:
        fout.write('      clubs-CLUBS_START,\n')
    else:
        fout.write('      0L,\n')
    fout.write('''
      diamonds-DIAMONDS_START, 
      hearts-HEARTS_START,
      spades-SPADES_START);
  
  fprintf(back, "%lu %lu %lu %lu %lu %lu %lu %.2f\\n", 
      state->exhaustC, 
      state->heurC, 
      state->skipC,
      state->exhaustD,
      state->heurD, 
      state->skipD, 
      state->solutions, 
      state->elapsed);
  fclose(back);
  backup = 0;
}
\n''')

def genHand_abc(s, h, d, c=0):
    with open(f'../src/dist_{s}_{h}_{d}_0.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
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
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (d==5): skip(0, d, fout)
        
        epilog(fout, title)

def genHand_abcd(s,h,d,c):
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        name = f'dist_{s}_{h}_{d}_{c}'
        title =f'{s}-{h}-{d}-{c}'
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
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')

        epilog(fout, title)
        if (c==5): skip(c, d, fout)

def genHand_aab(s,h,d, c=0):
    assert h == s
    with open(f'../src/dist_{s}_{h}_{d}_0.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        plainSuit('SPADES', s, fout)
        dominatedSuit('HEARTS', h, fout)
        symSuit('DIAMONDS', d, fout)
        sym = 'diamonds'
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (d==5): skip(0, d, fout)

        epilog(fout, title)

def genHand_abb(s,h,d,c=0):
    assert h==d
    with open(f'../src/dist_{s}_{h}_{d}_0.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        symSuit('SPADES',s,fout)
        plainSuit('HEARTS', h, fout)
        dominatedSuit('DIAMONDS',d,fout)
        sym = 'spades'
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (d==5): skip(0, d, fout)

        epilog(fout, title)

def genHand_aabc(s,h,d,c):
    assert s == h
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        name = f'dist_{s}_{h}_{d}_{c}'
        title = f'{s}-{h}-{d}-{c}'
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
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHand_abbc(s,h,d,c):
    assert h==d
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
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
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')           
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHands_abcc(s,h,d,c):
    assert d == c
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
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
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')       
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHands_aaab(s,h,d,c):
    assert s == h == d
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        name = f'dist_{s}_{h}_{d}_{c}'
        title = f'{s}-{h}-{d}-{c}'
        plainSuit('SPADES', s, fout)
        dominatedSuit('HEARTS', h, fout)
        dominatedSuit('DIAMONDS', d,  fout)
        symSuit('CLUBS', c, fout)
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')           
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)
    

def genHands_abbb(s,h,d,c):
    assert h==d==c
    with open(f'../src/dist_{s}_{h}_{d}_{c}.c', 'w') as fout:
        prolog(fout)
        title = f'{s}-{h}-{d}-{c}'
        name = f'dist_{s}_{h}_{d}_{c}'
        symSuit('SPADES', s, fout)
        plainSuit('HEARTS', h, fout)
        dominatedSuit('DIAMONDS', d,  fout)
        dominatedSuit('CLUBS', c, fout)  
        backup(fout, name, c)
        fout.write(f'\nvoid {name}() {{\n')             
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
        fout.write('    state.exhaustC += 1;\n')
        fout.write('    state.exhaustD += factor;\n')
        if (c==5): skip(c, d, fout)

        epilog(fout, title)

def genHand(p):
    match p:
        case (10,5,5,5) | (10,10,5,0) | (13,12,0,0) | (12,12,1,0) | (13,6,6,0) | (13,11,1,0) | (13,7,5,0):
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

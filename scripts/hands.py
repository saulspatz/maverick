'''
Generate programs to count deals in Maverick solitaire,
by generating the equivalence classes one-by-one and
mutliplying by the appropriate factors.

There are 10 patterns that the distribution can have.
'''

from math import factorial

def count(n):
    return factorial(13)//(factorial(n)*factorial(13-n))

def genhands(s, h, d=0, c=0):
    with open(f'../src/dist{s}{h}{d}{c}.c', 'w') as fout:
        fout.write('#include <stdio.h>\n')
        fout.write('#include "types.h"\n')
        fout.write(f'extern Spades{s} spades{s}[];\n')
        fout.write(f'extern Hearts{h} hearts{h}[];\n')
        if d:
            fout.write(f'extern Diamonds{d} diamonds{d}[];\n')
        if c:
            fout.write(f'extern Clubs{c} clubs{c}[];\n')
        fout.write('enum {SPADES, HEARTS, DIAMONDS, CLUBS};\n') 
        name = f'dist{s}{h}{d}{c}'
        fout.write(f'\nvoid {name}() {{\n')
        fout.write('  int factor;\n')
        fout.write('  long total = 0L;\n')
        fout.write(f'  int END_SPADES  = {count(s)-1};\n')
        if h != s:
            fout.write(f'  int END_HEARTS  = {count(h)-1};\n')
        if d and d!= h:
            fout.write(f'  int END_DIAMONDS  = {count(d)-1};\n')
        if c and c!= d:
            fout.write(f'  int END_CLUBS  = {count(c)-1};\n')

        if s > h > d > c > 0:
            fout.write('  int index[4];\n')                       # abcd
            fout.write('  index[CLUBS]=-1;\n')
            fout.write('  index[DIAMONDS]=0;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[CLUBS] < END_CLUBS) {\n')
            fout.write('      index[CLUBS]++;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[DIAMONDS] < END_DIAMONDS) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      index[CLUBS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < END_HEARTS) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    };\n') 

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n') 

        if s > h > d > c == 0:                         # abc
            fout.write('  int index[4];\n')                       
            fout.write('  index[DIAMONDS]=-1;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[DIAMONDS] < END_DIAMONDS) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      index[CLUBS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < END_HEARTS) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = index[HEARTS]= 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n')

        if s > h and d == c == 0:
            fout.write('  int index[4];\n')                       # ab
            fout.write('  index[HEARTS]=-1;\n')
            fout.write('  index[SPADES]=0;\n')                       
            fout.write('  while(1) {\n')
            fout.write('    if (index[HEARTS] < END_HEARTS) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      factor = 12;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[HEARTS] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')
    
        if s == h > d > c > 0:                             # aabc
            fout.write('  int index[4];\n')                       
            fout.write('  index[CLUBS]=-1;\n')
            fout.write('  index[DIAMONDS]=0;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[CLUBS] < END_CLUBS) {\n')
            fout.write('      index[CLUBS]++;\n')
            fout.write('      factor = (index[HEARTS]==index[SPADES]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[DIAMONDS] < END_DIAMONDS) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      index[CLUBS] = 0;\n')
            fout.write('      factor = (index[HEARTS]==index[SPADES]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < index[SPADES]) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = 0;\n')
            fout.write('      factor = (index[HEARTS]==index[SPADES]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n')

        if s > h == d > c > 0:
            fout.write('  int index[4];\n')                      # abbc
            fout.write('  index[CLUBS]=-1;\n')
            fout.write('  index[DIAMONDS]=0;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')                             
            fout.write('  while(1) {\n')
            fout.write('    if (index[CLUBS] < END_CLUBS) {\n')
            fout.write('      index[CLUBS]++;\n')
            fout.write('      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[DIAMONDS] < index[HEARTS]) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      index[CLUBS] = 0;\n')
            fout.write('      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < END_HEARTS) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = 0;\n')
            fout.write('      factor = (index[DIAMONDS]==index[HEARTS]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')

        if s > h > d == c > 0:                             # abcc
            fout.write('  int index[4];\n')
            fout.write('  index[CLUBS]=-1;\n')
            fout.write('  index[DIAMONDS]=0;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[CLUBS] < index[DIAMONDS]) {\n')
            fout.write('      index[CLUBS]++;\n')
            fout.write('      factor = (index[CLUBS]==index[DIAMONDS]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[DIAMONDS] < END_DIAMONDS) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      index[CLUBS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < END_HEARTS) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = index[HEARTS] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')

        if s > h == d > c == 0:                             # abb
            fout.write('  int index[4];\n')                   
            fout.write('  index[DIAMONDS]=-1;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[DIAMONDS] < index[HEARTS]) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      factor = (index[DIAMONDS] == index[HEARTS]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < END_HEARTS) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[DIAMONDS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[DIAMONDS] =index[HEARTS] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')

        if s == h > d > c  == 0:                            #aab
            fout.write('  int index[4];\n')                       
            fout.write('  index[DIAMONDS]=-1;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[DIAMONDS] < END_DIAMONDS) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      factor = (index[HEARTS] == index[SPADES]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < index[SPADES]) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[DIAMONDS] = 0;\n')
            fout.write('      factor = (index[HEARTS] == index[SPADES]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[DIAMONDS] = index[HEARTS] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n')

        if s == h == d > c > 0:                             # aaab
            fout.write('  int index[4];\n')                      
            fout.write('  index[CLUBS]=-1;\n')
            fout.write('  index[DIAMONDS]=0;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')                          
            fout.write('  while(1) {\n')
            fout.write('    if (index[CLUBS] < END_CLUBS) {\n')
            fout.write('      index[CLUBS]++;\n')
            fout.write('      if (index[SPADES]==index[DIAMONDS]) factor = 4;\n')
            fout.write('      else if (index[SPADES]==index[HEARTS]) factor = 12;\n')
            fout.write('      else if (index[HEARTS]==index[DIAMONDS]) factor = 12;\n')
            fout.write('      else factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[DIAMONDS] < index[HEARTS]) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      index[CLUBS] = 0;\n')
            fout.write('      if (index[SPADES]==index[DIAMONDS]) factor = 4;\n')
            fout.write('      else if (index[SPADES]==index[HEARTS]) factor = 12;\n')
            fout.write('      else if (index[HEARTS]==index[DIAMONDS]) factor = 12;\n')
            fout.write('      else factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < index[SPADES]) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[DIAMONDS] = index[CLUBS] = 0;\n')
            fout.write('      factor = (index[HEARTS] == index[SPADES]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[HEARTS] = index[DIAMONDS]  = index[CLUBS] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')
        
        if s > h == d == c > 0:                             # abbb
            fout.write('  int index[4];\n')                    
            fout.write('  index[CLUBS]=-1;\n')
            fout.write('  index[DIAMONDS]=0;\n')
            fout.write('  index[HEARTS]=0;\n')
            fout.write('  index[SPADES]=0;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[CLUBS] < index[DIAMONDS]) {\n')
            fout.write('      index[CLUBS]++;\n')
            fout.write('      if (index[HEARTS]==index[CLUBS]) factor = 4;\n')
            fout.write('      else if (index[CLUBS]==index[DIAMONDS]) factor = 12;\n')
            fout.write('      else if (index[HEARTS]==index[DIAMONDS]) factor = 12;\n')
            fout.write('      else factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[DIAMONDS] < index[HEARTS]) {\n')
            fout.write('      index[DIAMONDS]++;\n')
            fout.write('      index[CLUBS] = 0;\n')
            fout.write('      factor = (index[HEARTS] == index[DIAMONDS]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[HEARTS] < END_HEARTS) {\n')
            fout.write('      index[HEARTS]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')   

            fout.write('    if (index[SPADES] < END_SPADES) {\n')
            fout.write('      index[SPADES]++;\n')
            fout.write('      index[CLUBS] = index[DIAMONDS] =index[HEARTS] = 0;\n')
            fout.write('      factor = 4;\n')
            fout.write('    } else break;\n')                            

        fout. write('\ncompute:\n\n    total += factor;\n')
        fout.write('  }\n\n')
        fout.write(f'  printf("{s}-{h}-{d}-{c}: %ld\\n", total);\n')
        fout.write('}')

genhands(13, 9, 2, 1)
genhands(13,10,2)
genhands(13,12)
genhands(11,11,2,1)
genhands(12,6,6,1)
genhands(13,6,3,3)
genhands(13,6,6)
genhands(12,12,1)
genhands(8,8,8,1)
genhands(13,4,4,4)


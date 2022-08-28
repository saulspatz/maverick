'''
Generate programs to count deals in Maverick solitaire,
by generating the equivalence classes one-by-one and
mutliplying by the appropriate factors.

There are 10 patterns that the distribution can have.
'''
def genhands(s, h, d=0, c=0):
    with open(f'src/{s}{h}{d}{c}.c', 'w') as fout:
        fout.write('#include <stdio.h>\n')
        fout.write(f'#include "../include/spades{s}.h"\n')
        fout.write(f'#include "../include/hearts{h}.h"\n')
        if d:
            fout.write(f'#include "../include/diamonds{d}.h"\n')
        if c:
            fout.write(f'#include "../include/clubs{c}.h"\n')
        name = f'dist{s}{h}{d}{c}'
        fout.write(f'\nvoid {name}() {{\n')
        fout.write(f'  int index[4];\n')
        for x in range(3):
            fout.write(f'  index[{x}] = 0;\n')
        fout.write('  index[3]=-1;\n')
        fout.write('  int factor;')
        if s > h > d > c > 0:                       # abcd
            fout.write('  long total = 0L;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    };\n') 

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[3] = index[2] = index[1] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n') 

        if s > h > d > c == 0:                         # abc
            fout.write('  while(1) {\n')
            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[3] = index[2] = index[1]= 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n')

        if s > h and d == c == 0:                        # ab
            fout.write('  while(1) {\n')
            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[3] = index[2] = index[1]= 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')
            fout.write('  }\n\n')
    
        if s == h > d > c > 0:                             # aabc
            fout.write('  while(1) {\n')
            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      factor = (index[1]==index[0]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      factor = (index[1]==index[0]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < index[0]) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      factor = (index[1]==index[0]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[3] = index[2] = index[1] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n')

        if s > h == d > c > 0:                             # abbc
            fout.write('  while(1) {\n')
            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      factor = (index[2]==index[1]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      factor = (index[2]==index[1]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      factor = (index[2]==index[1]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[3] = index[2] = index[1] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')

        if s > h > d == c > 0:                             # abcc
            fout.write('  while(1) {\n')
            fout.write('    if (index[3] < index[2]) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      factor = (index[3]==index[2]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[3] = index[2] = index[1] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')

        if s > h == d > c == 0:                             # abb
            fout.write('  while(1) {\n')
            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      factor = (index[2] == index[1]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[2] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[2] =index[1] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')

        if s == h > d > c  == 0:                            #aab
            fout.write('  while(1) {\n')
            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      factor = (index[1] == index[0]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < index[0]) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[2] = 0;\n')
            fout.write('      factor = (index[1] == index[0]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[2] = index[1] = 0;\n')
            fout.write('      factor = 24;\n')
            fout.write('    } else break;\n')

        if s == h == d > c > 0:                             # aaab                          
            fout.write('  while(1) {\n')
            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      if (index[0]==index[2]) factor = 4;\n')
            fout.write('      else if (index[0]==index[1]) factor = 12;\n')
            fout.write('      else if (index[1]==index[2]) factor = 12;\n')
            fout.write('      else factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      if (index[0]==index[2]) factor = 4;\n')
            fout.write('      else if (index[0]==index[1]) factor = 12;\n')
            fout.write('      else if (index[1]==index[3]) factor = 12;\n')
            fout.write('      else factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < index[0]) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[2] = index[3] = 0;\n')
            fout.write('      factor = (index[1] == index[2]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[2] =index[1] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('    } else break;\n')
        
        if s > h == d == c > 0:                             # abbb
            fout.write('  long total = 4L;\n')
            fout.write('  while(1) {\n')
            fout.write('    if (index[3] < index[2]) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      if (index[1]==index[3]) factor = 4;\n')
            fout.write('      else if (index[3]==index[2]) factor = 12;\n')
            fout.write('      else if (index[1]==index[2]) factor = 12;\n')
            fout.write('      else factor = 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      factor = (index[1] == index[2]) ? 12 : 24;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      factor = 12;\n')
            fout.write('      goto compute;\n')
            fout.write('    }\n')   

            fout.write('    if (index[0] < END0) {\n')
            fout.write('      index[0]++;\n')
            fout.write('      index[3] = index[2] =index[1] = 0;\n')
            fout.write('      factor = 4;\n')
            fout.write('    } else break;\n')                            

        fout. write('\ncompute:\n\n    total += factor;\n')
        fout.write('  }\n\n')
        fout.write('  printf("%ld\\n", total);\n')
        fout.write('  return 0;\n')
        fout.write('}')

genhands(8, 7, 6, 4)


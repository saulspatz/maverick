def genhands(s, h, d=0, c=0):
    with open(f'src/{s}{h}{d}{c}.c', 'w') as fout:
        fout.write('#include <stdio.h>\n')
        fout.write(f'#include "../include/spades{s}.h"\n')
        fout.write(f'#include "../include/hearts{h}.h"\n')
        if d:
            fout.write(f'#include "../include/diamonds{d}.h"\n')
        if c:
            fout.write(f'#include "../include/clubs{c}.h"\n')
        fout.write('\nint main() {\n')
        fout.write(f'  int index[4];\n')

        for x in range(4):
            fout.write(f'  index[{x}] = 0;\n')
        fout.write('  long total = 0L;\n')

        if s > h > d > c > 0:
            fout.write('    do {\n')
            fout.write('       total += 24;\n')
            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    };\n') 

            fout.write('    index[0]++;\n')
            fout.write('    index[3] = index[2] = index[1] = 0;\n')

        if s > h > d > c == 0:                         # abc
            fout.write('  do {\n')
            fout.write('    total += 24;\n')
            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    index[0]++;\n')
            fout.write('    index[3] = index[2] = index[1]= 0;\n')
        
        if s > h and d == c == 0:                        # ab
            fout.write('  do {\n')
            fout.write('    total += 12;\n')
            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    index[0]++;\n')
            fout.write('    index[1] = 0;\n')

        if s == h > d > c > 0:                             # aabc
            fout.write('  do {\n')
            fout.write('    total += (index[1]==index[0]) ? 12 : 24;\n')
            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < index[0]) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    index[0]++;\n')
            fout.write('    index[3] = index[2] = index[1] = 0;\n')

        if s > h == d > c > 0:                             # abbc
            fout.write('  do {\n')
            fout.write('    total += (index[2]==index[1]) ? 12 : 24;\n')
            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    index[0]++;\n')
            fout.write('    index[3] = index[2] = index[1] = 0;\n')

        if s > h == d > c == 0:                             # abb
            fout.write('  do {\n')
            fout.write('    total += (index[2] == index[1]) ? 12 : 24;\n')
            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('      index[0]++;\n')
            fout.write('      index[2] =index[1] = 0;\n')

        if s > h > d == c > 0:                             # abcc
            fout.write('  do {\n')
            fout.write('    total += (index[3]==index[2]) ? 12 : 24;\n')
            fout.write('    if (index[3] < index[2]) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    index[0]++;\n')
            fout.write('    index[3] = index[2] = index[1] = 0;\n')

        if s == h > d > c  == 0:                            #aab
            fout.write('  do {\n')
            fout.write('    total += (index[1] == index[0]) ? 12 : 24;\n')
            fout.write('    if (index[2] < END2) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < index[0]) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    index[0]++;\n')
            fout.write('    index[2] = index[1] = 0;\n')

        if s == h == d > c > 0:                             # aaab                          
            fout.write('  do {\n')
            fout.write('    if (index[0]==index[2]) total += 4;\n')
            fout.write('    else if (index[0]==index[1]) total += 12;\n')
            fout.write('    else if (index[1]==index[2]) total += 12;\n')
            fout.write('    else total += 24;\n')

            fout.write('    if (index[3] < END3) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < index[0]) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[2] = index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')
            fout.write('    index[0]++;\n')
            fout.write('    index[3] = index[2] =index[1] = 0;\n')

        if s > h == d == c > 0:                             # abbb
            fout.write('  do {\n')
            fout.write('    if (index[1]==index[3]) total += 4;\n')
            fout.write('    else if (index[3]==index[2]) total += 12;\n')
            fout.write('    else if (index[1]==index[2]) total += 12;\n')
            fout.write('    else total += 24;\n\n')
            fout.write('    if (index[3] < index[2]) {\n')
            fout.write('      index[3]++;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[2] < index[1]) {\n')
            fout.write('      index[2]++;\n')
            fout.write('      index[3] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')

            fout.write('    if (index[1] < END1) {\n')
            fout.write('      index[1]++;\n')
            fout.write('      index[3] = index[2] = 0;\n')
            fout.write('      continue;\n')
            fout.write('    }\n')   

            fout.write('    index[0]++;\n')
            fout.write('    index[3] = index[2] =index[1] = 0;\n')

        fout.write('  } while (index[0] <= END0);\n')
        fout.write('  printf("%ld\\n", total);\n')
        fout.write('  return 0;\n')
        fout.write('}')

genhands(13, 4, 4, 4)

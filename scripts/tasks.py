'''
1. Read the names of the distxxxx.c file from ../src/ to get the tasks
2. Read classes.txt file to get the number of classses in 
   each tasks.
3. Sort the tasks in decreasing order of classes.
4. Make the externs.h file
5. Make the tasks.h file 
'''

import os

files = [f[5:-2] for f in os.listdir('../src') if f.startswith('dist')]
dists = [f.translate({ord('_'): ord('-')}) for f in files]

sizes = { }
with open('../scripts/classes.txt') as fin:
    for line in fin:
        line = line.strip()
        if not line: break
        line = line.split()[:2]
        sizes[line[0]] = int(line[1].translate({ord(','):None}))

classes = sorted(list(sizes.items()), key = lambda x:x[1])
classes = [c[0] for c in classes if c[0] in dists]

with open("../include/externs.h", 'w') as fout:
    fout.write('#ifndef EXTERNS_H\n')
    fout.write('#define EXTERNS_H\n')
    for f in files:
        fout.write(f'extern void dist_{f}();\n')
    fout.write(f'\nint numTasks = {len(classes)};\n')
    fout.write('#endif\n')

with open("../include/tasks.h",'w') as fout:
    fout.write('#ifndef TASKS_H\n')
    fout.write('#define TASKS_H\n')
    fout.write('typedef void (*task)();\n')
    fout.write('task tasks[] = {\n')
    for c in classes:
        fout.write(f'dist_{c.translate({ord("-"):ord("_")})},\n')
    fout.write('};\n')  
    fout.write('#endif\n')

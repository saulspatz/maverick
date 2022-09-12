'''
1. Sort the equivalence classes in decreasing order of size.
2. Create the corresponding distxxx.c files in src/ directory.
3. Make the externs.h file
4. Make the tasks.h file
5. REMEMBER to manually adjust num_taks in maverick.c 
'''

from partitions import partitions, product, binomial
from hands import genhands
import rankSym

suits = {n: binomial(13,n) for n in range(14)}
equal = {n: binomial(6, n//2) for n in range(14)}
swords = {n: (suits[n]+equal[n])//2 for n in range(14)}

classes = []
for p in partitions(25, 4, 13):
    match p:
        case (s,h):
            hands = swords[s] * suits[h]
        case (s,h,d) if s > h > d:
            hands = swords[s]*product(suits[n] for n in p[1:])
        case (s,h,d,c) if s > h > d > c:
            hands =  swords[s]*product(suits[n] for n in p[1:])
        case (s, h, d) if h == s:
            k = suits[h]
            hands = sum(suits[d]*binomial(k,j) for j in (1,2))
        case (s, h, d) if h == d:
            k = suits[h]
            hands = sum(suits[s]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s==h>d:
            k = suits[h]
            hands = sum(suits[d]*suits[c]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s > h == d > c:
            k = suits[h]
            hands = sum(suits[s]*suits[c]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if h > d == c:
            k = suits[d]
            hands = sum(suits[s]*suits[h]*binomial(k,j) for j in (1,2))
        case (s,h,d,c) if s == d:
            k = suits[s]
            hands = sum(suits[c]*binomial(k,j) for j in (1,2,3))
        case (s,h,d,c) if h == c:
            k = suits[h]
            hands = sum(suits[s]*binomial(k,j) for j in (1,2,3))
        case _:
            print(f'{p} not matched')
    classes.append((hands, p))
    if len(p) == len(set(p)):
        rankSym.genhands(*p)
        print(f'{p} rankSym')
    else:
        genhands(*p)
        print(f'{p} hands')
classes.sort(reverse = True)

def compact(t):
    answer = 'dist'
    for x in t:
        answer += str(x)
    if len(t)==3:
        answer += '0'
    elif len(t)== 2:
        answer += '00'
    return answer

#modifed from externals.py
with open("../include/externs.h", 'w') as fout:
	fout.write('#ifndef EXTERNS_H\n')
	fout.write('#define EXTERNS_H\n')
	for _, p in classes:
		fout.write(f'extern void {compact(p)}();\n')
	fout.write('#endif\n')

# modifed from makeTasks.py
with open("../include/tasks.h",'w') as fout:
	fout.write('#ifndef TASKS_H\n')
	fout.write('#define TASKS_H\n')
	fout.write('typedef void (*task)();\n')
	fout.write('task tasks[] = {\n')
	for _, p in classes:
		fout.write(f'  {compact(p)},\n')
	fout.write('};\n')  
	fout.write('#endif\n')

print('You must MANUALLY adjust num_taks in maverick.c')

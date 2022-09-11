'''
Make the "suits.h" file
'''
a = ('spades', 'hearts', 'diamonds', 'clubs')
low = (7, 4, 1, 1)
high = (14, 13, 9, 7)
z = zip(a,low,high)
with open("../include/suits.h",'w') as fout:
	fout.write('#ifndef SUITS_H\n')
	fout.write('#define SUITS_H\n')
	for n in range(1,14):
		fout.write(f'#include "suit{n}.h"\n')
	for n in range(7,14):
		for s,l,h in z:
			for n in range(l,h):
				fout.write(f'#include "{s}{n}.h"\n')
	for n in range(7,14):
		fout.write(f'#include "ranks{n}.h"\n')
		fout.write(f'#include "swords{n}.h"\n')
	fout.write('#endif\n')

	


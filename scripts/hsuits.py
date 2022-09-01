'''
Make the "suits.h" file
'''

a = ('spades', 'hearts', 'diamonds', 'clubs')
low = (7, 4, 1, 1)
high = (14, 13, 8, 7)
z = zip(a,low,high)
with open("../include/suits.h",'w') as fout:
	for n in range(7,14):
		for s,l,h in z:
			for n in range(l,h):
				fout.write(f'#include "{s}{n}.h"\n')


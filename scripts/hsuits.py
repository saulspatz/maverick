'''
Make the "suits.h" file
'''
with open("../include/suits.h",'w') as fout:
	fout.write('#ifndef SUITS_H\n')
	fout.write('#define SUITS_H\n')
	for n in range(1,14):
		fout.write(f'#include "suit{n}.h"\n')
	for n in range(7,14):
		fout.write(f'#include "ranks{n}.h"\n')
	fout.write('#endif\n')

	


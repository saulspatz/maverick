suits = ('Spades', 'Hearts', 'Diamonds', 'Clubs')
low = (7, 4, 1, 1)
high = (14, 13, 9, 7)
z = zip(suits,low,high)

with open("../include/types.h", 'w') as fout:
	fout.write('#ifndef TYPES_H\n')
	fout.write('#define TYPES_H\n')
	fout.write('typedef struct {\n')
	fout.write('  unsigned char rank;\n')
	fout.write('  unsigned char suit;\n')
	fout.write('} Card;\n\n')
	fout.write('typedef unsigned int RankSet; ')
	for s, l, h, in z:
		for n in range(l, h):
			fout.write('typedef struct {\n')
			fout.write(f'  Card cards[{n}];\n')
			fout.write(f'  RankSet ranks;')
			fout.write(f"}} {s}{n};\n\n")
	fout.write('#endif\n')
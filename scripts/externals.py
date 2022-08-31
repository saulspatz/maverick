import os
with open("include/externs.h", 'w') as fout:
	fout.write('#ifndef EXTERNS_H\n')
	fout.write('#define EXTERNS_H\n')
	for prog in os.listdir("src"):
		if prog.startswith("dist"):
			fout.write(f'extern void {prog[:-2]}();\n')
	fout.write('#endif\n')






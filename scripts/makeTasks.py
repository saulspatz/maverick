import os

with open("../include/tasks.h",'w') as fout:
	fout.write('#ifndef TASKS_H\n')
	fout.write('#define TASKS_H\n')
	fout.write('typedef void (*task)();\n')
	fout.write('task tasks[] = {\n')
	for prog in os.listdir('../src'):
		if prog.startswith('dist'):
			fout.write(f'  {prog[:-2]},\n')
	fout.write('};\n')  
	fout.write('#endif\n')
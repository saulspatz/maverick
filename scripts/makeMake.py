import os

'''
This build the list of dependencies of the dist*.o
on the headers, to be pasted at the end of the makefile.
'''

with open("../build/includes.txt", 'w') as fout:
    for f in [f for f in os.listdir('../src') if f.startswith('dist')]:
        g = f.translate({ord('c'):ord('o')})
        text = g + ': ../include/types.h '
        with open('../src/'+f) as fin:
            for line in fin:
                line = line.strip()
                if not line.startswith('extern RankSet'):
                    continue
                line = line.split()
                text += '../include/'+ line[2][:-3] + '.h '
        fout.write(text+'\n')

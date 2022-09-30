import os

keep = []
with open('sift.py') as fin:
    for line in fin:
        line =line.strip()
        line = 'dist'+line.translate({ord('-'):ord('_')}) + '.c'
        keep.append(line)
for pgm in os.listdir('../src'):
    if not pgm.startswith('dist'):
        continue
    if pgm not in keep:
        os.system(f'rm ../src/{pgm}')


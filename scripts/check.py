counts = { }
with open('../build/counts.log') as fin:
    for line in fin:
        line = line.strip().split()
        counts[line[0]] = line[2]
classes = {}        
with open('classes.txt') as fin:
    for line in fin:
        line = line.strip().split()
        if not line: break
        classes[line[0]] = line[1]

errors = 0
for count in counts:
    if counts[count] != classes[count]:
        print(count)
        errors += 1

print(f'\n{errors} incorrect')
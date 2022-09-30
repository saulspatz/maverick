counts = { }
deals1 = {}
with open('../build/counts.log') as fin:
    for line in fin:
        line = line.strip().split()
        counts[line[0]] = line[2]
        deals1[line[0]] = line[1]
classes = {}        
with open('classes.txt') as fin:
    for line in fin:
        line = line.strip().split()
        if not line: break
        classes[line[0]] = line[1]
deals2 = {}
with open('partitions2.txt') as fin:
    for line in fin:
        line = line.strip().split()
        if not line: break
        deals2[line[0]] = line[1]

errors = 0
for count in counts:
    if counts[count] != classes[count]:
        print(count, counts[count], classes[count])
        errors += 1
    if deals1[count] != deals2[count]:
        print(count, deals1[count], deals2[count])
        errors += 1

print(f'\n{errors} incorrect')
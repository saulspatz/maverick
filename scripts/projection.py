from collections import namedtuple

Record = namedtuple('Record', ['done', 'seconds'])
text = open('interim.txt').readlines()
interim = {} 
for line in text:
    line = line.strip().split()
    interim[line[0]] = Record(sum(map(int,line[1:4])), float(line[-1]))
with open('classes.txt') as fin:
    for line in fin:
        line = line.strip().split()
        if not line: break
        dist = line[0]
        if dist in interim:
            total = int(line[1].replace(',',''))
            record = interim[dist]
            projected = total/record.done * record.seconds
            remaining = projected - record.seconds
            print(dist, 'projected:', projected/3600, 'remaining:', remaining/3600 )

            



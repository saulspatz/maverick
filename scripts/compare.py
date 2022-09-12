log = open('../results.log').readlines()
part = open('partitions2.txt').readlines()

log = [line.strip().split() for line in log]
part = [line.strip().split() for line in part]

log = {line[0][:-1]:int(line[1]) for line in log}
part = {line[0][:-1]:int(line[1]) for line in part}

log = sorted(log.items(), reverse=True)
part = sorted(part.items(), reverse=True)

log = {item[0] : item[1] for item in log}
part = {item[0] : item[1] for item in part}

for p in log:
    q = p.split('-')
    if len(q) == len(set(q)) and log[p] != 2*part[p]:
        print(f'{p} not twice')
   

print(sum(part.values()))

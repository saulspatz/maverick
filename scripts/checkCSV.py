import csv

partitions = {}
classes = {}

with open ('partitions2.txt') as fin:
    for line in fin:
        items = line.strip().split()
        num = int(items[1].replace(',',''))
        partitions[items[0]]=num

with open ('classes.txt') as fin:
    for line in fin:
        items = line.strip().split()
        if len(items) != 2:
            continue
        num = int(items[1].replace(',',''))
        classes[items[0]]=num

with open('/home/saul/Desktop/counts.csv', newline='') as fin:
    reader = csv.reader(fin)

    for line in reader:
        if not line[0]: continue
        if line[0].startswith('D'):continue
        
        for k in range(1,8):      
            line[k] = int(line[k].replace(',',''))
        key = line[0].strip()
        clas = sum(line[1:4])
        part = sum(line[4:7])
        if clas != classes[key]:
            print(f'class error for {key}')
        if part != partitions[key]:
            print(f'deal error for {key}')
        if line[7] > part:
            print(f'Too many solutions for {key}')



    

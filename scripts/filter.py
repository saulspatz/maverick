#filter.py
#filter duplicate lines from test.log

lines = set(open("../build/test.log").readlines())
with open("../build/test2.log", "w") as fout:
    for line in lines:
        fout.write(line)

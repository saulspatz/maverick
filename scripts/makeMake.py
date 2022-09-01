'''
This build the list of dependencies of the dist*.o
on the headers, to be pasted at the end of the makefile.
I don't think these will ever change, but who knows?
'''

from partitions import partitions
with open("../build/includes.txt", 'w') as fout:
    for p in partitions(25, 4, 13):
        match p:
            case (s,h,d,c):
                text =  f'dist{s}{h}{d}{c}.o:'
                text += f'../include/spades{s}.h '
                text += f'../include/hearts{h}.h '
                text += f'../include/diamonds{d}.h '
                text += f'../include/clubs{c}.h ../include/card.h\n'
            case (s,h,d):
                text =  f'dist{s}{h}{d}.o: '
                text += f'../include/spades{s}.h '
                text += f'../include/hearts{h}.h '
                text += f'../include/diamonds{d}.h ../include/card.h\n'
            case (s,h):
                text =  f'dist{s}{h}.o: '
                text += f'../include/spades{s}.h '
                text += f'../include/hearts{h}.h ../include/card.h\n'
            case _:
                print(f'unmatched: {p}')
                exit()
           
        fout.write(text)


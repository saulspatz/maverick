#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "types.h" //for RankSet

typedef struct {
    int flushes;
    int straights;
    int fullHouses;
} Value;

extern int solver(RankSet spades, RankSet hearts,
            RankSet diamonds, RankSet clubs, Value *value);

int main() {
    FILE *input = fopen("problems.txt", "r");
    FILE *solns = fopen("solutions.txt", "w");
    RankSet suit[4];
    int card;
    Value value;

    char buffer[80];
    char *ptr;
    int count; // characters read by sscanf
    while (fgets(buffer, 79, input)) {
        count = 0;
        ptr = buffer;
        memset(suit, 0, sizeof(suit));
        for (int i = 0; i < 25; ++i){
            sscanf(ptr, "%d%n", &card, &count);
            int c = (card-1)%13 + 1;
            int s = (card-1)/13;
            suit[s] |= 1 << c;
            ptr += count; 
        }
        int s = solver(suit[3], suit[2], suit[1], suit[0], &value);
        fprintf(solns, "%d %d %d %d\n", 
            value.flushes, value.straights, value.fullHouses, s);
        fflush(solns);
    }
    fclose(solns);
}

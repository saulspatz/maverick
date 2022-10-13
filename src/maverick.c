#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "externs.h" // names of pattern functions
#include "suits.h"   // all possible suit distributions
#include "tasks.h"   // task list

extern int numTasks;

int main(int argc, char *argv[]) {
	if (!access("counts1.csv",F_OK)) {
		FILE* out = fopen("counts1.csv", "w");
		fprintf(out, "Distribution, Exhaustive Search, Heuristic, Short Five,Exhaustive Search, Heuristic, Short Five, Time\n");
		fclose(out);
	}
	if (argc == 1) {
		fprintf(stderr, "Arguments required for tasks\n");
		exit(1);
	}  
	if (strncmp(argv[1], "-f", 2) == 0) {
		FILE *fin = fopen(argv[1]+2, "r");
		int index;
		fscanf(fin, "%d", &index);
		while (!feof(fin)) {
			if (index>= numTasks) {
				FILE *log = fopen("maverick.log", "a");
				fprintf(log, "maverick.c: Invalid index %d\n", index);
				fclose(log);
				continue;
			}
			tasks[index]();
			fscanf(fin, "%d", &index);
		}
	}
	else {
		for (int i = 1; i <= argc; i++) {
			int index = atoi(argv[i]);
			if (index>= numTasks) {
				FILE *log = fopen("maverick.log", "a");
				fprintf(log, "maverick.c: Invalid index %d\n", index);
				fclose(log);
				continue;
			}
			tasks[index]();
		}
	}
}
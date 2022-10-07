#include <stdio.h>
#include "externs.h" // names of pattern functions
#include "suits.h"   // all possible suit distributions
#include "tasks.h"   // task list

int main() {
	extern int numTasks;
	FILE* out = fopen("counts2.log", "w");
	fprintf(out, "Distribution, Exhaustive Search, Heuristic, Short Five,Exhaustive Search, Heuristic, Short Five, Time\n");
	fclose(out);
	for (int i = 0; i < numTasks; ++i)
		tasks[i]();  
}
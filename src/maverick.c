#include <stdio.h>
#include <unistd.h>
#include "externs.h" // names of pattern functions
#include "suits.h"   // all possible suit distributions
#include "tasks.h"   // task list

int main() {
	extern int numTasks;
	if (!access("counts1.log",F_OK)) {
		FILE* out = fopen("counts1.log", "w");
		fprintf(out, "Distribution, Exhaustive Search, Heuristic, Short Five,Exhaustive Search, Heuristic, Short Five, Time\n");
		fclose(out);
	}
	for (int i = 0; i < numTasks; ++i)
		tasks[i]();  
}
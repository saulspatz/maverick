#include "externs.h" // names of pattern functions
#include "suits.h"   // all possible suit distributions
#include "tasks.h"   // task list

int main() {
	extern int numTasks;
	for (int i = 0; i < numTasks; ++i)
		tasks[i]();  
}
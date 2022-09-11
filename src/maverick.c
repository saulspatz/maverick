#include "externs.h" // names of pattern functions
#include "suits.h"   // all possible suit distributions
#include "tasks.h"   // task list

int main() {
	const int numTasks = 102;
	for (int i = 0; i < numTasks; ++i)
		tasks[i]();  
}
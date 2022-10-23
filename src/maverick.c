#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include "externs.h" // names of pattern functions
#include "suits.h"   // all possible suit distributions
#include "tasks.h"   // task list
#include "straights.h" // all possible straights

extern int numTasks;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int fexists(const char *fileanme);
unsigned int interval = 3600;
int backup;

void *setFlag(){
	while(1) {
		sleep(interval);
		pthread_mutex_lock( &mutex1 );
		backup = 1;
		pthread_mutex_unlock( &mutex1 );
	}
	return 0;
}

int main(int argc, char *argv[]) {
	pthread_t thread1;
	pthread_create(&thread1, NULL, setFlag, NULL);

	if (!fexists("../results/counts.csv")) {
		FILE* out = fopen("../results/counts.csv", "w");
		fprintf(out, "Distribution, Exhaustive Search, Heuristic, Short Five,Exhaustive Search, Heuristic, Short Five, Solutions, Time\n");
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
				FILE *log = fopen("../results/maverick.log", "a");
				fprintf(log, "../results/maverick.c: Invalid index %d\n", index);
				fclose(log);
				continue;
			}
			tasks[index]();
			fscanf(fin, "%d", &index);
		}
	}
	else {
		for (int i = 1; i < argc; i++) {
			int index = atoi(argv[i]);
			if (index>= numTasks) {
				FILE *log = fopen("../results/maverick.log", "a");
				fprintf(log, "maverick.c: Invalid index %d\n", index);
				fclose(log);
				continue;
			}
			tasks[index]();
		}
	}
}
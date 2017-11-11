#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>


long* arr;
long size;
long x;
long res;
int n;
int id = -1;

void myThread() {
	id++;
	printf("Thread %d \n", id);
	long result = -1;
   	for (int i = id*(size/n); i < (id+1)*(size/n) && result == -1; i++) {
		if (arr[i] == x) {
			result = i;
		}
	}
	if (result != -1) 
		printf("T RES %ld\n", result);
    	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	if ( argc != 3 ) {
		printf("Not Enough Argument\n");
		return 1;
	}
	size = strtol(argv[1], NULL, 10);
	arr = (long*)(malloc(size * sizeof(long)));
   	x = strtol(argv[2], NULL, 10);
   	for (size_t i = 0; i < size; i++) arr[i] = i*2;
	n = 4;
	int i;
	clock_t begin, end;
	double time_spent;
	begin = clock();
	printf("Start");
	pthread_t tid[4];
	for (i = 0; i < n; i++)
		pthread_create(&tid[i], NULL, myThread, (void*)i);
	
	for (i = 0; i < n; i++)
		pthread_join(&tid[i], NULL);
	
	end = clock();
	printf("END");
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time that spend for search in %d Thread is %f \n", n, time_spent);
   	return 0;

}

#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>


long* arr;
long size;
long x;
long res;
int n;
int id = -1;

void* myThread(void * pthis) {
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
	return 0;
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
	n = 8;
	int i;
	clock_t begin, end;
	double time_spent;
	begin = clock();
	printf("Start");
	HANDLE thread[8]; //Thread handle
        DWORD lpId[8];
	for (i = 0; i < n; i++) {
 		thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)myThread, (LPVOID) NULL,0,(LPDWORD) &lpId);
	}    
	for (i = 0; i < n; i++) {
		WaitForSingleObject(thread[i], INFINITE);
		CloseHandle(thread[i]);
	}
	end = clock();
	printf("END");
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time that spend for search in %d Thread is %f \n", n, time_spent);
   	return 0;

}

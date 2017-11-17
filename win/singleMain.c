#include <time.h>
#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char* argv[]) {
	if ( argc != 3 ) {
		printf("Not Enough Argument\n");
		return 1;
	}
	long n = strtol(argv[1], NULL, 10);
	long* arr = (long*)(malloc(n * sizeof(long)));
   	long x = strtol(argv[2], NULL, 10);
   	for (size_t i = 0; i < n; i++) arr[i] = i*2;
	long result = -1;
	clock_t begin, end;
	double time_spent;
	begin = clock();
   	for (int i = 0; i < n && result == -1; i++) {
		if (arr[i] == x) {
			result = i;
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	(result == -1) ? printf("Element is not present in array time that spend to search %f \n", time_spent)
                       : printf("Element is present at index %ld time that spend to search %f \n", result, time_spent);
   	return 0;
}

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main(int argc, char* argv[]) {
	if ( argc != 3 ) {
		printf("Not Enough Argument\n");
		return 1;
	}
	long size = strtol(argv[1], NULL, 10);
	long* arr = (long*)(malloc(size * sizeof(long)));
   	long x = strtol(argv[2], NULL, 10);
   	for (size_t i = 0; i < size; i++) arr[i] = i*2;

	pid_t pids[10];
	int i;
	int n = 10;
	/* Start children. */
	clock_t begin, end;
	double time_spent = 0.0;
	begin = clock();
	for (i = 0; i < n; ++i) {
  		if ((pids[i] = fork()) < 0) {
    			perror("fork");
    			abort();
  		} else if (pids[i] == 0) {
    			long temp = -1;
			for (int  j = i*(size/n); j < (i+1)*size/n; j++) {
				if (arr[j] == x) {
					temp = j;	
					break;
				}
			}
			if (temp != -1)
                        	printf("Element is present at index %ld TEMP\n", temp);
			exit(0);
  		}
	}
	/* Wait for children to exit. */
	int status;
	pid_t pid;
	while (n > 0) {
  		pid = wait(&status);
  		--n;  // TODO(pts): Remove pid from the pids array.
	}
	end = clock();
	time_spent = (double)(end - begin)/ CLOCKS_PER_SEC;
	printf("\nTime that Spend : %f \n", time_spent);
   	return 0;
}

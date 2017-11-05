#include <stdio.h>
#include <stdlib.h> 
// A recursive binary search function. It returns location of x in
// given array arr[l..r] is present, otherwise -1
long binarySearch(long arr[], long l, long r, long x)
{
   if (r >= l)
   {
        long mid = l + (r - l)/2;
 
        // If the element is present at the middle itself
        if (arr[mid] == x)  return mid;
 
        // If element is smaller than mid, then it can only be present
        // in left subarray
        if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);
 
        // Else the element can only be present in right subarray
        return binarySearch(arr, mid+1, r, x);
   }
 
   // We reach here when element is not present in array
   return -1;
}
 
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
	for (i = 0; i < n; ++i) {
  		if ((pids[i] = fork()) < 0) {
    			perror("fork");
    			abort();
  		} else if (pids[i] == 0) {
			long temp = binarySearch(arr, i*size/n, ((i+1)*size/n) - 1, x);
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

   	return 0;
}

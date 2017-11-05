#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>


long* arr;
long size;
long x;
long res;
int n;
int id = -1;
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

void myThread() {
	id++;
	long temp = binarySearch(arr, id*size/n, ((id+1)*size/n) - 1, x);
	if (temp != -1) 
		printf("T RES %ld\n", temp);
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
	pthread_t tid;
	for (i = 0; i < n; i++)
		pthread_create(&tid, NULL, myThread, (void*)i);
    	pthread_exit(NULL);

   	return 0;

}

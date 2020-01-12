#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000000


int main(int argc, char *argv) {
	FILE *fp = fopen("q2-data.csv", "w");
	long int n = 10000;
	
	while (n <= MAX_SIZE) {
		long int *arr = malloc(sizeof(long int) * n), key = -1;
		for (long int i = 0; i < n; i++)
			arr[i] = i;

		long int low = 0, high = n - 1;

		int iterations = 0;

		//============================
		while (high >= low) {
			long int mid = low + ((high - low) / 2);
			
			if (arr[mid] == key)
				break;
			else if (arr[mid] < key)
				low = mid + 1;
			else
				high = mid - 1;
			
			iterations++;
		}
		//============================

		fprintf(fp, "%ld,%d\n", n, iterations);


		n <<= 1;
	}
	
	
	fclose(fp);
	
	return 0;
}

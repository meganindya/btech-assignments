#include <stdio.h>
#include <stdlib.h>


int getSearchBinaryTime(int n) {
	int *arr = malloc(sizeof(int) * n);
		for (long int i = 0; i < n; i++)
			arr[i] = i;

	//============================
	int key = -1, iterations = 0;
	
	int low = 0, high = n - 1;

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

	return iterations;
}

int main(int argc, char *argv) {
	FILE *fp = fopen("q2-data.csv", "w");
	long int n = 10000;
	
	do {
		fprintf(fp, "%ld,%d\n", n, getSearchBinaryTime(n));
	} while((n <<= 1) < 1000000000);
	
	fclose(fp);
	system("./q2-plot.sh");
	
	return 0;
}

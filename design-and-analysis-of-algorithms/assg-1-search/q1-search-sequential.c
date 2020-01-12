#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv) {
	FILE *fp = fopen("q1-data.csv", "w");
	long int n = 10000, ti;
	clock_t start, end;
	
	while (n <= 100000000) {
		int *arr = (int *) malloc(sizeof(int) * n), key = -1;
		for (int i = 0; i < n; i++)
			arr[i] = i;
		
		start = clock();

		//============================
		int i = 1;

		check:
		if (key == arr[i - 1])
			goto exit;
		
		i = i + 1;

		if (i <= n)
			goto check;
		//============================

		exit:
		end = clock();
		
		double time = ((double) (end - start)) / CLOCKS_PER_SEC;
		ti = time * 1000000000;
		fprintf(fp, "%ld,%ld\n", n, ti);


		n <<= 1;
	}
	
	
	fclose(fp);
	
	return 0;
}

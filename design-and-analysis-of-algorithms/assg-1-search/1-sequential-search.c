#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv) {
	FILE *fp = fopen("q1.csv", "w");
	long long int n = 10000, ti;
	clock_t start, end;
	
	
	while (n <= 1000000) {
		int arr[n], key = n;
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
		fprintf(fp, "%lld,%lld\n", n, ti);


		n = n + 10000;
	}
	
	
	fclose(fp);
	
	return 0;
}

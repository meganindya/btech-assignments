#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long int getSearchSequentialTime(int n) {
	int *arr = (int *) malloc(sizeof(int) * n), key = -1;
	for (int i = 0; i < n; i++)
		arr[i] = i;
	
	clock_t start, end;
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
	return (time * 1000000000);
}

int main(int argc, char *argv) {
	FILE *fp = fopen("q1-data.csv", "w");
	long int n = 10000;
	
	do {
		fprintf(fp, "%ld,%ld\n", n, getSearchSequentialTime(n));
	} while((n <<= 1) < 1000000000);
	
	fclose(fp);
	system("./q1-plot.sh");
	
	return 0;
}

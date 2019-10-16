#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *input(int *);
void sort(int *, int, int);
int part(int *, int, int);
void swap(int *, int *);

int main(void){
	int n, *inp = input(&n);
	sort(inp, 0, n - 1);
	printf("   Sorted Sequence :\t");
	for(int i = 0; i < n; i++)	printf("%d ", inp[i]);
	printf("\n\n");
}

void sort(int *a, int low, int high){
	if(low < high){
		int p = part(a, low, high);
		sort(a, low, p - 1);
		sort(a, p + 1, high);
	}
}

int part(int *a, int low, int high){
	int x = a[high], i = low - 1;

	for(int j = low; j <= high - 1; j++){
		if(a[j] <= x)	swap(&a[++i], &a[j]);
	}

	swap(&a[i + 1], &a[high]);
	return (i + 1);
}

void swap(int *a, int *b){
	int t = *a;
	*a = *b; *b = t;
}

int *input(int *n){
	printf("\n\n   Enter Sequence :\t");
	char *s = (char *) malloc(sizeof(char) * 256);
	scanf("%[^\n]s", s); int len = strlen(s);
	s[len] = ' '; len++;
	int *arr = (int *) malloc(sizeof(int) * 128), k = 0;
	for(int i = 0; i < 128; i++)	arr[i] = 0;
	for(int i = 0; i < len; i++){
		if(s[i] == ' ')	k++;
		else arr[k] = arr[k] * 10 + (s[i] - '0');
	}
	int *input = (int *) malloc(sizeof(int) * k);
	for(int i = 0; i < k; i++)	input[i] = arr[i];
	free(arr); free(s); *n = k;
	return input;
}
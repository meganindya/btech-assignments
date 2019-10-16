#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *input(int *);
void sort(int *, int, int);
void merge(int *, int, int, int);

int main(void){
	int n, *inp = input(&n);
	sort(inp, 0, n);
	printf("   Sorted Sequence :\t");
	for(int i = 0; i < n; i++)	printf("%d ", inp[i]);
	printf("\n\n");
}

void sort(int *a, int low, int high){
	if(low < high){
		int mid = (low + high) / 2;
		sort(a, low, mid);
		sort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
}

void merge(int *a, int low, int mid, int high){
	int n1 = mid - (low - 1); 
	int n2 =  high - mid;
	int l[n1], r[n2];
	for(int z = 0; z < n1; z++)	l[z] = a[low + z];
	for(int z = 0; z < n2; z++)	r[z] = a[mid + 1 + z];

	int i = 0, j = 0, k = low;
	while((i < n1) && (j < n2)){
		if(l[i] <= r[j])	a[k++] = l[i++];
		else				a[k++] = r[j++];
	}

	while(i < n1)	a[k++] = l[i++];
	while(j < n2)	a[k++] = r[j++];
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
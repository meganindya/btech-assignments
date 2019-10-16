#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *input(int *);
int search(int *, int, int, int);

int main(void){
	int n, *arr = input(&n), x;
	printf("   Enter Target : "); scanf("%d", &x);
	int pos = search(arr, x, 0, n - 1);
	if(pos == -1)	printf("\n   Target Not Found!\n\n");
	else 			printf("\n   Target Found at position %d\n\n", pos);
}

int search(int *a, int x, int lb, int rb){
	if(rb >= lb){
		int mid = lb + (rb - lb) / 2;
		if(a[mid] == x)		return mid;
		if(a[mid] > x)		return search(a, x, lb, mid - 1);
							return search(a, x, mid + 1, rb);
	}
	return -1;
}

int *input(int *n){
	printf("\n\n   Enter Array Elements :\t");
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
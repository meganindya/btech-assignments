#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *input(int *);
int *ins(int *, int);
int *del(int *, int);

int main(void){
	printf("\033[H\033[J");
    int n, *tree = input(&n);
	int *sorted = ins(tree, n);
	printf("\n   Sorted Sequence :\t");
	for(int i = 0; i < n; i++)
		printf("%d ", sorted[i]);
	printf("\n\n");
}

int *input(int *n){
	printf("\n\n   Enter Sequence :\t");
	char *s = (char *) malloc(sizeof(char) * 256);
	scanf("%[^\n]s", s); int len = strlen(s);
	s[len] = ' '; len++;
	int *arr = (int *) malloc(sizeof(int) * 128), *input, k = 0;
	for(int i = 0; i < 128; i++)	arr[i] = 0;
	for(int i = 0; i < len; i++){
		if(s[i] == ' ')	k++;
		else arr[k] = arr[k] * 10 + (s[i] - '0');
	}
	input = (int *) malloc(sizeof(int) * k);
	for(int i = 0; i < k; i++)	input[i] = arr[i];
	free(arr); free(s); *n = k;
	return input;
}

int *ins(int *tree, int n){
	int *arr = (int *) malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++){
		arr[i] = tree[i];
		if(i == 0)	continue;
		int par = (i - 1) / 2;
		int chd = i;
		while(par != chd){
			if(arr[par] < arr[chd]){
				int temp = arr[par];
				arr[par] = arr[chd];
				arr[chd] = temp;
				chd = par;
				par = (chd - 1) / 2;
			}
			else break;
		}
	}
	return del(arr, n);
}

int *del(int *tree, int n){
	if(n < 2)	goto skip;
	for(int i = 0; i < (n - 2); i++){
		int temp = tree[n - 1 - i];
		tree[n - 1 - i] = tree[0];
		tree[0] = temp;
		int par = 0, lch = 1, rch = 2;
		while(rch < (n - 1 - i)){
			if((tree[par] > tree[lch]) && (tree[par] > tree[rch]))	break;
			int index, temp;
			if(tree[lch] > tree[rch])	index = lch;
			else index = rch;
			temp = tree[par];
			tree[par] = tree[index];
			tree[index] = temp;
			par = index;
			lch = 2 * par + 1;
			rch = lch + 1;
		}
	}
	skip: return tree;
}

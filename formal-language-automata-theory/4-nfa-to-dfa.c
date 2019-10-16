// Author : Anindya Kundu - 510817020

// This program stores and prints the State Table of a
// Non-deterministic Finite Automata. It then converts
// the Non-deterministic Finite Automata to Deterministic
// Finite Automata and prints it's State Table.

// It takes the "number of states", the "inputs", the
// "transitional functions" and the final state as input.

// The NFA Table is a 2D array of rows = number of states
// and columns = number of inputs.
//   '→' is placed before initial state.
//   '●' is placed before final state.
// The data type of the table is a defined structure
// containing the string of the next states and length.
// The DFA Table follows the same.

// It is assumed that the states are serially denoted
// from 'A', hence present state isn't stored. It is
// also assumed that the first state is the initial
// state. Also, the input syntax is to be correct
// semantically and syntactically as follows:
// * Enter Number of States: *integer*
// * Enter Inputs: #,#,..,# (# : lower alpha / digit)
// * Enter Transitional Functions:
// *   δ(%, $) → #,...,#  *uppercase alphabet / '-'*
//                        (only '-' in it's case)
// * Enter Final State/s: *uppercase alphabet*

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define clear() printf("\033[H\033[J")

typedef struct nfa{
	char *s;	//string of next states
	int n;		//length of string
}	cell;

char *getVals(int *, int);
void inputTransFuncs(cell **, char *, int, int);
void printStateTable(cell **, char *, int, int, char *);
int max(int *, int);
cell ***toDFA(cell **, char *, int, int, char *, int *);
int contains(char *, char);
char *copyString(char *);
void fillTable(cell ***, int, int, cell **);
int unorderedCompare(char *, char *);
void nonDuplicateCopy(char *, char *, int *);
void push(char **, int *, char *);
char *pop(char **, int *);

int main(int argc, char *argv[]){
    clear(); int r, c;
    printf("Enter Number of States: ");
    scanf("%d", &r);
    printf("Enter Inputs: ");
    char *ip = getVals(&c, 1);
    printf("Enter Transitional Functions:\n");
    cell *ar[r][c]; inputTransFuncs(&ar[0][0], ip, r, c);
    printf("Enter Final State/s: ");
    int n_fin; char *fin = getVals(&n_fin, 2);

    printf("\nState Table for NFA:\n--------------------\n");
    printStateTable(&ar[0][0], ip, r, c, fin);
    
    //GLITCH!! : doesn't work without this loop
    for(int i = 0; i < r; i++)
    	//for(int j = 0; j < c; j++)
    		if(ar[i][0] != NULL){}
   
    printf("\n  (states renamed)");
    printf("\nState Table for DFA:\n--------------------\n");
    int l; cell ***tb = toDFA(&ar[0][0], ip, r, c, fin, &l);
    r = l; cell *ot[r][c];	//copy of tb
    for(int i = 0; i < r; i++)
    	for(int j = 0; j < c; j++)
    		ot[i][j] = tb[i][j];
    printStateTable(&ot[0][0], ip, r, c, fin);

    printf("\n");
    return 0;
}

//returns a string of inputs(z = 1) / next states(z = 2)
//  (stores length in passed pointer)
char *getVals(int *n, int z){
    char s[64], t[64]; *n = 0;
    scanf("%s", s);
    for(int i = 0; s[i] != '\0'; i++){
        if(z == 1 && (islower(s[i]) || isdigit(s[i])))  t[(*n)++] = s[i];
        if(z == 2 && (isupper(s[i]) || s[i] == '-'))    t[(*n)++] = s[i];
    }
    char *ip = (char *) malloc(sizeof(char) * (*n));
    for(int i = 0; i < (*n); i++)   ip[i] = t[i];
    return ip;
}

void inputTransFuncs(cell **ar, char *ip, int r, int c){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            printf("  δ(%c, %c) → ", ('A' + i), *(ip + j));
            cell *temp = (cell *) malloc(sizeof(cell));
            temp -> n = 0;  temp -> s = getVals(&(temp -> n), 2);
            *(ar + (c * i) + j) = temp;
        }
    }
}

void printStateTable(cell **ar, char *ip, int r, int c, char *fn){
	printf("   P S\t");
    if(c % 2 != 0)
    {   for(int i = 1; i < c / 2; i++)  printf("\t");   printf("   ");  }
    else
    {   for(int i = 1; i < (c - 1) / 2; i++)  printf("\t");   printf("       ");  }
    printf("N S\n--------");
    for(int i = 0; i < c; i++)  printf("|-------"); printf("\n\t");
    for(int i = 0; i < c; i++)  printf("    %c\t", ip[i]);
    printf("\n********");
    for(int i = 0; i < c; i++)  printf("|*******"); printf("\n");

    for(int i = 0; i < r; i++){
        int n_row[c], max_vals;
        for(int j = 0; j < c; j++){
        	cell *temp = *(ar + (c * i) + j);
        	n_row[j] = temp -> n;
        }
        max_vals = max(n_row, c);
        if(i == 0){	printf("  → %c\t", ('A' + i)); goto skip;	}
        for(int k = 0; fn[k] != '\0'; k++)
        	if(fn[k] == ('A' + i)){
        		printf("  ● %c\t", ('A' + i));
        		goto skip; break;
        	}
        printf("    %c\t", ('A' + i));
        skip:
        for(int k = 0; k < max_vals; k++){
        	if(k != 0)	printf("\t");
        	for(int j = 0; j < c; j++){
        		cell *temp = *(ar + (c * i) + j);
        		if(k < (temp -> n))	printf("|   %c\t", temp -> s[k]);
        		else				printf("|\t");
        	}  	printf("\n");
        }
    	printf("--------");
    	for(int i = 0; i < c; i++)	printf("|-------"); printf("\n");
    }
}

//returns max element of array
int max(int *a, int n){
	int z = 0;
	for(int i = 0; i < n; i++)
		if(a[i] > z)	z = a[i];
	return z;
}

//returns the 2D array of DFA (no of rows stored in *l)
cell ***toDFA(cell **ar, char *ip, int r, int c, char *fn, int *l){
	int row = 1, col = c + 1;	//columns increased to fit initial states
	for(int i = 0; i < r; i++)	row *= 2;	//∵ max states = 2 ^ mod

		//Intermediate DFA array(for operation) declaration
	cell ***tb = (cell ***) malloc(sizeof(cell **) * row);
	for(int i = 0; i < row; i++)
		tb[i] = (cell **) malloc(sizeof(cell *) * col);
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			tb[i][j] = NULL;

		//filling 1st row from NFA table
	cell *temp = (cell *) malloc(sizeof(cell));
	temp -> n = 1; temp -> s = (char *) malloc(sizeof(char));
	temp -> s[0] = 'A';
	tb[0][0] = temp;
	for(int i = 0; i < c; i++){
		cell *temp = (cell *) malloc(sizeof(cell));
		cell *old = *(ar + (c * 0) + i);
		temp -> n = strlen(old -> s);
		temp -> s = copyString(old -> s);
		tb[0][i + 1] = temp;
	}

	fillTable(tb, row, col, ar);	//fills the rest by algorithm
		//len stores new number of rows
	int len, cn = 0; for(len = 0; tb[len][0] != NULL; len++);
	for(int i = 0; fn[i] != '\0'; i++)
		for(int j = 0; j < len; j++){
			cell *temp = tb[j][0];
			if(contains(temp -> s, fn[i]))	cn++;
		}
		//making a list of new final states according to new states
	char *fs = (char *) malloc(sizeof(char) * cn); int m = 0;
	for(int i = 0; fn[i] != '\0'; i++)
		for(int j = 0; j < len; j++){
			cell *temp = tb[j][0];
			if(contains(temp -> s, fn[i]))	fs[m++] = 'A' + j;
		}
		//refresing final states list according to new states
	fn = (char *) realloc(fn, sizeof(char) * cn);
	strcpy(fn, fs);

		//final DFA array declaration
	cell ***out = (cell ***) malloc(sizeof(cell **) * len);
	for(int i = 0; i < len; i++)
		out[i] = (cell **) malloc(sizeof(cell *) * c);
	for(int i = 0; i < len; i++)
		for(int j = 0; j < c; j++)
			for(int k = 0; k < len; k++){
				cell *a = tb[k][0], *b = tb[i][j + 1];
				if(unorderedCompare(a -> s, b -> s) == 1){
					cell *outc = (cell *) malloc(sizeof(cell));
					outc -> n = 1; outc -> s = (char *) malloc(sizeof(char));
					outc -> s[0] = 'A' + k;
					out[i][j] = outc;
				}
			}
	*l = len;	//stores new number of rows to passed length pointer
	return out;
}

//returns 1 if character is present in string, 0 if not
int contains(char *s, char x){
	for(int i = 0; s[i] != '\0'; i++)
		if(s[i] == x){	return 1; break;	}
	return 0;
}

//returns pointer of a duplicated string
char *copyString(char *s){
	char *str = (char *) malloc(sizeof(char) * strlen(s));
	for(int i = 0; s[i] != '\0'; i++)
		str[i] = s[i];
	return str;
}

//fills remainder of Intermediate DFA array
void fillTable(cell ***ar, int r, int c, cell **or){
	char *stack[r]; int top = -1, k = 1;	//stack definition
	for(int i = c - 1; i > 0; i--){	//pushing 1st row elements in stack
		cell *temp = ar[0][i];
		if(temp -> s[0] == '-')	continue;
		push(stack, &top, temp -> s);
	}
	while(top != -1){				//looping until stack is empty
		char *temp = pop(stack, &top); int f = 0;
		for(int i = 0; ar[i][0] != NULL; i++){	//pop and compare with 1st column
			cell *ps = ar[i][0];
			if(unorderedCompare(temp, ps -> s) == 1){	f = 1; break;	}
		}
		if(f == 1)	continue;		//skip to next if already present
		else{
			cell *new = (cell *) malloc(sizeof(cell));
			new -> n = strlen(temp);
			new -> s = copyString(temp);
			ar[k][0] = new;			//add a new row with element in 1st column
			for(int i = 1; i < c; i++){	//add it's next states from NFA table
				char str[(int)(log(r) / log(2))]; int t = 0;
				for(int j = 0; str[j] != '\0'; j++)	str[j] = 0;
				for(int j = 0; temp[j] != '\0'; j++){
					char x = temp[j];
					cell *cur = *(or + ((x - 'A') * (c - 1))  + (i - 1));
					char *dat = cur -> s;
					if(dat[0] == '-')	continue;
					nonDuplicateCopy(dat, str, &t);
				}
				cell *new = (cell *) malloc(sizeof(cell));
				new -> n = strlen(str);
				new -> s = copyString(str);
				ar[k][i] = new;
				push(stack, &top, str);	//add new element to stack
			}	k++;
		}
	}
	printf("  (intermediate)\n");
	for(int i = 0; i < k; i++){
		for(int j = 0; j < c; j++){
			cell *temp = ar[i][j];
			printf(" |%s|\t", temp -> s);
			if(j == 0)	printf(":");
		}
		printf("\n");
	}	printf("\n  (final)\n");
}

//returns true if both strings have same characters(unordered), 0 if not
int unorderedCompare(char *a, char *b){
	if(strlen(a) != strlen(b))	return 0;
	else{
		int c = 0;
		for(int i = 0; a[i] != '\0'; i++){
			for(int j = 0; b[j] != '\0'; j++)
				if(a[i] == b[j])	c++;
		}
		if(c == strlen(a))	return 1;
		else				return 0;
	}
}

//copies characters not present in destination from source
void nonDuplicateCopy(char *src, char *des, int *p){
	for(int i = 0; src[i] != '\0'; i++){
		char x = src[i];
		for(int j = 0; j < (*p); j++)
			if(x == des[j]){	return;	break;	}
		des[(*p)++] = x;
	}
}

//stack push function
void push(char **stack, int *top, char *v){
	stack[++(*top)] = copyString(v);
}

//stack pop function
char *pop(char **stack, int *top){
	return stack[(*top)--];
}
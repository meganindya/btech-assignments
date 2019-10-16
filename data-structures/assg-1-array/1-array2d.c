/*
	Program to store profit made by 20 stores
	in a mall, each having 5 departments
*/

#include <stdio.h>

void cellinfo(int *r, int *c);
void dsp(int *data);
void ins(int *data, int r, int c);
void del(int *data, int r, int c);
void upd(int *data, int r, int c);

int main(void){
	int data[20][5], ch, r, c;
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 5; j++)	data[i][j] = 0;
	}

	while(1){
		printf("\n\n----------------------------");
		printf("\nPick a task :\n-------------");
		printf("\n  1 for INSERT\n  2 for DELETE\n  3 for UPDATE\n  4 for DISPLAY\n");
		printf("0 to EXIT\n");
		printf("\nEnter choice : ");
		scanf("%d", &ch);

		if(ch == 0)	break;
		else if(ch == 1 || ch == 2 || ch == 3)	cellinfo(&r, &c);

		switch(ch){
			case 1:		ins(&data[0][0], r, c); break;
			case 2:		del(&data[0][0], r, c); break;
			case 3:		upd(&data[0][0], r, c); break;
			case 4:		dsp(&data[0][0]);		break;
			default:	printf("INVALID entry! Retry");
		}
	}

	return 0;
}

void cellinfo(int *r, int *c){
	printf("\nEnter Store no\t\t: ");
	scanf("%d", r);
	printf("Enter Department no\t: ");
	scanf("%d", c);
	(*r)--; (*c)--;
}

void dsp(int *data){
	printf("\n\t\tD1\tD2\tD3\tD4\tD5\n");
	printf("---------------------------------------------------\n");
	for(int i = 0; i < 20; i++){
		printf("Store %d  \t", (i + 1));
		for(int j = 0; j < 5; j++)
			printf("%d\t", *(data + i*5 + j));
		printf("\n");
	}
}

void ins(int *data, int r, int c){
	printf("\nEnter value to INSERT\t: ");
	scanf("%d", &*(data + 5*r + c));
	printf("\n--INSERTED sucessfully!");
}

void del(int *data, int r, int c){
	*(data + 5*r + c) = 0;
	printf("\n--DELETED successfully!");
}

void upd(int *data, int r, int c){
	printf("\nStored value\t: %d\n", *(data + 5*r + c));
	printf("Enter new value\t: ");
	scanf("%d", &*(data + 5*r + c));
	printf("\n--UPDATED successfully!");
}

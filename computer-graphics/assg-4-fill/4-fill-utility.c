#include <stdio.h>
#include <GL/glut.h>

#define WW 640
#define WH 480

typedef struct points{
	int x, y;
	struct points *next;
}	polygon;

void gpInit();
void gpDisplay();
void drawPolygon(polygon *);

FILE *fp;

int main(int argc, char *argv[]){
	char fname[64];
	printf("\nEnter File Name : ");
	scanf("%s", fname);
	fp = fopen(fname, "r");
	if(fp == NULL){
		printf("  -- File not Found!\n");
		goto jump;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WW, WH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Polygon Filling");
	glutDisplayFunc(gpDisplay);
	gpInit();
	glutMainLoop();
	fclose(fp);

	jump: return 0;
}

void gpInit(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.35, 0.45);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WW, 0, WH);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void gpDisplay(){
	polygon *p = NULL, *curr = NULL;
	int x, y;
	while(!feof(fp)){
		fscanf(fp, "%d %d", &x, &y);
		if(x != -1){
			polygon *temp = (polygon *) malloc(sizeof(polygon));
			temp -> x = x;
			temp -> y = y;
			temp -> next = NULL;
			if(p == NULL){	p = temp; curr = p;	}
			else{
				curr -> next = temp;
				curr = curr -> next;
			}
		}
		else{
			drawPolygon(p);
			p = NULL; curr = NULL;
		}
	}
}

void drawPolygon(polygon *p){
	glBegin(GL_POLYGON);
	while(p != NULL){
		glVertex2i(p -> x, p -> y);
		p = p -> next;
	}
	glEnd();
	glFlush();
}
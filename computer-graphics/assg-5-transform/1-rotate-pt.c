#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define WW 640
#define WH 480

#define PI 3.141592654

void gpInit();
void gpMouse(int, int, int, int);
void drawPoint(int, int);
void drawLine(int, int, int, int);
void gpTimer();

void rotate(int, int, int, int, float);

FILE *fp;
int click = 0, xa = -1, ya = -1, xb = -1, yb = -1, xc = -1, yc = -1;

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WW, WH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Point Rotation");
	glutMouseFunc(gpMouse);
	glutTimerFunc(gpTimer);
	gpInit();
	glutMainLoop();
	fclose(fp);

	return 0;
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

void gpMouse(int button, int state, int x, int y){
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	if((button == GLUT_LEFT_BUTTON)  && (state == GLUT_DOWN)){
		click++; glColor3f(0.0, 0.35, 0.45);
		if(click % 3 != 0)drawPoint(x, y);
		if 	   (click % 3 == 1)	{	xa = x; ya = y;	}
		else if(click % 3 == 2)	{	xb = x; yb = y;	}
		else if(click % 3 == 0)	{
			xc = x; yc = y;
			float m1 = (float) (ya - yb) / (float) (xa - xb);
			float m2 = (float) (yc - yb) / (float) (xc - xb);
			float an = atan((m2 - m1) / (1 - m1 * m2));
			drawLine(xb, yb, xa, ya);
			rotate(xb, yb, xa, ya, an);
		}
	}
	if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)){
		glClear(GL_COLOR_BUFFER_BIT);
	}	glFlush();
}

void drawPoint(int x, int y){
	glPointSize(8.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawLine(int xa, int ya, int xb, int yb){
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(xa, ya);
	glVertex2i(xb, yb);
	glEnd();
}

void rotate(int cx, int cy, int px, int py, float an){
	float nmat[2] = {0, 0};
	float pmat[2] = {(float) px - cx, (float) py - cy};
	float rmat[2][2] = {{cos(an), -sin(an)}, {sin(an), cos(an)}};

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++)
			nmat[i] += rmat[i][j] * pmat[j];
	}

	nmat[0] += cx; nmat[1] += cy;
	if(an < 0)	rotate(cx, cy, (int) nmat[0], (int) nmat[1], PI);
	else{
		glColor3f(0.8f, 0.0f, 0.1f);
		int nx = (int) nmat[0], ny = (int) nmat[1];
		drawPoint(nx, ny);
		drawLine(cx, cy, nx, ny);
		glFlush();
	}
}
#include <stdio.h>
#include <GL/glut.h>

#define WW 640
#define WH 480

void gpInit();
void gpMouse(int, int, int, int);
void drawPoint(int, int);
void drawLine(int, int, int, int);

FILE *fp;
int click = 0, xa = -1, ya = -1, xb = -1, yb = -1, ix = -1, iy = -1;

int main(int argc, char *argv[]){
	char fname[64];
	printf("Enter File Name : ");
	scanf("%s", fname);
	fp = fopen(fname, "w+");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WW, WH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Polygon Drawing");
	glutMouseFunc(gpMouse);
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
		click++; fprintf(fp, "%d %d\n", x, y);
		drawPoint(x, y);
		if(click == 1){
			ix = x;	iy = y;
			xa = x; ya = y;
		}
		else{
			if(click != 2){		xa = xb; ya = yb;	}
			xb = x; yb = y;
			drawLine(xa, ya, xb, yb);
		}
	}
	if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)){
		if(ix != -1){
			if(click != 1)	drawLine(xb, yb, ix, iy);
			fprintf(fp, "%d %d\n", ix, iy);
			fprintf(fp, "%d %d\n", -1, -1);
		}
		click = 0;
		xa = ya = xb = yb = ix = iy = -1;
	}	glFlush();
}

void drawPoint(int x, int y){
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawLine(int xa, int ya, int xb, int yb){
	glBegin(GL_LINES);
	glVertex2i(xa, ya);
	glVertex2i(xb, yb);
	glEnd();
}
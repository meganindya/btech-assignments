#include <stdio.h>
#include <GL/glut.h>

#define WW 640
#define WH 480

void gpInit();
void gpPolygon();
void gpMouse(int, int, int, int);
void drawLine(int, int, int, int);

void boundaryFill(int, int, float *);
void setPixel(int, int, float *);

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
	glutCreateWindow("Boundary Filling");
	glutDisplayFunc(gpPolygon);
	glutMouseFunc(gpMouse);
	gpInit();
	glutMainLoop();
	fclose(fp);

	jump: return 0;
}

void gpInit(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WW, 0, WH);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void gpPolygon(){
	int xa, ya, xb, yb, pass = 0;
	while(fscanf(fp, "%d", &xb) == 1){
		fscanf(fp, "%d", &yb);
		if(xb == -1){	pass = 0; continue;	}
		pass++;
		if(pass == 1){	xa = xb; ya = yb;	}
		else{
			drawLine(xa, ya, xb, yb);
			xa = xb; ya = yb;
		}
	}
	glFlush();
}

void gpMouse(int button, int state, int x, int y){
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	if((button == GLUT_LEFT_BUTTON)  && (state == GLUT_DOWN)){
		float col[3] = {0.0, 0.35, 0.45};
		boundaryFill(x, y, col);
	}
	if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)){
		glClear(GL_COLOR_BUFFER_BIT);
		rewind(fp);
		gpPolygon();
	}	glFlush();
}

void drawLine(int xa, int ya, int xb, int yb){
	glBegin(GL_LINES);
	glVertex2i(xa, ya);
	glVertex2i(xb, yb);
	glEnd();
}

void boundaryFill(int x, int y, float *col){
	struct{ GLubyte r, g, b; } pixel;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
	if(pixel.r == 255 && pixel.g == 255 && pixel.b == 255){
		setPixel(x, y, col);
		if(x + 1 < WW)	boundaryFill(x + 1, y, col);
		if(x - 1 > 0)	boundaryFill(x - 1, y, col);
		if(y + 1 < WH)	boundaryFill(x, y + 1, col);
		if(y - 1 > 0)	boundaryFill(x, y - 1, col);
	}
}

void setPixel(int x, int y, float *col){
    glColor3fv(col);
	glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
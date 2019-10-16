#include <GL/glut.h>

void gpMouse(int, int, int, int);
void drawLineBRE();
void drawPoint(int, int, float);
void gpInit();

int click = 0, xa = 0, ya = 0, xb = 0, yb = 0;

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line Drawing using Bresenham's Algorithm");
	glutMouseFunc(gpMouse);
	gpInit();
	glutMainLoop();
}

void gpMouse(int button, int state, int x, int y){
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		glClear(GL_COLOR_BUFFER_BIT);
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		if((click % 2) == 0){	xa = x; ya = y;	}
		else				{	xb = x; yb = y; drawLineBRE();	}
		drawPoint(x, y, 9.0); click++;
	}	glFlush();
}

void drawLineBRE(){
	int dely = yb - ya, delx = xb - xa, sx = 1, sy = 1;
	if(delx < 0)	sx = -1;	delx = abs(delx);
	if(dely < 0)	sy = -1;	dely = abs(dely);
	int p = 2 * dely - delx;
	if((dely - delx) > 0){
		while(ya != yb){
			drawPoint(xa, ya, 6.0);
			ya += sy;
			if(p > 0){
				xa += sx;
				p -= 2 * dely;
			}	p += 2 * delx;
		}
	}
	else{
		while(xa != xb){
			drawPoint(xa, ya, 6.0);
			xa += sx;
			if(p > 0){
				ya += sy;
				p -= 2 * delx;
			}	p += 2 * dely;
		}
	}
}

void drawPoint(int x, int y, float s){
	glPointSize(s);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void gpInit(){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glEnable(GL_POINT_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

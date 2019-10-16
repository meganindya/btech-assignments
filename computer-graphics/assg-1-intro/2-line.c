#include <stdio.h>
#include <GL/glut.h>

int click = 0, xa = 0, ya = 0, xb = 0, yb = 0;

void myInit(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.5);
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void drawPoint(int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawLine(){
	glBegin(GL_LINES);
	glVertex2f(xa, ya);
	glVertex2f(xb, yb);
	glEnd();
}

void myMouse(int button, int state, int x, int y){
	y= glutGet(GLUT_WINDOW_HEIGHT) - y;
	if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		glClear(GL_COLOR_BUFFER_BIT);
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		drawPoint(x, y);
		if((click % 2) == 0){
			xa = x;
			ya = y;
			click++;
		}
		else{
			xb = x;
			yb = y;
			click++;
			drawLine();
		}
	}
	glFlush();
}

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Frog Program");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	myInit();
	glutMainLoop();
}

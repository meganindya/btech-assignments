#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

void gpDisplay();
void gpMouse(int, int, int, int);
void drawParabola(int, int, int, int);
void drawPoint(int, int, float);
void gpInit();

int xpos = 0, ypos = 0, dir = 0, click = 0;

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Parabola Drawing Algorithm");
	glutDisplayFunc(gpDisplay);
	glutMouseFunc(gpMouse);
	gpInit();
	glutMainLoop();
}

void gpDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void gpMouse(int button, int state, int x, int y){
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)){
		glClear(GL_COLOR_BUFFER_BIT);
		click = 0;
	}
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		if(click % 2 == 0){
			xpos = x; ypos = y;
			drawPoint(x, y, 2.0);
		}
		else if(click % 2 == 1){
			if(abs(y) > abs(x)){
				drawPoint(xpos, y, 2.0);
				drawParabola(xpos, ypos, y - ypos, 1);
			}
			else{
				drawPoint(x, ypos, 2.0);
				drawParabola(xpos, ypos, x - xpos, 0);
			}
		}	click++;
	}
	glFlush();
}

void drawParabola(int cx, int cy, int a, int d){
	int x = 0, y = 0, sx = 1, sy = 1, lt;
	if(d == 0){
		if(a < 0){
			sx = -1;
			lt = cx;
		}
		else	lt = 640 - cx;
		int p = 1 - 2 * a; a = abs(a);
		while(y < 2 * a){
    		drawPoint(cx + sx * x, cy + y, 2.0);
    		drawPoint(cx + sx * x, cy - y, 2.0);
    		if(p > 0){	p -= 4 * a; x++;	}
    		y ++; p += 2 * y + 3;
    	}
    	p = y * (y + 1) - (4 * a * (x - 1));
    	while(lt--){
    		drawPoint(cx + sx * x, cy + y, 2.0);
    		drawPoint(cx + sx * x, cy - y, 2.0);
    		if(p > 0){	p += 2 * y; y++;	}
    		x++; p -= 4 * a;
    	}
	}
	else{
		if(a < 0)	sy = -1;
	}
}

void drawPoint(int x, int y, float s){
	glPointSize(s);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void gpInit(){
	glClearColor(1.0, 1.0, 0.5, 1.0);
	glColor3f(0.0, 0.35, 0.45);
	glEnable(GL_POINT_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

void gpDisplay();
void gpMouse(int, int, int, int);
void drawCircle(int, int, int);
void drawPoint(int, int, float);
void gpInit();

int xpos = 0, ypos = 0, click = 0; float r = 0;

void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Circle Drawing Algorithm");
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
		else{
			float dx = x - xpos, dy = y - ypos;
			r = sqrt(dx * dx + dy * dy);
			drawCircle(xpos, ypos, r);
		}	click++;
	}
	glFlush();
}

void drawCircle(int cx, int cy, int rad){
    if(rad == 0){
    	glColor3f(1.0, 1.0, 1.0);
    	drawPoint(cx, cy, 5.0);
    	return;
    }
    glColor3f(0.0, 0.0, 0.0);
    int x = rad, y = 0, dx = 1, dy = 1;
    int p = dx - (rad << 1);
    while (x >= y){
    	for(int i = -1; i <= 1; i += 1)
    		for(int j =  -1; j <= 1; j += 1){
    			drawPoint(cx + x * i, cy + y * j, 2.0);
    			drawPoint(cx + y * i, cy + x * j, 2.0);
    		}
        if (p <= 0)	{	y++; p += dy; dy += 2;	}
        else		{	x--; dx += 2; p += dx - (rad << 1);	}
    }
    drawCircle(cx, cy, rad - 1);
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

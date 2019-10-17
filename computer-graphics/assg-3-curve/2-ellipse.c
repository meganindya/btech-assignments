#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

void gpDisplay();
void gpMouse(int, int, int, int);
void drawEllipse(int, int, int, int);
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
			drawEllipse(xpos, ypos, r * 2, r);
		}	click++;
	}
	glFlush();
}

void drawEllipse(int x, int y,int rx,int ry)
{
	int curr_x=0, curr_y=ry;
	int next_x,next_y;
	float mid_y, p1=(ry*ry)-(rx*rx*ry)+0.25*rx*rx;
	float slope=(-2*curr_x*ry*ry)/(2*curr_y*rx*rx);
	while(slope>-1)
	{
		drawPoint(curr_x+x,curr_y+y, 2.0);
		drawPoint(-curr_x+x,curr_y+y, 2.0);
		drawPoint(curr_x+x,-curr_y+y, 2.0);
		drawPoint(-curr_x+x,-curr_y+y, 2.0);
		next_x=curr_x+1;
		mid_y= curr_y-0.5;
		if(p1>0)
			next_y=curr_y-1;
		else
			next_y=curr_y;
		p1=p1+2*ry*ry*(curr_x+1)+ry*ry+rx*rx*((next_y-0.5)*(next_y-0.5)-(curr_y-0.5)*(curr_y-0.5));
		curr_x=next_x;
		curr_y=next_y;
		slope=(-2*curr_x*ry*ry)/(2*curr_y*rx*rx);
		
	}
	float p2=p1;
	while(curr_y>=0)
	{
		drawPoint(curr_x+x,curr_y+y, 2.0);
		drawPoint(-curr_x+x,curr_y+y, 2.0);
		drawPoint(curr_x+x,-curr_y+y, 2.0);
		drawPoint(-curr_x+x,-curr_y+y, 2.0);
		next_y=curr_y-1;
		if(p2<=0)
			next_x=curr_x+1;
		else
			next_x=curr_x;
		p2=p2-2*rx*rx*(curr_y-1)+rx*rx+ry*ry*((next_x+0.5)*(next_x+0.5)-(curr_x+0.5)*(curr_x+0.5));
		curr_x=next_x;
		curr_y=next_y;
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
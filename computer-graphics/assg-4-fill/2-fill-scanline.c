#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define maxHt 800
#define maxWd 600
#define maxVer 10000

FILE *fp;

typedef struct edgebucket
{
    int ymax;
    float xofymin;
    float slopeinverse;
}EdgeBucket;

typedef struct edgetabletuple
{
    int countEdgeBucket;
    EdgeBucket buckets[maxVer];
}EdgeTableTuple;

EdgeTableTuple EdgeTable[maxHt]={0}, ActiveEdgeTuple={0};

void insertionSort(EdgeTableTuple *ett)
{
    int i,j;
    EdgeBucket temp;
	for (i = 1; i < ett->countEdgeBucket; i++)
    {
        temp.ymax = ett->buckets[i].ymax;
        temp.xofymin = ett->buckets[i].xofymin;
        temp.slopeinverse = ett->buckets[i].slopeinverse;
        j = i - 1;
		while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0))
		{
			ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
			ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
			ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
			j = j - 1;
		}
		ett->buckets[j + 1].ymax = temp.ymax;
		ett->buckets[j + 1].xofymin = temp.xofymin;
		ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
    }
}

void storeEdgeInTuple (EdgeTableTuple *receiver,int ym,int xm,float slopInv)
{
    (receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
    (receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
    (receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;
    insertionSort(receiver);
	(receiver->countEdgeBucket)++;
}

void storeEdgeInTable (int x1,int y1, int x2, int y2)
{
    float m,minv;
    int ymaxTS,xwithyminTS, scanline;
	if (x2==x1)
        minv=0.000000;
    else
    {
    m = ((float)(y2-y1))/((float)(x2-x1));
	// horizontal lines are not stored in edge table
    if (y2==y1)
        return;
	minv = (float)1.0/m;
    }
	if (y1>y2)
    {
        scanline=y2;
        ymaxTS=y1;
        xwithyminTS=x2;
    }
    else
    {
        scanline=y1;
        ymaxTS=y2;
        xwithyminTS=x1;
    }
    storeEdgeInTuple(&EdgeTable[scanline],ymaxTS,xwithyminTS,minv);
}

void removeEdgeByYmax(EdgeTableTuple *Tup,int yy)
{
    int i,c;
    for (i=0; i< Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].ymax == yy)
        {
			for ( c = i ; c < Tup->countEdgeBucket -1 ; c++ )
            {
                Tup->buckets[c].ymax =Tup->buckets[c+1].ymax;
                Tup->buckets[c].xofymin =Tup->buckets[c+1].xofymin;
                Tup->buckets[c].slopeinverse = Tup->buckets[c+1].slopeinverse;
            }
            Tup->countEdgeBucket--;
            i--;
        }
    }
}

void updatexbyslopeinv(EdgeTableTuple *Tup)
{
    int i;
	for (i=0; i<Tup->countEdgeBucket; i++)
        (Tup->buckets[i]).xofymin =(Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
}


void ScanlineFill()
{
    int i, j;
    for (i=0; i<maxHt; i++)
    {
		for (j=0; j<EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple,EdgeTable[i].buckets[j].
            ymax,EdgeTable[i].buckets[j].xofymin,
            EdgeTable[i].buckets[j].slopeinverse);
        }
        removeEdgeByYmax(&ActiveEdgeTuple, i);
		insertionSort(&ActiveEdgeTuple);
		int x[ActiveEdgeTuple.countEdgeBucket];
		for(j=0;j<ActiveEdgeTuple.countEdgeBucket;j++)
			x[j]=(int)(ActiveEdgeTuple.buckets[j].xofymin);
		for(j=0;j<ActiveEdgeTuple.countEdgeBucket;j++)
		{
			glColor3f(0.0f,0.35f,0.45f);
			glBegin(GL_LINES);
            glVertex2i(x[j],i);
            glVertex2i(x[j+1],i);
            glEnd();
            glFlush();
			j++;
		}
		updatexbyslopeinv(&ActiveEdgeTuple);
	}
}

void myInit(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0,maxHt,maxWd,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawPoly()
{
	glColor3f(0.0f,0.0f,0.0f);
    int count = 0,x1,y1,x2,y2,x,y;
    rewind(fp);
    while(!feof(fp) )
    {
        count++;
        if (count>2)
        {
            x1 = x2;
            y1 = y2;
            count=2;
        }
        if (count==1)
        {
            fscanf(fp, "%d,%d", &x1, &y1);
			x=x1;
			y=y1;
        }
        else
        {
            fscanf(fp, "%d,%d", &x2, &y2);
            if(x2==0 && y2==0)
            {        
                     fscanf(fp, "%d,%d", &x1, &y1);
                     fscanf(fp, "%d,%d", &x2, &y2);
            }
            glBegin(GL_LINES);
            glVertex2i( x1, y1);
            glVertex2i( x2, y2);
            glEnd();
            storeEdgeInTable(x1, y1, x2, y2);
			glFlush();
        }
    }
}

void draw(void)
{
    drawPoly();
    ScanlineFill();
}

int main(int argc, char** argv)
{
	char fname[64];
    printf("\nEnter File Name : ");
    scanf("%s", fname);
    fp = fopen(fname, "r");
    if(fp == NULL){
        printf("  -- File not Found!\n");
        return 0;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(maxHt,maxWd);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Scanline filled");
    myInit();
    glutDisplayFunc(draw);
	glutMainLoop();
    fclose(fp);
}

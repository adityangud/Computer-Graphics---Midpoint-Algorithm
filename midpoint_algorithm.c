#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int xCenter, yCenter, radius;
float theta1, theta2;
int ch;
int c,d;
void drawCircle(float,float,float);
void drawArc(float,float,float,float,float);

void mouse(int btn, int state, int x, int y)
{
    static int count=0;
    float temp,rs;
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {count++;
        if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && (count%2==1) )
        {
            xCenter=x; yCenter=499-y;
        }
        if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&
                ((count%2==0)&&(count!=0)))
        {
            c=x; d=499-y;
            rs=(c-xCenter)*(c-xCenter)+(d-yCenter)*(d-yCenter);
            temp=sqrt(abs(rs));
            radius=temp;
            if(ch == 2)
            {
                printf("\nEnter theta1 and theta2: \n");
                scanf("%f %f",&theta1,&theta2);
                drawArc((float)xCenter,(float)yCenter,theta1,
                        theta2,radius);
            } else {
                drawCircle((float)xCenter,(float)yCenter,radius);
                glFlush();
            }
        }
    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        exit(1);
    }
}

void drawpoint(int x, int y)
{
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void drawArc(float xCenter, float yCenter,float theta1,float theta2,float
        radius)
{
    if(theta1 > 360)
        while(theta1 >=360)
            theta1-=360;
    if(theta2 > 360)
        while(theta2 >=360)
            theta2-=360;
    if(theta1 > theta2)
    {
        for(float i = 0; i<=3.1417*theta2/180.0; i = i+0.005)
            drawpoint(xCenter+radius*cos(i), yCenter+radius*sin(i));
        for(float i = 3.1417*theta1/180.0; i<=2*3.1417; i = i+0.005)
            drawpoint(xCenter+radius*cos(i), yCenter+radius*sin(i));
    }
    else
        for(float i = 3.1417*theta1/180.0; i<=3.1417*theta2/180.0; i = i+0.005)
            drawpoint(xCenter+radius*cos(i), yCenter+radius*sin(i));
    glFlush();
}

void circlePlotPoints(int x, int y)
{
    drawpoint(xCenter + x, yCenter + y);
    drawpoint(xCenter - x, yCenter + y);
    drawpoint(xCenter + x, yCenter - y);
    drawpoint(xCenter - x, yCenter - y);
    drawpoint(xCenter + y, yCenter + x);
    drawpoint(xCenter - y, yCenter + x);
    drawpoint(xCenter + y, yCenter - x);
    drawpoint(xCenter - y, yCenter - x);
}

void drawCircle(float xCenter, float yCenter, float radius)
{
    int x = 0;
    int y = radius;
    int p = 1 - radius;
    while(x < y) {
        x++;
        if(p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x-y) + 1;
        }
        circlePlotPoints(x, y);
    }
}

void display()
{
    glFlush();
}

void myinit()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

void main(int argc, char** argv)
{
    printf("1.Circle 2.Arc 3.Exit \n");
    scanf("%d",&ch);
    if(ch !=1 && ch!=2 )
        exit(0);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Bresenham's circle");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    myinit();
    glutMainLoop();
}

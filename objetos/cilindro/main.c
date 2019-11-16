#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

int win, win2;
int needsLightUpdate = GL_TRUE;
int useLighting = GL_TRUE;
int useSpecularTexture = GL_FALSE;
int useTexture = GL_FALSE;
int useHighRes = GL_FALSE;
int usePattern = GL_FALSE;
int moveLight = GL_FALSE;
int moveObject = GL_FALSE;

int drawObj = 0, maxObj = 2;
GLfloat lightRotX, lightRotY;
GLfloat objectRotX, objectRotY;
int curx, cury, width, height;

void
drawCylinder(int numMajor, int numMinor, float height, float radius)
{
    double majorStep = height / numMajor;
    double minorStep = 2.0 * M_PI / numMinor;
    int i, j;

    for (i = 0; i < numMajor; ++i)
    {
        GLfloat z0 = 0.5 * height - i * majorStep;
        GLfloat z1 = z0 - majorStep;

        glBegin(GL_TRIANGLE_STRIP);
        for (j = 0; j <= numMinor; ++j)
        {
            double a = j * minorStep;
            GLfloat x = radius * cos(a);
            GLfloat y = radius * sin(a);
            glNormal3f(x / radius, y / radius, 0.0);
            glTexCoord2f(j / (GLfloat) numMinor, i / (GLfloat) numMajor);
            glVertex3f(x, y, z0);

            glNormal3f(x / radius, y / radius, 0.0);
            glTexCoord2f(j / (GLfloat) numMinor, (i + 1) / (GLfloat) numMajor);
            glVertex3f(x, y, z1);
        }
        glEnd();
         /** Draw the circle on top of cylinder */
        glBegin(GL_POLYGON);
        float height = 0.1;
        float angle = 0.0;
        while( angle < 2*M_PI ) {
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + .1;
        }
        glVertex3f(radius, 0.0, height);
        glEnd();
    }
}
void
initialize(void)
{
    glMatrixMode(GL_PROJECTION);
    glFrustum(-0.50, 0.50, -0.50, 0.50, 1.0, 3.0);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0, 0.0, -2.0);

    glDepthFunc(GL_LEQUAL);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void
redraw(void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-2.0, -2.0, -1.0);
    glColor3f(1, 1, 1);
    glVertex3f(2.0, -2.0, -1.0);
    glColor3f(1, 1, 1);
    glVertex3f(2.0, 2.0, -1.0);
    glColor3f(1, 1, 1);
    glVertex3f(-2.0, 2.0, -1.0);
    glEnd();
    glEnable(GL_DEPTH_TEST);


    glPushMatrix();
    glRotatef(objectRotY, 0, 1, 0);
    glRotatef(objectRotX, 1, 0, 0);

    glColor3f(0.0, .65, 0);
    drawCylinder(6, 16, 1.0, 0.4);

    glTranslatef(0.0, 0.0, -.6);

    glColor3f(0.0, .65, 0);
    drawCylinder(6, 16, .3, .45);

    glPopMatrix();
}

void
motion(int x, int y)
{
    if (moveObject)
    {
        GLfloat dx = (y - cury) * 360.0 / height;
        GLfloat dy = (x - curx) * 360.0 / width;
        if (moveObject)
        {
            objectRotX += dx;
            if (objectRotX > 360)
                objectRotX -= 360;
            if (objectRotX < 0)
                objectRotX += 360;
            objectRotY += dy;
            if (objectRotY > 360)
                objectRotY -= 360;
            if (objectRotY < 0)
                objectRotY += 360;
        }
        curx = x;
        cury = y;
    }
    glutPostRedisplay();
}

void
mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        switch (button)
        {
        case GLUT_LEFT_BUTTON:
            moveObject = GL_TRUE;
            motion(curx = x, cury = y);
            break;
        case GLUT_MIDDLE_BUTTON:
            moveLight = GL_TRUE;
            motion(curx = x, cury = y);
            break;
        }
    }
    else if (state == GLUT_UP)
    {
        switch (button)
        {
        case GLUT_LEFT_BUTTON:
            moveObject = GL_FALSE;
            break;
        case GLUT_MIDDLE_BUTTON:
            moveLight = GL_FALSE;
            break;
        }
    }
}

void
display(void)
{
    redraw();
    glFlush();
    glutSwapBuffers();

}


int main (int argc, char **argv)
{
    int i;

    glutInit(&argc, argv);
    glutInitWindowSize(width = 500, height = 500);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    for (i = 1; i < argc; ++i)
    {

        exit(1);
    }
    win = glutCreateWindow("envphong");
    glutDisplayFunc(display);

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    initialize();
    glutMainLoop();
    return 0;
}

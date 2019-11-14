
#include <windows.h>
#include <GL\glut.h>
#include <math.h>

int n = 50;
float ang = 0;

void init(){
    glClearColor(0, 127, 255, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
}
void circle(float positionX){
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(255,255,255);
    glPushMatrix();

    glTranslatef(positionX,-1,0);
    glPushMatrix();
    glBegin(GL_POLYGON);
        for(i=0;i<n;i++){
            glVertex2f(0.2*cos(ang),0.2*sin(ang)); //aqui afeta o tamanho
            ang = ang+(2*M_PI)/n;
        }
    glEnd();

    glPopMatrix();
    glFlush();
}

void drawCloud(){
    float positionX;
    for (positionX=-1; positionX = 1; positionX+=0.25){
        circle(positionX);
    }
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (600 ,600);
    glutCreateWindow ("Flappy Bird");
    init();
    glutDisplayFunc (drawCloud);
    glutMainLoop ();
    return 0;
}

/**
 * Flappy Bird
 * Character - Bird
*/

#include <GL/glut.h>

float angX = 0;
float angY = 0;
float headRadius = 4.0;
float eyeRadius = 1.0;

void init(){
     glClearColor(0.0,0.0,0.0,0.0);
     glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-7,7,-7,7,-7,7);
     glPushMatrix();
}

void drawEyes() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-2.0, 1.5, 3.0);
    glutSolidSphere(eyeRadius, 20, 20);
    glTranslatef(0.0, 0.0, eyeRadius);
    glColor3f(0.0,0.0,0.0);
    glutSolidSphere(eyeRadius/2.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(2.0, 1.5, 3.0);
    glutSolidSphere(eyeRadius, 20, 20);
    glTranslatef(0.0, 0.0, eyeRadius);
    glColor3f(0.0,0.0,0.0);
    glutSolidSphere(eyeRadius/2.0, 20, 20);
    glPopMatrix();
}


void drawBody() {
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(headRadius,20,20);
    glPopMatrix();
}

void drawBeak() {
    glPushMatrix();
    glColor3f(1.0, 0.75, 0.0);
    glTranslatef(0.0, 0.0, 3);
    glRotatef(10, 1.0, 0.0, 0.0);
    glutSolidCone(1.0, 3.0, 20, 20);
    glPopMatrix();
}

/**
 * Desenha asa com 0.5 de altura de acordo com os parametros a seguir
 * @param {int} side        | 1 para asa direita, -1 para asa esquerda
 * @param {float} size      | valores positivos, escala que a asa sera desenhada (0.5 significa que a asa sera da metade - ou 50% - do tamanho padrao)
 * @param {float} yOffset   | offset em y, para desenhar camadas da asa em diferentes alturas
 * @param {float} r         | valor de r para definicao de cor rgb
 * @param {float} g         | valor de g para definicao de cor rgb
 * @param {float} b         | valor de b para definicao de cor rgb
 */
void drawWing(int side, float size, float yOffset, float r, float g, float b) { /// side: 1 or -1 (1 for right wing, -1 for left wing))
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(side*-3.5, 0.0 + yOffset, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(side*size*0.0, size*0.0, size*-1.5);
        glVertex3f(side*size*-2.0, size*0.0, size*-1.5);
        glVertex3f(side*size*-1.0, size*0.0, size*1.0);
        glVertex3f(side*size*0.0, size*0.0, size*1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(side*size*0.0, size*0.0, size*-1.5);
        glVertex3f(side*size*-2.0, size*0.0, size*-1.5);
        glVertex3f(side*size*-2.0, size*-0.5, size*-1.5);
        glVertex3f(side*size*0.0, size*-0.5, size*-1.5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(side*size*0.0, size*-0.5, size*-1.5);
        glVertex3f(side*size*-2.0, size*-0.5, size*-1.5);
        glVertex3f(side*size*-1.0, size*-0.5, size*1.0);
        glVertex3f(side*size*0.0, size*-0.5, size*1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(side*size*0.0, size*0.0, size*1.0);
        glVertex3f(side*size*-1.0, size*0.0, size*1.0);
        glVertex3f(side*size*-1.0, size*-0.5, size*1.0);
        glVertex3f(side*size*0.0, size*-0.5, size*1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(side*size*-2.0, size*0.0, size*-1.5);
        glVertex3f(side*size*-2.0, size*-0.5, size*-1.5);
        glVertex3f(side*size*-1.0, size*-0.5, size*1.0);
        glVertex3f(side*size*-1.0, size*0.0, size*1.0);
    glEnd();
    glPopMatrix();
}


void drawWings() {
    drawWing(1, 1.0, 0.0, 0.85, 0.85, 0.85);
    drawWing(-1, 1.0, 0.0, 0.85, 0.85, 0.85);
    drawWing(1, 0.8, 0.25, 0.90, 0.90, 0.90);
    drawWing(-1, 0.8, 0.25, 0.90, 0.90, 0.90);
    drawWing(1, 0.8, -0.25, 0.80, 0.80, 0.80);
    drawWing(-1, 0.8, -0.25, 0.80, 0.80, 0.80);
    drawWing(1, 0.65, 0.5, 0.95, 0.95, 0.95);
    drawWing(-1, 0.65, 0.5, 0.95, 0.95, 0.95);
}

void drawBird() {
    drawBody();
    drawEyes();
    drawBeak();
    drawWings();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    glPopMatrix();
    glPushMatrix();
    glRotatef(angX,1,0,0);
    glRotatef(angY,0,1,0);
    drawBird();
    glFlush();
}

void transformacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angX-=15;
           break ;
        case GLUT_KEY_DOWN :
           angX+=15;
           break ;
        case GLUT_KEY_LEFT :
           angY-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angY+=15;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Bird");
     glutDisplayFunc(display);
     glutSpecialFunc(transformacoes);
     init();
     glutMainLoop();
}

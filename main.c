#include "objetos/bird/bird.c"
//#include "objetos/cano/cano.c"
#include <GL/glut.h>

GLfloat action = 0.0;

void init(){
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
  glClearColor(0.5,0.0,5.0,0.0);
  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
  glMatrixMode(GL_MODELVIEW);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-7,7,-7,7,-7,7);
  glPushMatrix();
  obj = gluNewQuadric();
  gluQuadricDrawStyle(obj,GLU_LINE);
}

extern void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-7,7,-7,7,-7,7);
    gluLookAt(1.0,1.0,1.0,
          0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
          0.0, 1.0, 0.0); //vetor view-up (V)
    glRotatef(angX,1,0,0);
    glRotatef(angY,0,1,0);
    drawBird(); //desenha um cubo
    glViewport(10, 0+action, 200, 200);    
    //glFlush();
    glutSwapBuffers();
}

void transformacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           action+=50;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

void queda(int value)
{
	action-=5;
	glutPostRedisplay();
	glutTimerFunc(30,queda, 1);
}

int main(int argc, char *argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50,50);
  glutInitWindowSize(800,800);
  glutCreateWindow("Bird");
  glutDisplayFunc(display);
  glutSpecialFunc(transformacoes);
  glutTimerFunc(150, queda, 1);
  init();
  glutMainLoop();
}
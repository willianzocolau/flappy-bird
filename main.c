#include <GL/glut.h>
#include "objetos/bird/bird.c"

GLUquadricObj *obj;

int objId = 1;
float angX = 15;
float angY = 70;
float soma;
int start = 0;
// Posição inicial do quadrado
GLfloat x1 = 5.0f;
GLfloat y1 = 1.0f;

GLfloat pan = 80;
GLsizei rsize = 50;

// Passo nas direções x e y
GLfloat xstep = 0;
GLfloat ystep = 0;

GLfloat panstep = 0;


// Medidas da janela
GLfloat windowWidth = 600;
GLfloat windowHeight = 600;


void init(){
  glClearColor(0.0,0.0,0.0,0.0);
  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-100,100,-100,100,-100,100);
  glPushMatrix();
  obj = gluNewQuadric();
  gluQuadricDrawStyle(obj,GLU_LINE);
}

void timerFunc(int value)
{
	// Direção oposta qdo atinge o canto direito ou esquerdo

	// Direção oposta qdo atinge o lado de cima ou de baixo
	if(y1 > x1 )
		ystep = -ystep;
    if(y1 <=-100){
        y1 = -10000;
    }
    if(y1 >=100){
        y1 = -10000;
    }

	// passo que movimenta o passaro
	y1 += ystep;
   pan -= panstep;
	// Redesenha a cena com as novas coordenadas
	glutPostRedisplay();
	glutTimerFunc(10,timerFunc, 1);
}
void parede(float altura, float direita){

  GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();

  glPopMatrix();
  glPushMatrix();

  glRotatef(90,1,0,0);
  glTranslatef(pan-direita, 0, -25+altura);

  gluCylinder(quadratic, 12, 12, 10, 32, 32);

  glPopMatrix();
  glPushMatrix();

  glRotatef(90,1,0,0);
  glTranslatef(pan-direita, 0, -235+altura);

  gluCylinder(quadratic, 10, 10, 220, 32, 32);


  glPopMatrix();
  glPushMatrix();

  glRotatef(-90,1,0,0);
  glTranslatef(pan-direita, 0, -25-altura);

  gluCylinder(quadratic, 12, 12, 10, 32, 32);

  glPopMatrix();
  glPushMatrix();

  glRotatef(-90,1,0,0);
  glTranslatef(pan-direita, 0, -235-altura);

  gluCylinder(quadratic, 10, 10, 220, 32, 32);
  soma +=50;
}

void colisao(){

}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
  glColor3f(0.0,0.0,1.0);

  //passaro
  glPopMatrix();
  glPushMatrix();
  glRotatef(angX,1,0,0);
  glRotatef(angY,0,1,0);
  glTranslatef(0, y1, 0);
  drawBird();
  //glutWireSphere(3,50,50);

  GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();

  //mapa
  glColor3f(0.0,0.8,0.0);
  parede(0, 0);
  parede(-10, -50);
  parede(-20, -100);
  parede(10, -150);
  parede(-30, -200);
  parede(0, -250);
  parede(-40, -300);
  parede(-10, -350);

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch (key){
    case '1' :
    start = 1;
    x1 = y1 + 20;
        ystep = 1;
        panstep = .5f;
        break ;
    default:
        break;
  }
  glutPostRedisplay() ;
}

void transformacoes(int key, int x, int y){
   switch (key){
      case GLUT_KEY_UP :
      start = 1;
         x1 = y1 + 20;
         ystep = 1;
         break ;
      case GLUT_KEY_DOWN :
         angX-=15;
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
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowPosition(50,50);
   glutInitWindowSize(600,600);
   glutCreateWindow("Objetos 3D - OpenGL");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(transformacoes);
   glutTimerFunc(10,timerFunc,1);
   init();
   glutMainLoop();
}

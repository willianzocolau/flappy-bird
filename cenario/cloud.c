#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL\glut.h>
#include <math.h>

int n = 50;
float ang = 0;

#define EOL '\n'

#ifndef OBJLIB_H_INCLUSO //Evitar que biblioteca seja carregada duas vezes
#define OBJLIB_H_INCLUSO

//Biblioteca para interpretar arquivo OBJ

typedef struct{
    float x,y,z;
}Vert;

typedef struct{
    Vert *verts;
    Vert norms;
    Vert *tex;
}Face;

typedef struct{
    Vert tam;
    Face *faces;
    int numFaces;
}Obj;
Obj *nuvem;
Obj *objCarrega(char* filename);
void objLibera(Obj *obj);
void objImprime(Obj *obj);

#endif

//#define DEBUG

//#define CENTRALIZAR

//#define NORMALIZAR

#ifndef OBJLIB_H_INCLUSO //Evitar que biblioteca seja carregada duas vezes
#define OBJLIB_H_INCLUSO


//Biblioteca para interpretar arquivo OBJ

typedef struct{
    float x,y,z;
}Vert;

typedef struct{
    Vert *verts;
    Vert norms;
    Vert *tex;
}Face;

typedef struct{
    Vert tam;
    Face *faces;
    int numFaces;
}Obj;

Obj *objCarrega(char* filename);
void objLibera(Obj *obj);
void objImprime(Obj obj);

#endif

#define NORM_TAM 0.8

int fSeekNewline(FILE* f){
    int c;
    do
        c = fgetc(f);
    while(c!=EOL && c!= EOF);
    return c;
}

Obj *objCarrega(char* filename){
    Obj *obj;

    char temTextura = 0;

    float x,y,z;

    Vert max, min;

    int res,i,j,k,l, nVerts = 0, nNorms = 0, nTex = 0;

    Vert *verts, *norms, *tex;

    printf("\n\nAbrindo arquivo: %s",filename);

    FILE *f = fopen(filename,"r");

    if (f == NULL){
        printf("\n\tFalha no carregamento!");
        return NULL;         //Erro no carregamento do arquivo
    }
    obj = (Obj*)malloc(sizeof(Obj));          //Aloca espaço - Objeto
    verts = (Vert*)malloc(sizeof(Vert));       //Aloca espaço - Vértices
    norms =  (Vert*) malloc(sizeof(Vert));       //Aloca espaço - Normais
    tex = (Vert*)malloc(sizeof(Vert));       //Aloca espaço - Texturas

    obj->faces = (Face*)malloc(sizeof(Face));  //Aloca espaço - Faces
    obj->numFaces = 0;

    if (obj   == NULL ||
        verts == NULL ||
        norms == NULL ||
        tex   == NULL ||
        obj->faces == NULL)
            return NULL;     //Erro na alocação

    do{
        res = getc(f);  //Pega caractere
        switch(res){
            case EOF:   //Chegou no fim do arquivo
                //printf("\n\tEncontrou EOF");
                break;
            case 'v':
            case 'V':
                res = getc(f);
                if (res == ' '){
                    fscanf(f,"%f %f %f",&x,&y,&z);
                    if (nVerts > 0){
                        verts = (Vert*) realloc(verts,sizeof(Vert)*(nVerts+1));
                        if (max.x < x) max.x = x; else if (min.x > x) min.x = x;
                        if (max.y < y) max.y = y; else if (min.y > y) min.y = y;
                        if (max.z < z) max.z = z; else if (min.z > z) min.z = z;
                    }else{
                        max.x = x; max.y = y; max.z = z;
                        min.x = x; min.y = y; min.z = z;
                    }
                    verts[nVerts].x = x;
                    verts[nVerts].y = y;
                    verts[nVerts].z = z;
                    #ifdef DEBUG
                        printf("\n\tVertice\t%f\t%f\t%f",verts[nVerts].x, verts[nVerts].y, verts[nVerts].z);
                    #endif
                    nVerts ++;

                    res = fSeekNewline(f);
                }else if (res == 'n' || res == 'N'){
                    fscanf(f,"%f %f %f",&x,&y,&z);
                    if (nNorms > 0)
                        norms = (Vert*)realloc(norms,sizeof(Vert)*(nNorms+1));
                    norms[nNorms].x = x;
                    norms[nNorms].y = y;
                    norms[nNorms].z = z;
                    #ifdef DEBUG
                        printf("\n\tNormal\t%f\t%f\t%f",norms[nNorms].x, norms[nNorms].y, norms[nNorms].z);
                    #endif
                    nNorms++;
                    res = fSeekNewline(f);
                }else if (res == 't' || res == 'T'){
                    temTextura = 1;
                    fscanf(f,"%f %f",&x,&y);
                    if (nTex > 0)
                        tex = (Vert*)realloc(tex,sizeof(Vert)*(nTex+1));
                    tex[nTex].x = x;
                    tex[nTex].y = y;
                    tex[nTex].z = 0;
                    #ifdef DEBUG
                        printf("\n\tTextura\t%f\t%f",tex[nTex].x, tex[nTex].y);
                    #endif
                    nTex++;
                    res = fSeekNewline(f);
                }
                break;
            case 'f':
            case 'F':
                #ifdef DEBUG
                    printf("\n\tFace");
                #endif

                if (obj->numFaces > 0)
                    obj->faces = (Face*)realloc(obj->faces,sizeof(Face)*(obj->numFaces+1));


                obj->faces[obj->numFaces].verts = (Vert*) malloc(sizeof(Vert)*3);
                //obj->faces[obj->numFaces].norms = malloc(sizeof(Vert)*3);

                if (temTextura)
                    obj->faces[obj->numFaces].tex = (Vert*) malloc(sizeof(Vert)*3);
                else
                    obj->faces[obj->numFaces].tex = NULL;

                l = 0;
                for(k=0;k<3;k++){
                    if (temTextura)
                        fscanf(f,"%d/%d/%d",&i,&l,&j);
                    else
                        fscanf(f,"%d//%d",&i,&j);

                    i--; j--; l--;
                    #ifdef DEBUG
                        printf("\n\t%d\t%d\t\t%d",k,i,j);
                    #endif
                    //Vert
                    obj->faces[obj->numFaces].verts[k].x = verts[i].x;
                    obj->faces[obj->numFaces].verts[k].y = verts[i].y;
                    obj->faces[obj->numFaces].verts[k].z = verts[i].z;
                    //Tex
                    if (temTextura){
                        obj->faces[obj->numFaces].tex[k].x  = tex[l].x;
                        obj->faces[obj->numFaces].tex[k].y  = tex[l].y;
                        obj->faces[obj->numFaces].tex[k].z  = 0;
                    }
                }
                //Norm
                obj->faces[obj->numFaces].norms.x = norms[j].x;
                obj->faces[obj->numFaces].norms.y = norms[j].y;
                obj->faces[obj->numFaces].norms.z = norms[j].z;

                obj->numFaces++;
                res = fSeekNewline(f);

                break;
            case '#':
            default:
                //printf("\nEncontrou outro: %c", res);
                res = fSeekNewline(f);
        }
    }while(res!=EOF);

    free(verts);

    fclose(f);
    printf("\n-OK!");

    obj->tam.x = (max.x-min.x)/2;
    obj->tam.y = (max.x-min.y)/2;
    obj->tam.z = (max.x-min.z)/2;

    #ifdef CENTRALIZAR
        printf("\n\tCentralizando...");
        x = (max.x - min.x)/2 + min.x;
        y = (max.y - min.y)/2 + min.y;
        z = (max.z - min.z)/2 + min.z;

        for (i=0;i<obj->numFaces;i++){
            for (j=0;j<3;j++){
                obj->faces[i].verts[j].x -= x;
                obj->faces[i].verts[j].y -= y;
                obj->faces[i].verts[j].z -= z;
            }
        }
    #else
        #ifdef NORMALIZAR
            printf("\n\tNormalizando...");
            x = (max.x - min.x);
            y = (max.y - min.y);
            z = (max.z - min.z);

            for (i=0;i<obj->numFaces;i++){
                for (j=0;j<3;j++){
                    obj->faces[i].verts[j].x = 2*NORM_TAM*(obj->faces[i].verts[j].x - min.x)/x - NORM_TAM;
                    obj->faces[i].verts[j].y = 2*NORM_TAM*(obj->faces[i].verts[j].y - min.y)/y - NORM_TAM;
                    obj->faces[i].verts[j].z = 2*NORM_TAM*(obj->faces[i].verts[j].z - min.z)/z - NORM_TAM;
                }
            }
        #endif
    #endif
    return obj;
}

void objLibera(Obj *obj){
    int i;
    for (i=0;i<obj->numFaces;i++){
        free (obj->faces[i].verts);
        //free (obj->faces[i].norms);
    }

    free(obj->faces);
    free(obj);
    obj = NULL;
}

void objImprime(Obj *obj){
    int i,j;
    Vert *v;
    for (i=0;i<obj->numFaces;i++){
        v = obj->faces[i].verts;
        printf("\nFace:\n\tx: %f\ty: %f\tz: %f",v[0].x,v[0].y,v[0].z);
        printf("\nFace:\n\tx: %f\ty: %f\tz: %f",v[1].x,v[1].y,v[1].z);
        printf("\nFace:\n\tx: %f\ty: %f\tz: %f",v[2].x,v[2].y,v[2].z);
    }
}
void circle(){

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(255,255,255);
    glDrawElements(GL_POLYGON, 98 , GL_UNSIGNED_INT, nuvem->faces->verts); //https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glDrawElements.xml

    glFlush();
}
void init(){
    glClearColor(0, 127, 255, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
}

int main ( int argc , char * argv [] ){
    Obj *nuvem;
    nuvem = objCarrega("C:/Users/aamgo/Desktop/abc/cloud.obj");
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (600 ,600);
    glutCreateWindow ("Flappy Bird");
    init();
    glutDisplayFunc (circle);
    glutMainLoop ();
    return 0;
}

#ifndef __AFFINES
#define __AFFINES

#include "stdio.h"
#include "stdlib.h"
#include "ppm.h"
#include "math.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include <time.h>

typedef struct {
    GLfloat posX, posY, posZ;
    GLfloat bras_gauche;
    GLfloat bras_droit;
    GLfloat main_gauche;
    GLfloat main_droite;
    GLfloat haut_corps;
    GLfloat rtete;
    GLfloat lui_meme;
} Playmobile;

GLfloat * translation (float a, float b, float c);
GLfloat * homothetie (float a, float b, float c);
void ballon();
void phalange();
void doigt();
void hand();
void pouce();
void bassin();
void jambe();
void bas();
void ventre();
void epaule();
void haut(Playmobile *p);
void playmobile(Playmobile *p,GLfloat x, GLfloat y, GLfloat z);
void cou();
void tete();
void une_main();
void bras();
void poigner();
void pied();
void sol();
void loadTexture(int index, char * filename);

void initPlaymobile(Playmobile *p, GLfloat x, GLfloat y, GLfloat z);
void updateRandomRotations(Playmobile *p , int mouvement);
void triangle(float angle);

#endif 
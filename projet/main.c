// gcc main.c opmat.c affines.c actions.c init.c VM_init.c axes.o  lumiere.o switch_blend.o  switch_light.o ppm.o -lm -lGL -lGLU -lglut -o test

#include "init.h"
#include "axes.h"
#include "affines.h"
#include "VM_init.h"
#include "opmat.h"
#include <stdio.h>

int blend = 0;
int light = 0;
GLfloat xrot = 0.0f;   
GLfloat yrot = 0.0f;   
GLfloat zrot = 0.0f;
GLfloat dz = -5.0f;
GLfloat angle = 0.0f;
int flagSens = 1;

GLfloat posX = 0.0f, posY = 5.0f, posZ = 20.0f;

GLfloat bras_gauche = 0.0f;
GLfloat bras_droit = 0.0f;
GLfloat main_gauche = 0.0f;
GLfloat main_droite = 0.0f;
GLfloat haut_corps = 0.0f;
GLfloat rtete = 0.0f;
GLfloat lui_meme = 0.0f;

GLfloat limite1 = 20.0f;
GLfloat limite2 = -20.0f;

Playmobile P1;
Playmobile P2;

GLuint textures[2]; 

char* tab[2] = {
 "./img/herbe.ppm",
 "./img/ballon.ppm"
};

GLvoid Modelisation()
{
  VM_init();
    
    glPushMatrix();
    {
      GLfloat * ma_translation = translation(0,-2.75,0);
      glMultMatrixf(ma_translation);
      sol();
    }
    glPopMatrix();
    glPushMatrix();
    {
      playmobile(&P1,P1.posX,P1.posY,P1.posZ);
    }
    glPopMatrix();
    glPushMatrix();
    {
      playmobile(&P2,P2.posX,P2.posY,P2.posZ);
      int mouvement = rand() % 17;
      updateRandomRotations(&P2, mouvement);
    }
    glPopMatrix();
    glPushMatrix();
    {
      GLfloat * ma_translation = translation(3,-1.75,10);
      glMultMatrixf(ma_translation);
      ballon();
    }
    glPopMatrix();

axes();
glutSwapBuffers();

}

int main(int argc, char **argv) 
{
    initPlaymobile(&P1, 0.0f, 0.0f, 0.0f);
    initPlaymobile(&P2, 5.0f, 0.0f, 0.0f);  

    notre_init(argc, argv, Modelisation);  

    glutMainLoop(); 
    return 0;
}
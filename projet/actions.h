#ifndef __ACTIONS
#define __ACTIONS

/* ascii codes for various special keys */
#include "affines.h"
#include "touches.h"
#include "switch_blend.h"
#include "switch_light.h"
#include <stdlib.h>

extern GLfloat posX_replica;
extern GLfloat posY_replica; 
extern GLfloat posZ_replica; 
extern GLfloat bras_gauche_replica; 
extern GLfloat bras_droit_replica;
extern GLfloat main_gauche_replica; 
extern GLfloat main_droite_replica; 
extern GLfloat haut_corps_replica; 
extern GLfloat rtete_replica; 

void touche_pressee(unsigned char key, int x, int y);
void touche_speciale(int key, int x, int y);

#endif


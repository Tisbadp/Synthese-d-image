#include "actions.h"

extern GLfloat xrot;
extern GLfloat yrot;
extern GLfloat zrot;
extern GLfloat dz;
extern int blend;
extern int light;
extern GLfloat angle;

extern GLfloat posX, posY, posZ;

extern GLfloat bras_gauche;
extern GLfloat bras_droit;
extern GLfloat main_gauche;
extern GLfloat main_droite;
extern GLfloat haut_corps;
extern GLfloat rtete;
extern GLfloat lui_meme;

int modeControle = 0;

extern GLfloat limite1;
extern GLfloat limite2;

extern Playmobile P1;

int lumiereAllumee = 1; 

void touche_pressee(unsigned char key, int x, int y)
{
    usleep(100);

    if (key == 'n'){
      modeControle = !modeControle; 
    }
    if (modeControle == 0) { 
        switch (key) {
        case 'w': 
          if(posZ + 1.0f < limite1) posZ += 1;
            break;
        case 's':  
          if(posZ - 1.0f > limite2) posZ -= 1;
            break;
        case 'a': 
          if(posX - 1.0f > limite2) posX -= 1;
            break;
        case 'd':  
          if(posX + 1.0f < limite1) posX += 1;
            break;
        case 'q':  
          if(posY + 1.0f < limite1) posY += 1;
            break;
        case 'e':  
          if(posY - 1.0f > limite2) posY -= 1;
            break;
        case ESCAPE:
            exit(1);
            break;
        case TOUCHE_MIN_B: blend =  switch_blend(blend); break;
        case TOUCHE_MIN_L: light = switch_light(light); break;
        case 'u':  // Ajout de la touche L pour allumer/éteindre les lumières
            lumiereAllumee = !lumiereAllumee;  // Basculer l'état de la lumière
            break;
        }
    }
    else { 
        switch (key) {
            case TOUCHE_q:
              if (angle > 0)
                angle -= 10.0f;
                break;
            case TOUCHE_d:
              if (angle <= 70)
                angle += 10.0f;
                break;
            case ESCAPE:
              exit(1);
              break;
            case 'z': dz +=1; break;
            case 'Z': dz -=1; break;
            case ESPACE: xrot = 0.0f; yrot = 0.0f; break;
            case TOUCHE_MIN_B: blend =  switch_blend(blend); break;
            case TOUCHE_MIN_L: light = switch_light(light); break;
            case 'r': P1.bras_gauche = P1.bras_droit = P1.rtete = P1.main_gauche = P1.main_droite = P1.haut_corps = P1.lui_meme = 0; break;
            case 'g': P1.lui_meme += 10; break;
            case 'G': P1.lui_meme -= 10; break;
            case 'p': P1.bras_gauche -= 10; break;
            case 'P': P1.bras_gauche += 10; break;
            case 'o': P1.bras_droit -= 10; break;
            case 'O': P1.bras_droit += 10; break;
            case 't': P1.rtete += 10; break;
            case 'T': P1.rtete -= 10; break;
            case 'i': P1.main_gauche += 10; break;
            case 'I': P1.main_gauche -= 10; break;
            case 'y': P1.main_droite += 10; break;
            case 'Y': P1.main_droite -= 10; break;
            case 'm': if (P1.haut_corps < 90) P1.haut_corps += 10; break;
            case 'M': if (P1.haut_corps > 0) P1.haut_corps -= 10; break;
            case 'u':  // Ajout de la touche L pour allumer/éteindre les lumières
            lumiereAllumee = !lumiereAllumee;  // Basculer l'état de la lumière
            break;
        }
    }
    
}

void touche_speciale(int key, int x, int y){
    usleep(100);
    if (modeControle == 0) { 
      switch (key) {
          case GLUT_KEY_UP: xrot += 10; break;
          case GLUT_KEY_DOWN: xrot -= 10;  break;
          case GLUT_KEY_LEFT: yrot += 10; break;
          case GLUT_KEY_RIGHT: yrot -= 10; break;
      }
    }
    else{
     switch (key) {
        case GLUT_KEY_LEFT: if(P1.posX - 1.0f > limite2) P1.posX -= 1;break;
        case GLUT_KEY_RIGHT: if(P1.posX + 1.0f < limite1) P1.posX += 1; break;
        case GLUT_KEY_UP: if(P1.posZ + 1.0f < limite1) P1.posZ += 1; break;
        case GLUT_KEY_DOWN: if(P1.posZ - 1.0f > limite2) P1.posZ -= 1;  break;
      }
  }
}


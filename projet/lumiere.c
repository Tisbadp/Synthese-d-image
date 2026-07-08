#include "lumiere.h"
#include <GL/glut.h>  

#define LUMIERE_POSITIONNELLE 1.0
#define LUMIERE_DIRECTIONNELLE 0.0

extern int lumiereAllumee;

void lumiere() {
    glEnable(GL_LIGHT0);  
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glEnable(GL_COLOR_MATERIAL);  // Utiliser les couleurs des matériaux pour l'éclairage
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Lumière ambiante (avec une valeur plus raisonnable)
    GLfloat ambient_light[] = {0.2f, 0.2f, 0.2f, 1.0f};  // Faible lumière ambiante pour un éclairage réaliste
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
    
    // Lumière positionnelle (Spotlight) - GL_LIGHT0
    GLfloat diffuse_light[] = {1.0f, 1.0f, 0.0f, 1.0f};  // Jaune pour l'éclairage
    GLfloat specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Blanc pour la lumière spéculaire
    GLfloat position0[] = {0.0, 0.0, 10.0, LUMIERE_POSITIONNELLE}; // Position de la lumière
    GLfloat spot_dir[] = {0.0, 0.0, -1.0}; // Direction du spotlight (vers le bas)
    
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);  // Angle du cône du spotlight
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);  // Couleur diffuse
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);  // Couleur spéculaire
    glLightfv(GL_LIGHT0, GL_POSITION, position0);  // Position de la lumière
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);  // Direction du spotlight

    // Lumière directionnelle (GL_LIGHT3)
    GLfloat direction[] = {10.0, 0.0, -10.0, LUMIERE_DIRECTIONNELLE};  // Direction de la lumière
    GLfloat diffuse_light1[]  = {1.0f, 1.0f, 1.0f, 1.0f};  // Couleur de la lumière directionnelle
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse_light1);  // Diffuse
    glLightfv(GL_LIGHT3, GL_POSITION, direction);  // Position de la lumière (doit être directionnelle)

    // Configurations supplémentaires
    glEnable(GL_LIGHT0);  // Assurez-vous que cette lumière est activée
    glEnable(GL_LIGHT3);  // Assurez-vous que la lumière directionnelle est activée

        if (lumiereAllumee) {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT3);
    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT3);
    }
}

/*
glEnable(GL_DEPTH_TEST);  
    glEnable(GL_LIGHTING);  

    glEnable(GL_LIGHT0);  
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Lumière ambiante
    GLfloat ambient_light[] = {1.2f, 0.2f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
    
    // Lumière positionnelle
    GLfloat diffuse_light[] = {1.0f, 1.0f, 0.0f, 1.0f};
    GLfloat specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position0[] = {0.0, 10.0, 10.0, LUMIERE_POSITIONNELLE};
    GLfloat spot_dir[] = {0.0, 0.0, -1.0, LUMIERE_POSITIONNELLE};
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position0); 
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);

    // Lumière directionnelle
    GLfloat direction[] = {10.0, 0.0, -10.0, LUMIERE_DIRECTIONNELLE};
    GLfloat diffuse_light1[]  = {1.0f, 1.0f, 1.0f, 1.0f};  
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT3, GL_POSITION, direction);*/
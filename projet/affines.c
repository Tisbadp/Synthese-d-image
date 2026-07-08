#include "affines.h"
#include <unistd.h>

extern int flagSens;
extern GLfloat angle;

extern GLfloat posX, posY, posZ;

extern GLfloat bras_gauche;
extern GLfloat bras_droit;
extern GLfloat main_gauche;
extern GLfloat main_droite;
extern GLfloat haut_corps;
extern GLfloat rtete;
extern GLfloat lui_meme;

extern GLfloat limite1;
extern GLfloat limite2;

extern char* tab[];

extern GLuint textures[];

TEXTURE_STRUCT *readPpm(char *ppmFileName);
unsigned char *rgb2rgba(TEXTURE_STRUCT *texture);


GLfloat * translation (float a, float b, float c) {
    GLfloat * res = (GLfloat *)malloc(sizeof(GLfloat) * 16);
    res[0] = (GLfloat)1.0f;
    res[1] = (GLfloat)0.0f;
    res[2] = (GLfloat)0.0f;
    res[3] = (GLfloat)0.0f;
    res[4] = (GLfloat)0.0f;
    res[5] = (GLfloat)1.0f;
    res[6] = (GLfloat)0.0f;
    res[7] = (GLfloat)0.0f;
    res[8] = (GLfloat)0.0f;
    res[9] = (GLfloat)0.0f;
    res[10] = (GLfloat)1.0f;
    res[11] = (GLfloat)0.0f;
    res[12] = (GLfloat)a;
    res[13] = (GLfloat)b;
    res[14] = (GLfloat)c;
    res[15] = (GLfloat)1.0f;
    return res;
}

GLfloat * homothetie (float a, float b, float c) {
    GLfloat * res = (GLfloat *)malloc(sizeof(GLfloat) * 16);
    res[0] = (GLfloat)a;
    res[1] = (GLfloat)0.0f;
    res[2] = (GLfloat)0.0f;
    res[3] = (GLfloat)0.0f;
    res[4] = (GLfloat)0.0f;
    res[5] = (GLfloat)b;
    res[6] = (GLfloat)0.0f;
    res[7] = (GLfloat)0.0f;
    res[8] = (GLfloat)0.0f;
    res[9] = (GLfloat)0.0f;
    res[10] = (GLfloat)c;
    res[11] = (GLfloat)0.0f;
    res[12] = (GLfloat)0.0f;
    res[13] = (GLfloat)0.0f;
    res[14] = (GLfloat)0.0f;
    res[15] = (GLfloat)1.0f;
    return res;
}

void loadTexture(int index, char *filename) {
    // Lecture de la texture à partir du fichier PPM
    TEXTURE_STRUCT *texture = readPpm(filename);

    if (!texture) {
        printf("Failed to load texture\n");
        return;
    }

    // Création d'une texture OpenGL
    glGenTextures(1, &textures[index]);
    printf("ID de texture généré: %d\n", textures[index]);

    glBindTexture(GL_TEXTURE_2D, textures[index]);

    // Définir les paramètres de la texture (filtrage, répétition, etc.)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    unsigned char* rgbaData = rgb2rgba(texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData);

    free(rgbaData);

    // Libération de la texture lue en mémoire
    free(texture->data);
    free(texture);
    printf("Texture loaded successfully!\n");
}

void ballon() {
    glPushMatrix();
    {
        // Activer la texture
        glEnable(GL_TEXTURE_2D);  
        glBindTexture(GL_TEXTURE_2D, textures[1]);  // Lier la texture du ballon

        // Assurez-vous que la couleur ne masque pas la texture
        glColor3f(1.0f, 1.0f, 1.0f);  

        // Définir les paramètres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Dessiner la sphère avec la texture
        glutSolidSphere(1.0, 32, 32);

        // Désactiver la texture après le dessin
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}



void sol() {
    glPushMatrix();
    {
        GLfloat largeurSol = limite1 - limite2;

        // Active le test de profondeur et la texture
        glEnable(GL_TEXTURE_2D);  

        glBindTexture(GL_TEXTURE_2D, textures[0]);  // Lier la texture chargée
        glColor3f(1.0f, 1.0f, 1.0f);  // Assurez-vous que la couleur ne masque pas la texture

        glBegin(GL_QUADS);
        
        // Définir les coordonnées de texture et les sommets du sol
        glTexCoord2f(0.0f, 5.0f);  // Coordonnée de texture pour le coin supérieur gauche
        glVertex3f(-largeurSol / 2, 0.0f, -largeurSol / 2);
        
        glTexCoord2f(5.0f, 5.0f);  // Coordonnée de texture pour le coin supérieur droit
        glVertex3f(largeurSol / 2, 0.0f, -largeurSol / 2);
        
        glTexCoord2f(5.0f, 1.0f);  // Coordonnée de texture pour le coin inférieur droit
        glVertex3f(largeurSol / 2, 0.0f, largeurSol / 2);
        
        glTexCoord2f(0.0f, 1.0f);  // Coordonnée de texture pour le coin inférieur gauche
        glVertex3f(-largeurSol / 2, 0.0f, largeurSol / 2);
        
        glEnd();
        
        // Désactive la texture après le dessin
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void updateRandomRotations(Playmobile *p , int mouvement) {
    usleep(50000);
    float nb_rand = (rand() % 2);
    switch(mouvement){
        case(0): if(p->posX + nb_rand < limite1) p->posX +=nb_rand; break; 
        case(1): if(p->posX - nb_rand > limite2) p->posX -=nb_rand; break;
        case(2): if(p->posZ + nb_rand < limite1) p->posZ +=nb_rand; break;
        case(3): if(p->posZ - nb_rand > limite2) p->posZ -=nb_rand; break;
        case(4): p->bras_gauche +=nb_rand +10; break;
        case(5): p->bras_gauche -=nb_rand -10; break;
        case(6): p->bras_droit +=nb_rand +10; break;
        case(7): p->bras_droit -=nb_rand -10; break;
        case(8): p->main_gauche +=nb_rand +10; break;
        case(9): p->main_gauche -=nb_rand -10; break;
        case(10): p->main_droite +=nb_rand +10; break;
        case(11): p->main_droite -=nb_rand -10; break;
        case(12): if(p->haut_corps + nb_rand +10 <= 90) p->haut_corps +=nb_rand +10; break;
        case(13): if(p->haut_corps - nb_rand -10 >= 0) p->haut_corps -=nb_rand -10; break;
        case(14): p->rtete +=nb_rand +10; break;
        case(15): p->rtete -=nb_rand -10; break;
        case(16): p->lui_meme +=nb_rand +10; break;
        case(17): p->lui_meme -=nb_rand -10; break;
    }
}

void initPlaymobile(Playmobile *p, GLfloat x, GLfloat y, GLfloat z) {
    p->posX = x;
    p->posY = y;
    p->posZ = z;
    p->bras_gauche = 0.0f;
    p->bras_droit = 0.0f;
    p->main_gauche = 0.0f;
    p->main_droite = 0.0f;
    p->haut_corps = 0.0f;
    p->rtete = 0.0f;
    p->lui_meme = 0.0f;
}

void playmobile(Playmobile *p,GLfloat x, GLfloat y, GLfloat z){
    glColor3f(0.0f, 0.1f, 1.0f);
    glPushMatrix();
    {
        glTranslatef(x,y,z);
        glRotatef(p->lui_meme, 0, 1, 0);
        bas();
        glRotatef(p->haut_corps,1,0,0);
        GLfloat * ma_translation1 = translation(0, 1.5, 0);
        glMultMatrixf(ma_translation1);
        haut(p);
    }
    glPopMatrix();
}


void pied(){
    glPushMatrix();
    {
        GLfloat *ma_homothetie = homothetie(1, 0.5, 2);
        glMultMatrixf(ma_homothetie);
        glutSolidCube(0.5);
    }
    glPopMatrix();
}

void poigner(){
    glPushMatrix();
    {
        GLfloat *ma_homothetie = homothetie(1, 0.25, 1);
        glMultMatrixf(ma_homothetie);
        glutSolidCube(0.5);
    }
    glPopMatrix();
}

void bras(){
    glPushMatrix();
    {
        jambe();
        GLfloat * ma_translation1 = translation(0, -2.5, 0);
        glMultMatrixf(ma_translation1);
        une_main();

    }
    glPopMatrix();
}

void une_main(){
    glPushMatrix();
    {
        poigner();
        glPushMatrix();
            {
                GLfloat * ma_translation = translation(-0.2, -0.25, 0);
                glMultMatrixf(ma_translation);
                glPushMatrix();
                {
                GLfloat *ma_homothetie = homothetie(0.25, 0.75, 1);
                glMultMatrixf(ma_homothetie);
                glutSolidCube(0.5);
                }
            }
    glPopMatrix();

        glPushMatrix();
            {
                GLfloat * ma_translation = translation(0.2, -0.25, 0);
                glMultMatrixf(ma_translation);
                glPushMatrix();
                {
                GLfloat *ma_homothetie = homothetie(0.25, 0.75, 1);
                glMultMatrixf(ma_homothetie);
                glutSolidCube(0.5);
                }
            }
    glPopMatrix();
    }    GLfloat * ma_translation = translation(5,0,0);
    glMultMatrixf(ma_translation);
    glPopMatrix();
}


void tete(){
    glPushMatrix();
    {
        glutSolidSphere(1.0, 32, 32);
    }
    glPopMatrix();
}

void cou(){
    glPushMatrix();
    {
        GLfloat *ma_homothetie = homothetie(2.5, 0.75, 2);
        glMultMatrixf(ma_homothetie);
        glutSolidCube(0.5);
    }
    glPopMatrix();
}

void haut(Playmobile *p){
    glPushMatrix();
    {
     ventre();
     glPushMatrix();
        {
            GLfloat * ma_translation1 = translation(0, 1.35, 0);
            glMultMatrixf(ma_translation1);
            cou();
            GLfloat * ma_translation = translation(0, 0.85, 0);
            glMultMatrixf(ma_translation);
            glRotatef(p->rtete, 1, 0, 0);
            tete();
       }
    glPopMatrix();
     glPushMatrix();
        {
            GLfloat * ma_translation = translation(1.25, 1, 0);
            glMultMatrixf(ma_translation);
            glutSolidCube(0.5);
            glRotatef(p->bras_droit, 1, 0, 0);
            epaule();
            GLfloat * ma_translation1 = translation(0.1, 0, 0);
            glMultMatrixf(ma_translation1);
            glPushMatrix();
            {
                glRotatef(p->main_droite, 0, 1, 0);
                bras();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix();
        {
            GLfloat * ma_translation = translation(-1.25, 1, 0);
            glMultMatrixf(ma_translation);
            glRotatef(p->bras_gauche, 1, 0, 0);
            epaule();
            GLfloat * ma_translation1 = translation(-0.1, 0, 0);
            glMultMatrixf(ma_translation1);
            glPushMatrix();
            {
                glRotatef(p->main_gauche, 0, 1, 0);
                bras();
            }
            glPopMatrix();
        }
        glPopMatrix();
        
    }
    glPopMatrix();
}

void epaule(){
        glPushMatrix();
    {
     GLfloat *ma_homothetie = homothetie(1.5, 1, 1);
        glMultMatrixf(ma_homothetie);
        glutSolidCube(0.5);
        
    }
    glPopMatrix();
}

void ventre(){
        glPushMatrix();
    {
     GLfloat *ma_homothetie = homothetie(4, 5, 2);
        glMultMatrixf(ma_homothetie);
        glutSolidCube(0.5);
        
    }
    glPopMatrix();
}

void bas(){
    glPushMatrix();
    {
        bassin();
        glPushMatrix();
        {
            GLfloat * ma_translation = translation(0.75, 0, 0);
            glMultMatrixf(ma_translation);
            glutSolidCube(0.5);
            jambe();
        }
        glPopMatrix();
        glPushMatrix();
        {
            GLfloat * ma_translation = translation(-0.75, 0, 0);
            glMultMatrixf(ma_translation);
            jambe();
        }
        glPopMatrix();
        glPushMatrix();
        {
            GLfloat * ma_translation = translation(-0.75, -2.5, 0.25);
            glMultMatrixf(ma_translation);
            pied();
        }
        glPopMatrix();
        glPushMatrix();
        {
            GLfloat * ma_translation = translation(0.75, -2.5, 0.25);
            glMultMatrixf(ma_translation);
            pied();
        }
        glPopMatrix();
        
    }
    glPopMatrix();
}

void jambe(){
        glPushMatrix();
{
  GLUquadricObj *quadric = gluNewQuadric();
   gluQuadricNormals(quadric, GLU_SMOOTH);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, 0.25, 0.25, 2.5, 32, 32);
}
glPopMatrix();
    
}

void bassin(){
    glPushMatrix();
{
  GLfloat *ma_homothetie = homothetie(4, 1, 2);
        glMultMatrixf(ma_homothetie);
        glutSolidCube(0.5);
}
glPopMatrix();

}

void pouce() {
    glPushMatrix(); {
        // phalange1
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glMultMatrixf (translation(-0.25f, 0.0f, 0.0f));
        glPushMatrix(); {
            glMultMatrixf (homothetie(0.5f, 0.5f, 0.25f));
            glutSolidCube(1.0);
        }
        glPopMatrix();
        // phalange2
        glMultMatrixf (translation(-0.25f, 0.0f, 0.0f));
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glMultMatrixf (translation(-0.25f, 0.0f, 0.0f));
        glPushMatrix(); {
            glMultMatrixf (homothetie(0.5f, 0.5f, 0.25f));
            glutSolidCube(1.0);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void phalange() {
    glMultMatrixf (translation(0.0f, 0.25f, 0.0f));
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glMultMatrixf (translation(0.0f, 0.25f, 0.0f));
    glPushMatrix(); {
        glMultMatrixf (homothetie(0.25f, 0.5f, 0.25f));
        glutSolidCube(1.0);
    }
    glPopMatrix();
}

void doigt() {
    glPushMatrix(); {
        phalange(angle);
        phalange(angle);
        phalange(angle);
    }
    glPopMatrix();
}

void hand() {
    if (angle>75) {
        flagSens = 0;
        printf("changement de flag 0\n");
    }
    if (angle<0)
    {
        flagSens = 1;
        printf("changement de flag 1\n");
    }
    if (flagSens==1)
        angle += 0.5f;
    else
        angle -= 0.5f;
    printf("flag : %f\n", flagSens);
    printf("angle effectif : %f\n", angle);
    glPushMatrix();
    {
        glMultMatrixf (homothetie(2.0f, 2.0f, 0.25f));
        glutSolidCube(1.0);
    }
    glPopMatrix();
    glMultMatrixf (translation(-1.0f, -0.75f, 0.0f));
    pouce(angle);
    glMultMatrixf (translation(0.125f, 1.5f, 0.0f));
    doigt(angle);
    glMultMatrixf (translation(0.5f, 0.0f, 0.0f));
    doigt(angle);
    glMultMatrixf (translation(0.75f, 0.0f, 0.0f));
    doigt(angle);
    glMultMatrixf (translation(0.5f, 0.0f, 0.0f));
    doigt(angle);
}

void triangle(float angle) {
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
}

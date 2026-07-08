#include "VM_init.h"

extern GLfloat xrot;
extern GLfloat yrot;
extern GLfloat zrot;
extern GLfloat dz;

extern GLfloat posX, posY, posZ; 


void VM_init() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);
     glTranslatef(-posX, -posY, -posZ);
    
}

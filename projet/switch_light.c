#include "switch_light.h"  
#include <GL/glut.h>     

GLuint switch_light(GLuint currentLightMode) {
    GLuint newLightMode;

    switch (currentLightMode) {
        case GL_LIGHT0:  
            newLightMode = GL_LIGHT1;
            break;
        case GL_LIGHT1:  
            newLightMode = GL_LIGHT2;
            break;
        case GL_LIGHT2: 
            newLightMode = GL_LIGHT3;
            break;
        default: 
            newLightMode = GL_LIGHT0;
            break;
    }

 
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);    
    glEnable(newLightMode);    

    return newLightMode;
}

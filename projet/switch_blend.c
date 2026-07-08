#include "switch_blend.h" 
#include <GL/glut.h>    

GLuint switch_blend(GLuint currentBlendMode) {
    if (currentBlendMode == GL_TRUE) {
        glDisable(GL_BLEND);  
        return GL_FALSE;    
    } else {
        glEnable(GL_BLEND); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        return GL_TRUE;   
    }
}
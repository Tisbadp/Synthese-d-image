#include <stdio.h>     
#include <stdlib.h>     
#include <math.h>
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>

GLfloat * mxm(GLfloat * m1, GLfloat * m2);

GLfloat * mxv(GLfloat * m, GLfloat * v);

void pretty_printer(GLfloat *m);

GLfloat * identite();

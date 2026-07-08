#include "init.h"

int window;

extern char * tab[];

GLvoid Redimensionne(GLsizei Width, GLsizei Height) {
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, (GLfloat)Width/(GLfloat)Height ,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int notre_init(int argc, char** argv, void (*DrawGLScene)()) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0,0);
    window = glutCreateWindow("OpenGL");  

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); 

    lumiere();
   
    for (int i = 0; i < 2; i++) {
        loadTexture(i, tab[i]);
    }

    glutDisplayFunc(DrawGLScene);
    glutIdleFunc(DrawGLScene);
    glutReshapeFunc(&Redimensionne);
    glutKeyboardFunc(&touche_pressee);
    glutSpecialFunc(&touche_speciale);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    return 1;
}

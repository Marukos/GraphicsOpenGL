#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>

GLvoid initGL()
{
    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(0, 0, a / 2);
    glScalef(a / 2, a / 2, 1);
    glTranslatef(0, 0, -1);
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    initGL();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("square");

    glMatrixMode(GL_PROJECTION);  // setup viewing projection
    glLoadIdentity();  // start with identity matrix
    glOrtho(-20, 20, -20, 20, -150, 150); // setup a 200x200x200 viewing world

    GLuint _displayListId = glGenLists(1); //Make room for the display list
    glNewList(_displayListId, GL_COMPILE); //Begin the display list
    glEndList();

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
//    glutIdleFunc(window_idle);
    glutMainLoop();

    return 0;
}

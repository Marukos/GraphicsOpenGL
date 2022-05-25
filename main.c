#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

static float angle = 0.0f;
static float lx=0.0f, lz=-1.0f;
static float x=0.0f, z=5.0f;

GLuint rectangle;
GLuint square;
GLuint triangle;
GLuint house;
GLuint grass;

GLvoid initGL()
{
    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
    rectangle = glGenLists(2);
    house = rectangle + 1;
    square = glGenLists(2);
    triangle = glGenLists(2);
    glNewList(rectangle, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(-5, -5, -10);
    glVertex3f(5, -5, -10);
    glVertex3f(5, -5, 10);
    glVertex3f(-5, -5, 10);
    glEnd();
    glEndList();

    glNewList(square, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(5, 5, -10);
    glVertex3f(-5, 5, -10);
    glVertex3f(-5, -5, -10);
    glVertex3f(5, -5, -10);
    glEnd();
    glEndList();

    glNewList(triangle, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(5, 5, -10);
    glVertex3f(-5, 5, -10);
    glVertex3f(0, 5+8.66025f, -10);
    glEnd();
    glEndList();

    glNewList(grass, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(-100, -5.5f, 100);
    glVertex3f(-100, -5.5f,-100);
    glVertex3f(100, -5.5f, -100);
    glVertex3f(100, -5.5f, 100);
    glEnd();
    glEndList();


    glNewList(house, GL_COMPILE);

    glColor3f(1, 0, 0);
    glPushMatrix();
    glCallList(rectangle);
    glPopMatrix();


    glColor3f(1, 1, 0);
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glCallList(rectangle);
    glPopMatrix();

    glColor3f(0, 1, 1);
    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    glCallList(rectangle);
    glPopMatrix();

    glColor3f(1, 0, 1);
    glPushMatrix();
    glTranslatef(0, 10, 0);
    glCallList(rectangle);
    glPopMatrix();

    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(-5, 5, 0);
    glRotatef(60, 0, 0, 1);
    glTranslatef(5, 5, 0);
    glCallList(rectangle);
    glPopMatrix();

    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(5, 5, 0);
    glRotatef(-60, 0, 0, 1);
    glTranslatef(-5, 5, 0);
    glCallList(rectangle);
    glPopMatrix();

    glColor3f(0, 0.5f, 0.5f);
    glPushMatrix();
    glCallList(square);
    glPopMatrix();

    glColor3f(0, 0.3f, 0.7f);
    glPushMatrix();
    glTranslatef(0,0,20);
    glCallList(square);
    glPopMatrix();

    glColor3f(1, 0.2f, 0.2f);
    glPushMatrix();
    glCallList(triangle);
    glPopMatrix();

    glColor3f(1, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0,0,20);
    glCallList(triangle);
    glPopMatrix();

    glColor3f(0, 1, 0.2f);
    glPushMatrix();
    glCallList(grass);
    glPopMatrix();

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEndList();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCallList(house);

//    gluLookAt(	0, 0, 0,
//                  0, 0,  0,
//                  0, 0,  0);
    init_scene();
    glRotatef(angle, 1, 1, 0);
    glutSwapBuffers();
}

void window_idle()
{
    angle += 0.0001;
    if (angle > 0.036) {
        angle = 0;
    }
    glutPostRedisplay();
}

void arrowKeys(int key, int xx, int yy) {
    if (key == GLUT_KEY_LEFT)
        angle -= 0.01f;
    else if (key == GLUT_KEY_RIGHT)
        angle += 0.01f;
    lx = sin(angle);
    lz = -cos(angle);
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    initGL();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("rectangle");

    glClearColor(0.0, 0.0, 0.0, 1.0);           // black background


    glMatrixMode(GL_PROJECTION);                // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(-20, 20, -20, 20, -150, 150);     // setup a 200x200x200 viewing world

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutIdleFunc(window_idle);
    glutSpecialFunc(arrowKeys);
    glutMainLoop();

    return 0;
}


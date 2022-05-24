#include <GL/glut.h>
#include <GL/glu.h>

static float a = 4.;
static float b = 100.;
static float scale = 1.0;
static float angle = 0;
static int change = 1;
static int counter = 1;

GLuint rectangle;
GLuint house;

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
    glNewList(rectangle, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(-10, -5, 0);
    glVertex3f(-10, 5, 0);
    glVertex3f(10, 5, 0);
    glVertex3f(10, -5, 0);
    glEnd();
    glEndList();

    glNewList(house, GL_COMPILE);

    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(0,5,0);
    glRotatef(90,1,0,0);
    glCallList(rectangle);
    glPopMatrix();


    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(0,-5,0);
    glRotatef(-90,1,0,0);
    glCallList(rectangle);
    glPopMatrix();


    glColor3f(0, 1, 1);
    glPushMatrix();
    glTranslatef(0,0,-5);
    glCallList(rectangle);
    glPopMatrix();
//
//    glColor3f(0, 0, 1);
//    glPushMatrix();
//    glScalef(a / 2, a / 2, a / 2);
//    glRotatef(-90, 0, 1, 0);
//    glCallList(rectangle);
//    glPopMatrix();
//
//    glColor3f(1, 0, 1);
//    glPushMatrix();
//    glRotatef(-90, 1, 0, 0);
//    glScalef(a / 2, a/2, a / 2);
//    glCallList(rectangle);
//    glPopMatrix();
//
//    glColor3f(0, 1, 0);
//    glPushMatrix();
//    glRotatef(90, 1, 0, 0);
//    glScalef(a / 2, a / 2, a / 2);
//    glCallList(rectangle);
//    glPopMatrix();


    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEndList();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (counter == 1) {
        glTranslatef(0, 0, -b);
        counter = 0;
    }
    glRotatef(angle, 1, 1, 0);


    glCallList(house);

    init_scene();
    glutSwapBuffers();
}

void window_idle()
{
//    angle += 0.0001;
    if (angle > 0.036) {
        angle = 0;
    }


    scale += 0.0005 * change;
    if (a > 8) {
        scale = 3.995;
        change = - 1;
    }
    if (a < 4) {
        scale = 0.0005;
        change = 1;
    }

    a = 4 + scale;

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
    glutMainLoop();

    return 0;
}


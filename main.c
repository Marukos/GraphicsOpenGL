#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

static float angle = 0.0f;
static float lx=0.0f, lz=-1.0f;
static float x=0.0f, z=5.0f;

GLuint rectangle;
GLuint square;
GLuint triangle;
GLuint house;
GLuint grass;
GLuint sun;

GLfloat tetrahedron_vertex[][3] = {
        0.0f,		 0.0f,		 1.0f,
        0.0f,		 0.942809f, -0.333333f,
        -0.816497f, -0.471405f, -0.333333f,
        0.816497f, -0.471405f, -0.333333f
};

GLvoid initGL()
{
    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void normalize(GLfloat* v)
{
    GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0]/= d; v[1]/= d; v[2]/= d;
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int depth)
{
    if (depth> 0) {
        GLfloat ab[3], ac[3], bc[3];
        for (unsigned int i = 0; i <3; i++)
            ab[i] = a[i] + b[i];
        normalize(ab);
        for (unsigned int i = 0; i <3; i++)
            ac[i] = a[i] + c[i];
        normalize(ac);
        for (unsigned int i = 0; i <3; i++)
            bc[i] = b[i] + c[i];
        normalize(bc);
        divide_triangle(a, ab, ac, depth-1);
        divide_triangle(b, bc, ab, depth-1);
        divide_triangle(c, ac, bc, depth-1);
        divide_triangle(ab, bc, ac, depth-1);
    }
    else {
        glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 0);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glEnd();
    }
}

void init_scene()
{

    rectangle = glGenLists(2);
    house = rectangle + 1;
    square = glGenLists(4);
    triangle = glGenLists(5);
    sun = glGenLists(6);
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
    glColor3f(0, 1, 0);
    glVertex3f(-100, 0, 100);
    glVertex3f(-100, 0,-100);
    glVertex3f(100, 0, -100);
    glVertex3f(100, 0, 100);
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

    glEndList();

    glNewList(sun, GL_COMPILE);
    glBegin(GL_LINE_LOOP);
    divide_triangle(tetrahedron_vertex[0], tetrahedron_vertex[2], tetrahedron_vertex[1], 4);
    divide_triangle(tetrahedron_vertex[0], tetrahedron_vertex[3], tetrahedron_vertex[2], 4);
    divide_triangle(tetrahedron_vertex[0], tetrahedron_vertex[1], tetrahedron_vertex[3], 4);
    divide_triangle(tetrahedron_vertex[1], tetrahedron_vertex[2], tetrahedron_vertex[3], 4);
    glEnd();
    glEndList();


    glPushMatrix();
    glTranslatef(-50,0,0);
    glCallList(sun);
    glPopMatrix();

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEndList();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCallList(house);
    glRotatef(angle,0,50,50);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluLookAt(0, 40, 70,
//              0, 0,  0,
//              0, 1,  0);
//    glMatrixMode(GL_MODELVIEW);

    init_scene();
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

    glClearColor(1, 1, 1, 1);           // black background


    glMatrixMode(GL_PROJECTION);                // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(-70, 70, -70, 70, -50, 50);     // setup a 200x200x200 viewing world

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutIdleFunc(window_idle);
    glutSpecialFunc(arrowKeys);
    glutMainLoop();

    return 0;
}


#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

static float angle = 0.0f, sun_angle = 0.0f;
static float lx = 0.0f, lz = -1.0f;
static float x = 0.0f, z = 5.0f;
static int polygons = 1;
static int light = 1;
static int shadows = 1;
static int value = 0;
GLfloat pos[4] = { -50, 0, 0, 0 };
GLfloat direction[3] = { 0, 0, 0 };
float mat[4];
GLfloat mat_emission[] = { 0.3f, 0.2f, 0.0f, 0.0f };

GLuint rectangle;
GLuint square, small_square;
GLuint triangle;
GLuint house;
GLuint grass1;
GLuint grass2;
GLuint sun;
GLuint roof;
GLuint walls;
GLuint light1;

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
    v[0] /= d; v[1] /= d; v[2] /= d;
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int depth)
{

    if (depth > 0) {
        GLfloat ab[3], ac[3], bc[3];
        for (unsigned int i = 0; i < 3; i++)
            ab[i] = a[i] + b[i];
        normalize(ab);
        for (unsigned int i = 0; i < 3; i++)
            ac[i] = a[i] + c[i];
        normalize(ac);
        for (unsigned int i = 0; i < 3; i++)
            bc[i] = b[i] + c[i];
        normalize(bc);
        divide_triangle(a, ab, ac, depth - 1);
        divide_triangle(b, bc, ab, depth - 1);
        divide_triangle(c, ac, bc, depth - 1);
        divide_triangle(ab, bc, ac, depth - 1);
    }
    else {
        glBegin(GL_LINE_LOOP);
        mat[0] = 0.05f;
        mat[1] = 0.05f;
        mat[2] = 0.0f;
        mat[3] = 1.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
        mat[0] = 0.5f;
        mat[1] = 0.5f;
        mat[2] = 0.4f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
        mat[0] = 0.0f;
        mat[1] = 0.0f;
        mat[2] = 0.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.078125f * 128.0f);

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
    small_square = glGenLists(7);
    walls = glGenLists(8);
    roof = glGenLists(9);
    grass1 = glGenLists(10);
    grass2 = glGenLists(12);
    light1 = glGenLists(11);

    glNewList(light1, GL_COMPILE);
    GLfloat spotlight_ambient[4] = { 1,1,1,1.0f };
    //GLfloat diff[] = { 1, 0, 0, 1 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, spotlight_ambient);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, diff);
    GLfloat spotlight_pos[4] = { -5.0f, 10.0f, 10.0f, 1.0f };
    GLfloat spotlight_direction[4] = { -5.0f, -10.0f,  6.0f ,0.0f};
    

    // -5 10 10  1
    // -10 0  14   1
    glLightfv(GL_LIGHT1, GL_POSITION, spotlight_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlight_direction);
    
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
    glEndList();

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

    glNewList(small_square, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, 0, -1);
    glVertex3f(1, 0, -1);
    glVertex3f(1, 0, 1);
    glEnd();
    glEndList();

    glNewList(triangle, GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(5, 5, -10);
    glVertex3f(-5, 5, -10);
    glVertex3f(0, 5 + 8.66025f, -10);
    glEnd();
    glEndList();


    glNewList(grass1, GL_COMPILE);
    glBegin(GL_POLYGON);
    mat[0] = 0.0f;
    mat[1] = 0.05f;
    mat[2] = 0.0f;
    mat[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 0.4f;
    mat[1] = 0.5f;
    mat[2] = 0.4f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.04f;
    mat[1] = 0.7f;
    mat[2] = 0.04f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.078125f * 128.0f);
    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

    glVertex3f(-50, 0, 50);
    glVertex3f(-50, 0, -50);
    glVertex3f(50, 0, -50);
    glVertex3f(50, 0, 50);    
    glEnd();
    glEndList();

    glNewList(grass2, GL_COMPILE);
    mat[0] = 0.0f;
    mat[1] = 0.05f;
    mat[2] = 0.0f;
    mat[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 0.4f;
    mat[1] = 0.5f;
    mat[2] = 0.4f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.04f;
    mat[1] = 0.7f;
    mat[2] = 0.04f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.078125f * 128.0f);
    //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

    for (int i = -50; i <= 50; i++) 
        for (int j = -50; j < 50; j++) {
            glBegin(GL_POLYGON);
            glVertex3f(i, 0, j);
            glVertex3f(i, 0, j + 1);
            glVertex3f(i + 1, 0, j + 1);
            glVertex3f(i + 1, 0, j);
            glEnd();
        }
    glEndList();

    glNewList(walls, GL_COMPILE);

    mat[0] = 0.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 0.5f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.7f;
    mat[1] = 0.6f;
    mat[2] = 0.6f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.25f * 128.0f);

    glPushMatrix();
    glCallList(rectangle);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glCallList(rectangle);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    glCallList(rectangle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 10, 0);
    glCallList(rectangle);
    glPopMatrix();

    glPushMatrix();
    glCallList(square);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 20);
    glCallList(square);
    glPopMatrix();

    glPushMatrix();
    glCallList(triangle);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 20);
    glCallList(triangle);
    glPopMatrix();
    glEnd();
    glEndList();



    glNewList(roof, GL_COMPILE);
    
    mat[0] = 0.25f;
    mat[1] = 0.20725f;
    mat[2] = 0.20725f;
    mat[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    mat[0] = 1.0f;
    mat[1] = 0.829f;
    mat[2] = 0.829f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    mat[0] = 0.296648f;
    mat[1] = 0.296648f;
    mat[2] = 0.296648f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.088f * 128.0f);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);


    glPushMatrix();
    glTranslatef(-5, 5, 0);
    glRotatef(60, 0, 0, 1);
    glTranslatef(5, 5, 0);
    glCallList(rectangle);
    glPopMatrix();

    //glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 100);
    glPushMatrix();
    glTranslatef(5, 5, 0);
    glRotatef(-60, 0, 0, 1);
    glTranslatef(-5, 5, 0);
    glCallList(rectangle);
    glPopMatrix();
    glEnd();
    glEndList();


    glNewList(sun, GL_COMPILE);
    glBegin(GL_LINE_LOOP);
    mat[0] = 0.05f;
    mat[1] = 0.05f;
    mat[2] = 0.0f;
    mat[3] = 1.0f;
    //glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glGetLightfv(GL_FRONT_AND_BACK, GL_AMBIENT,mat);
    mat[0] = 0.5f;
    mat[1] = 0.5f;
    mat[2] = 0.4f;
    glGetLightfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    glGetLightfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    //glMaterialf(GL_FRONT, GL_SHININESS, 0.078125f * 128.0f);
    //glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glGetLightfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

    divide_triangle(tetrahedron_vertex[0], tetrahedron_vertex[2], tetrahedron_vertex[1], 4);
    divide_triangle(tetrahedron_vertex[0], tetrahedron_vertex[3], tetrahedron_vertex[2], 4);
    divide_triangle(tetrahedron_vertex[0], tetrahedron_vertex[1], tetrahedron_vertex[3], 4);
    divide_triangle(tetrahedron_vertex[1], tetrahedron_vertex[2], tetrahedron_vertex[3], 4);

    glEnd();
    glEndList();   


    glNewList(house, GL_COMPILE);
    glCallList(walls);
    glCallList(roof);
    glEnd();
    glEndList();
}

void display(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    if (light == 1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    if (shadows == 1)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glCallList(house);

    if(polygons == 1)
        glCallList(grass1);
    else
        glCallList(grass2); 

    glPushMatrix();
    glRotatef(sun_angle, 0, 0, 1);
    
    glTranslatef(-50, 0, 0);
    glCallList(sun);
    //GLfloat spotlight_ambient[] = { 0.19125,	0.0735,	0.0225, 1 };
    GLfloat spotlight_ambient[] = { 1,	1,	1, 1 };
    //GLfloat diff[] = { 1, 0, 0, 1 };
    //GLfloat diff[] = { 0.7038,	0.27048,	0.0828, 1 };
    //GLfloat spec[] = { 0.628281,	0.555802,	0.366065, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, spotlight_ambient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, diff);
    //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1000);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 360);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glPopMatrix();

    glCallList(light1);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, 0.6f, z,
        x + lx, 0, z + lz,
        0.0f, 1.0f, 0.0f);
    glutSwapBuffers();
}

void window_idle()
{
    if (polygons == 1)
        sun_angle -= 0.02f;
    else
        sun_angle -= 0.1f;

    if (sun_angle < -180) {
        sun_angle = 0;
    }

    direction[0] = -sin(sun_angle) * 50;
    direction[1] = cos(sun_angle) * 50;
    glutPostRedisplay();
}

void arrowKeys(int key, int xx, int yy) {
    if (key == GLUT_KEY_LEFT) {
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
    }
    else if (key == GLUT_KEY_RIGHT) {
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
    }

    glutPostRedisplay();
}

void rightClickMenu(GLint menuNum)
{}

void grassRightClickSubMenu(GLint menuNum)
{
    polygons = menuNum;
}

void lightRightClickSubMenu(GLint menuNum)
{
    light = menuNum;
}

void shadowsRightClickSubMenu(GLint menuNum)
{
    shadows = menuNum;
}



void createGLUTMenus()
{
    //Grass sub menu
    auto grassSubMenuID = glutCreateMenu(grassRightClickSubMenu);
    glutAddMenuEntry("One polygon grass", 1);
    glutAddMenuEntry("100 polygons grass", 0);

    //Light sub menu
    auto lightSubMenuID = glutCreateMenu(lightRightClickSubMenu);
    glutAddMenuEntry("On", 1);
    glutAddMenuEntry("Off", 0);

    //Shadows sub menu
    auto shadowsSubMenuID = glutCreateMenu(shadowsRightClickSubMenu);
    glutAddMenuEntry("Smooth", 1);
    glutAddMenuEntry("Vertical", 0);

    //Parent menu
    glutCreateMenu(rightClickMenu);
    glutAddSubMenu("Grass", grassSubMenuID);
    glutAddSubMenu("Light", lightSubMenuID);
    glutAddSubMenu("Shadows", shadowsSubMenuID);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    initGL();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_NORMALIZE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("House");

    glClearColor(1, 1, 1, 1);           // black background

    
    glMatrixMode(GL_PROJECTION);                // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(-50, 50, -50, 50, -50, 50);     // setup a 200x200x200 viewing world

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init_scene();
    glutDisplayFunc(display);
    glutIdleFunc(window_idle);
    glutSpecialFunc(arrowKeys);
    createGLUTMenus();
    glutMainLoop();

    return 0;
}

#include <iostream>
#include <cmath>
#include <GLUT/glut.h>
#include <CGAL/Cartesian.h>

using namespace std;
using Point_3 = typename CGAL::Cartesian<float>::Point_3;
const static double PI = M_PI;

static double selfRotate_1 = 0;
static double selfRotate_2 = 0;
double x_ = 50, y_ = 0, z_ = 0;
double v_x = 0, v_y = 0.5, v_z = 0;
// double v_x = 2, v_y = 5, v_z = 2;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    // Draw the first red 'star'
    glPushMatrix();   // save the original matrix
    glTranslated(10, 0, 0);   // move the star 50 from origin to the x axis 
    glRotatef(selfRotate_1, 0, 1, 0);   // rotate around the axis y (after translate)
    glColor3f(1, 0, 0);       // Set color to red
    glutWireSphere(15, 50, 50); // glutWireSphere(radius，lines-，lines|)
    glPopMatrix();   // pop the original matrix 

    // Draw the second red 'star'
    glPushMatrix(); 
    glTranslated(-30, 0, 0);
    glRotatef(selfRotate_1, 0, 1, 0);
    glColor3f(1, 0, 0);
    glutWireSphere(15, 50, 50); 
    glPopMatrix();

    // Draw the planet.
    // Rotate first and then translate, the planet will rotate around axis y in original matrix.
    // The second rotate will enable the planet ro rotate around axis y after translation.   
    glPushMatrix(); 
    glTranslated(x_, y_, z_);
    glRotated(selfRotate_2, 0, 1, 0);
    glColor3f(0, 0, 1);
    glutWireSphere(8, 10, 10);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();

    // std::cout << "selfRotate_1 = " << selfRotate_1 << '\n';
    // std::cout << "selfRotate_2 = " << selfRotate_2 << '\n';
    // std::cout << "x = " << x << '\n';
    // std::cout << "y = " << y << '\n';
    // std::cout << "z = " << z << '\n';
}
 
void reshape(int w,int h)
{
    glViewport(0, 0, w, h); 
    // Specify which matrix is ​​the current matrix 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    // Create a perspective projection matrix(fovy,aspect,zNear,zFar);
    gluPerspective(90, w/h, 1, 1000); 
    // void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, 
    // GLdouble centery, GLdouble centerz,GLdouble upx, GLdouble upy, GLdouble upz);
    gluLookAt(0, 40, 150, 0, 0, 0, 0, 1, 0); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void setupRC()
{
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}
 
void Special( int key,int x,int y)
{
    double time = 2;
    // double G = 50, m1 = 50, m2 = 100, mPlane = 5;
    double G = 5, m1 = 100, m2 = 100, mPlane = 10;

    // The Plane_Position, Force, v and x are all vectors.
    Point_3 S1_Position(2,0,0);
    Point_3 S2_Position(-2,0,0);
    Point_3 cur_position;

    // The force from first red 'star'
    Point_3 Plane_Position1(S1_Position.x() - x_, S1_Position.y() - y_, S1_Position.z() - z_);
    float r1 = std::sqrt(Plane_Position1.x()*Plane_Position1.x() + Plane_Position1.y()*Plane_Position1.y() + Plane_Position1.z()*Plane_Position1.z());
    Point_3 unit1(Plane_Position1.x()/r1, Plane_Position1.y()/r1, Plane_Position1.z()/r1);
    float temp_F1 = (G * m1 * mPlane) / (r1 * r1);
    Point_3 Force1(temp_F1 * unit1.x(), temp_F1 * unit1. y(), temp_F1 * unit1.z());

    // The force from first red 'star'
    Point_3 Plane_Position2(S2_Position.x() - x_, S2_Position.y() - y_, S2_Position.z() - z_);
    float r2 = std::sqrt(Plane_Position2.x()*Plane_Position2.x() + Plane_Position2.y()*Plane_Position2.y() + Plane_Position2.z()*Plane_Position2.z());
    Point_3 unit2(Plane_Position2.x()/r2, Plane_Position1.y()/r2, Plane_Position1.z()/r2);
    float temp_F2 = (G * m2 * mPlane) / (r2 * r2);
    Point_3 Force2(temp_F2 * unit2.x(), temp_F2 * unit2. y(), temp_F2 * unit2.z());

    Point_3 Force(Force1.x() + Force2.x(), Force1.y() + Force2.y(), Force1.z() + Force2.z());

    // v = v0 + at = v0 + t*F/m
    v_x = v_x + time * Force.x() / mPlane;  
    v_y = v_y + time * Force.y() / mPlane;
    v_z = v_z + time * Force.z() / mPlane;

    // x = x0 + vt
    x_ += time * v_x;
    y_ += time * v_y;
    z_ += time * v_z;

    selfRotate_1 = (selfRotate_1 + 5 * time);
    selfRotate_2 = (selfRotate_2 + 20 * time);

    if (selfRotate_1 > 360) {
        selfRotate_1 = 0;
    }
    if (selfRotate_2 > 360) {
        selfRotate_2 = 0;
    }
}
 
void myTimeFunc(int x)
{
    Special(GLUT_KEY_UP, 0, 0);
    glutPostRedisplay();
    glutTimerFunc(100, myTimeFunc, 1);
}
int main(int argc,char *argv[])
{
    // cout<<PI;
    // Initialize GLUT library 
    glutInit(&argc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    // Init the size of window to (800,800) for glutCreateWindow.
    glutInitWindowSize(800, 800);
    // Create window Assignment1
    glutCreateWindow("Assignment1");

    setupRC();
    // Register callback functions for handling various types of events
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // glutSpecialFunc(Special);
    glutTimerFunc(500, myTimeFunc, 1);
    // glutKeyboardFunc(Special);
    // Enter main event-processing loop
    glutMainLoop();
    
}
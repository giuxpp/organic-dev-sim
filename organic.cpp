/***** INCLUDES Section *****/
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib> //for random()
#include <cmath>
#include "tree.h"

using namespace std;

#define window_width              1200
#define window_height             1600

#define COLOR_WHITE       {1.0f, 1.0f, 1.0f} 

const float pi = 3.14159265;

#define RAD2GRADE(xrad)    (360*xrad/(2*pi))

typedef struct {
    float red;
    float green;
    float blue;
}gxp_color;

// Return a random float in the range 0.0 to 1.0.                            */
GLfloat randomFloat() {
  return (GLfloat)rand() / (RAND_MAX/2);
}

void drawLine(float x0, float y0, float x1, float y1, gxp_color _color, uint8_t _line_width) {   
    //glLineWidth(_line_width); 
    glBegin(GL_LINES);
      glColor3f(_color.red, _color.green, _color.blue);
      glVertex2d(x0, y0);
      glVertex2d(x1, y1);
    glEnd();
}


void drawTree(GLfloat _x, GLfloat _y, GLfloat _branch_len, GLfloat _len_fac, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n){
    
    GLfloat branch_len = _branch_len;
    GLfloat x0=_x, x1r, x1l, y0=_y, y1r, y1l;    
    GLfloat angle = _angle_factor*_newAngle;
    GLfloat new_angle_right  = angle - _angle0*_angle_factor;
    GLfloat new_angle_left   = angle + _angle0*_angle_factor;
    GLfloat new_angle = _angle_factor * angle;
    GLfloat lenFactor = _len_fac;   
    uint8_t n = _n;
    uint8_t level = 0;

    static uint8_t tickness = (level++)<4?2*(4-level):1;
    
    if (n--)
{
        /* Right Branch */
        x1r=x0-sin(angle)*branch_len;
        y1r=y0+cos(angle)*branch_len;   
        drawLine(x0,y0,x1r,y1r,COLOR_WHITE, tickness);  

        /*  Left Branch */
        x1l=x0-sin(angle)*branch_len;
        y1l=y0+cos(angle)*branch_len;                 
        drawLine(x0,y0,x1l,y1l,COLOR_WHITE, tickness);        

        /* Recursive calling of this function */
        drawTree(x1l, y1l, lenFactor*branch_len, lenFactor, _angle0, _angle_factor, new_angle_left, n);
        drawTree(x1r, y1r, lenFactor*branch_len, lenFactor, _angle0, _angle_factor, new_angle_right, n);
    }
}

figureClass tree(0.5, 0.75, 1.0*pi/12, 1.50, 0.0, 6);
void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT);
 
    /*        x0  ,     y0,         lenght,         len_factor,     angle init,     angle_factor,         new_angle        iterations*/
    drawTree(0.0f,    -0.8f,    tree.branch_len,   tree.len_fac,    tree.angle,   tree.angle_factor,   tree.angle_trunk,  tree.nlevels);
 
    glutSwapBuffers();    
}

// On reshape, uses an orthographic projection with world coordinates ranging
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);  //original: GL_PROJECTION
    glLoadIdentity();
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); 
    renderScene(); 
    glFlush(); 
}

int main(int argc, char** argv){
   // test();
    
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);    
    glutCreateWindow("Organice Developement Simulation");
    //glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
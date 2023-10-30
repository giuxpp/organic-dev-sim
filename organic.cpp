/***** INCLUDES Section *****/
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib> //for random()
#include <cmath>

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

void drawLine(float x0, float y0, float x1, float y1, gxp_color _color) {
    //glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(_color.red, _color.green, _color.blue); 
    glLineWidth(1);  

    glBegin(GL_LINES);
      glVertex2d(x0, y0);
      glVertex2d(x1, y1);
    glEnd();
}


void drawTree(GLfloat _x, GLfloat _y, GLfloat _branch_len, GLfloat _len_fac, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, int _n){
    
    GLfloat branch_len = _branch_len;
    GLfloat x0=_x, x1, y0=_y, y1;    
    GLfloat angle = _newAngle;
    GLfloat new_angle_right  = angle - 2*_angle0;// - angle/2;
    GLfloat new_angle_left   = angle + _angle0;// - angle/2;
    GLfloat new_angle = _angle_factor * angle;
    GLfloat lenFactor = _len_fac;   
    int n=_n;
    
    if (n--)
{
        /**  Left Branch */
        x1=x0-sin(angle)*branch_len;
        y1=y0+cos(angle)*branch_len;   
       
        drawLine(x0,y0,x1,y1,COLOR_WHITE);        
        drawTree(x1, y1, lenFactor*branch_len, lenFactor, _angle0, _angle_factor, new_angle_left, n);

        /* Right Branch */
        x1=x0-sin(angle)*branch_len;
        y1=y0+cos(angle)*branch_len;   
       
        drawLine(x0,y0,x1,y1,COLOR_WHITE);        
        drawTree(x1, y1, lenFactor*branch_len, lenFactor, _angle0, _angle_factor, new_angle_right, n);
    }
}


void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1.5);  
    // glBegin (GL_LINES);
    //   glVertex2f(0.0, -0.34);
    //   glVertex2f(0.0,0.0);
    // glEnd();

    /*       x0,     y0,     lenght,   len_factor,   angle init,    angle_factor,  new_angle    iterations*/
    drawTree(0.0,    0.0,     0.24,      0.7,        (1*pi/12),       1.0,        (1*pi/12),       8);
 
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
    cout<<endl<<"!Hi there"<<endl;
    
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);    
    glutCreateWindow("Organice Developement Simulation");
    //glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
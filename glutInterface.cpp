#include "glutInterface.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>  // for glutMainLoopEvent()
#include <cmath>
#include "bioform.h"


/**********************************
 ****    LOCAL DECLARATIONS  ******
 **********************************/ 
using namespace std;

#define window_width              1500
#define window_height             1500
#define disp_x_range_min          (-1.0)
#define disp_x_range_max          ( 1.0)
#define disp_y_range_min          (-1.0)
#define disp_y_range_max          ( 1.0)

/** Color in RGB. From 0.0 to 1.0 */
typedef struct {
    float red;
    float green;
    float blue;
}gxp_color;

#define COLOR_WHITE       {1.0f, 1.0f, 1.0f}


/*************************************
 ****  LOCAL FUNCTION PROTOTYPES  ****
 *************************************/ 
void drawBioForms(GLfloat _x, GLfloat _y, GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n);


/************   BIOFORM   OBJECTS     ************************/
/**           trunkLen  firstB  bLenFact     angle      angFact   angleTrunk   levels) */
bioformClass tree(0.0,    0.005,     2,    1.85*pi/12,    1.2,      0,            5);


/*******************   drawLine ()    ************************
 *   draws a line from p0 to p1
 *   Used locally by drqwBioForm function *
 *************************************************************/
static void drawLine(float x0, float y0, float x1, float y1, gxp_color _color, uint8_t _line_width) {   
    glLineWidth(_line_width); 
    glBegin(GL_LINES);
      glColor3f(_color.red, _color.green, _color.blue);
      glVertex2d(x0, y0);
      glVertex2d(x1, y1);
    glEnd();
}


/******************   drawBioForms ()    **********************
 *   Draws a bio form based on the "genes" input parameters
 *   This function is shared with upper app layers.
 *************************************************************/
void drawBioForms(GLfloat _x, GLfloat _y, GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n){
    
    static bool firstBranch = true;
    GLfloat firstBranchLen = _firstBranchLen;
    GLfloat x0=_x, y0=_y, x1r, x1l, y1r, y1l;    
    GLfloat angleBranches = _angle_factor*_newAngle;    
    uint8_t lineGrossor = 2;        
    
    /* Setting lines Grossor and Trunk Lenght */
    if (firstBranch){
        firstBranch = false;
        firstBranchLen = _trunkLen;
        lineGrossor = 3;
    } else if (_n==1){
        lineGrossor = 1;
    } else {/*no action, keep initial value*/}

    /* Draw branches if deep levels allows it */
    if (_n)
    {
        /* Right Branch */
        GLfloat new_angle_right  = angleBranches - _angle0*_angle_factor;
        x1r=x0-sin(angleBranches)*firstBranchLen;
        y1r=y0+cos(angleBranches)*firstBranchLen;   
        drawLine(x0,y0,x1r,y1r,COLOR_WHITE, lineGrossor);  

        /*  Left Branch */
        GLfloat new_angle_left   = angleBranches + _angle0*_angle_factor;
        x1l=x0-sin(angleBranches)*firstBranchLen;
        y1l=y0+cos(angleBranches)*firstBranchLen;                 
        drawLine(x0,y0,x1l,y1l,COLOR_WHITE, lineGrossor);        

        /* Recursive calling of this function */
        drawBioForms(x1l, y1l, _trunkLen, _branchLenFact*_firstBranchLen, _branchLenFact, _angle0, _angle_factor, new_angle_left, _n-1);
        drawBioForms(x1r, y1r, _trunkLen, _branchLenFact*_firstBranchLen, _branchLenFact, _angle0, _angle_factor, new_angle_right, _n-1);
    }
}


/******    EnterGlutLoop()   ***************
 *   Enter main Glut library loop.
 *   When OpenGLUT has dispatched all pending events, it will 
 *   exitthe event processing, returning to your code.
 ********************************************/
void EnterGlutLoop(void){
    glutMainLoopEvent();
}


/*******     display()   ***************
 *   This callback is exectued from GL
 *   Execute the display routine 
 ***************************************/
void display() {
    glClear(GL_COLOR_BUFFER_BIT); 
        drawBioForms(0.0f,    -(tree.trunkLen),  tree.trunkLen,  tree.firstBranchLen,   tree.branchLenFact,    tree.angleBranches,   tree.angleFactor,   tree.angleTrunk,  tree.levels); 
        glutSwapBuffers();    
    glFlush(); 
}


/****    initGlutRoutine()   ****************
 *   Configuration and initialization of GL library
 *   The nex parameters are configured:
 *      Window size, position, scale, title, 
 ********************************************/
void initGlutRoutine(int argc, char** argv){
    glutInit(&argc, argv);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(disp_x_range_min, disp_x_range_max, disp_y_range_min, disp_y_range_max);
    glutInitWindowSize(window_width, window_height);    
    glutCreateWindow("Organic Developement Simulation");
    //glutReshapeFunc(reshape);
    glutDisplayFunc(display);
}




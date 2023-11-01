#include "bioform.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>  // for glutMainLoopEvent()
#include <cstdlib> //for random()
#include <cmath>



const float pi = 3.14159265;

/** Color in RGB. From 0.0 to 1.0 */
typedef struct {
    float red;
    float green;
    float blue;
}gxp_color;

#define COLOR_WHITE       {1.0f, 1.0f, 1.0f} 


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


/******************   drawBioForm ()    **********************
 *   Draws a bio form based on the "genes" input parameters
 *   This function is shared with upper app layers.
 *************************************************************/
void drawBioForm(GLfloat _x, GLfloat _y, GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n){
    
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
        drawBioForm(x1l, y1l, _trunkLen, _branchLenFact*_firstBranchLen, _branchLenFact, _angle0, _angle_factor, new_angle_left, _n-1);
        drawBioForm(x1r, y1r, _trunkLen, _branchLenFact*_firstBranchLen, _branchLenFact, _angle0, _angle_factor, new_angle_right, _n-1);
    }
}

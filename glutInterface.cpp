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

#define Pi (3.14158)




/*************************************
 ******   LOCAL DECLARATIONS   *******
 *************************************/ 
void drawBioFormWrapper(bioformClass bioform, point pnt);
void drawBioForms(GLfloat _x, GLfloat _y, GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n);

typedef struct node{
    bioformClass * bioformPointer;
    node * prev;
}nodeType;

nodeType * treePointer;

/************   BIOFORM   OBJECTS     ************************/
/**                    trunkLen     firstB     bLenFact      angleTrunk    angleBranches   angFact     levels) */
bioformClass formObject(  0.01f,       0.01f,      1.0f,          0.0f,      3*Pi/12,        1.0f,           3   );

void startNodes (void){
   treePointer = new node();
   treePointer->bioformPointer = &formObject;
   treePointer->prev = nullptr; 
}

void AddNode (void)
{ 
    node *newNode = new node();
    bioformClass * newBioform = new bioformClass();
    bioFormClone(treePointer->bioformPointer, newBioform);
    bioformMutation(newBioform);
    newNode->bioformPointer = newBioform;
    newNode->prev = treePointer;
    treePointer = newNode;
}

void FreeNode (void) {
    node * temp = treePointer;
    if (treePointer->prev != nullptr){
        treePointer = treePointer->prev;
        free(temp);
    }
}

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

/***************   drawBioFormWrapper    ********************
 *   Wrapper fro drawBioForms function
 *   Ths functions receives a bioform object and starts
 *   to draw its generated figure.
 ******************************0.05f ******************************/
void drawBioFormWrapper(bioformClass * bioform, point pnt){
    drawBioForms(pnt.x, pnt.y, 
                bioform->trunkLen, bioform->branchLen, bioform->branchLenFact,    
                bioform->angleBranches, bioform->angleFactor, bioform->angleTrunk,  
                bioform->levels); 
}


/******************   drawBioForms ()    **********************
 *   Draws a bio form based on the "genes" input parameters
 *   This function is shared with upper app layers.
 *************************************************************/
void drawBioForms(GLfloat _x, GLfloat _y, GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n){
    
    static bool firstBranch = true;
    GLfloat branchLen = _firstBranchLen;
    GLfloat x0=_x, y0=_y, x1r, x1l, y1r, y1l;    
    GLfloat angleBranches = _angle_factor*_newAngle;    
    uint8_t lineGrossor = 2;        
    
    /* Setting lines Grossor and Trunk Lenght */
    if (firstBranch){
        firstBranch = false;
        branchLen = _trunkLen;
        lineGrossor = 3;
    } else if (_n==1){
        lineGrossor = 1;
    } else {/*no action, keep initial value*/}

    /* Draw branches if deep levels allows it */
    if (_n)
    {
        /* Right Branch */
        GLfloat new_angle_right  = angleBranches - _angle0*_angle_factor;
        x1r=x0-sin(angleBranches)*branchLen;
        y1r=y0+cos(angleBranches)*branchLen;   
        drawLine(x0,y0,x1r,y1r,COLOR_WHITE, lineGrossor);  

        /*  Left Branch */
        GLfloat new_angle_left   = angleBranches + _angle0*_angle_factor;
        x1l=x0-sin(angleBranches)*branchLen;
        y1l=y0+cos(angleBranches)*branchLen;                 
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
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);         
        drawBioFormWrapper(treePointer->bioformPointer, {0.0f, figure_yaxis_offset});
        glutSwapBuffers();    
    glFlush(); 
}

// Handles the reshape event by setting the viewport so that it takes up the
// whole visible region, then sets the projection matrix to something reason-
// able that maintains proper aspect ratio.
void reshape(GLint w, GLint h) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(disp_x_range_min, disp_x_range_max, disp_y_range_min, disp_y_range_max);
}

// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int) {
    int timeout = 3000000;
    //cout<<"Got key.."<<key<<endl;
    while (timeout--){} //debouncing
    switch(key){
        case (GLUT_KEY_RIGHT):    
                AddNode();
                display();
                glutPostRedisplay();
                break;

        case (GLUT_KEY_LEFT):    
                FreeNode();
                display();
                glutPostRedisplay();
                break;

        default:
                break;
    }
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
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
}




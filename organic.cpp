/***** INCLUDES Section *****/
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>  // for glutMainLoopEvent()
#include <cstdlib> //for random()
#include <cmath>
#include "bioform.h"

using namespace std;

#define window_width              1200
#define window_height             1600

void initGlutRoutine(int argc, char** argv);


// Return a random float in the range 0.0 to 1.0.                            */
GLfloat randomFloat() {
  return (GLfloat)rand() / (RAND_MAX/2);
}

bioformClass tree(0.5, 0.78, 1.0*pi/12, 1.50, 0.0, 6);
void display() {
    glClear(GL_COLOR_BUFFER_BIT); 
        drawBioForm(0.0f,    -0.8f,    tree.branch_len,   tree.len_fac,    tree.angle,   tree.angle_factor,   tree.angle_trunk,  tree.nlevels); 
        glutSwapBuffers();    
    glFlush(); 
}


int main(int argc, char** argv){
       
    initGlutRoutine(argc, argv);
    
    //glutReshapeFunc(reshape);
    glutDisplayFunc(display);
        
    while (1){
        /**     glutMainLoop()  
         *  Enters the GLUT event processing loop. This routine should be called at most 
         *  once in a GLUT program.  Once called, this routine will never return. 
         *  It will call as necessary any callbacks that have been registered   */
        glutMainLoopEvent();
        
        //cout<<"Imprimiendo desde el main after events"<<endl;
    }    
    
    return 0;
}

void initGlutRoutine(int argc, char** argv){
    glutInit(&argc, argv);
    glMatrixMode(GL_MODELVIEW);  //original: GL_PROJECTION
    glLoadIdentity();
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glutInitWindowSize(window_width, window_height);    
    glutCreateWindow("Organic Developement Simulation");
}

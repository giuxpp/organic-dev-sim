/***** INCLUDES Section *****/
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib> //for random()

using namespace std;


#define window_width              600
#define window_height             800
#define SIZE_OF_LINES             500

// Return a random float in the range 0.0 to 1.0.
/* Usage:
    randomFloat();                               */
GLfloat randomFloat() {
  return (GLfloat)rand() / (RAND_MAX/2);
}



class orgBranch {
    public:        
        float start_pos[3];
        float end_pos[3];
        static float last_vertix[3];

        orgBranch(){
            start_pos[0]=last_vertix[0];
            start_pos[1]=last_vertix[1];
            start_pos[2]=last_vertix[2];

            end_pos[0]=randomFloat()-1;
            end_pos[1]=randomFloat()-1;

            last_vertix[0]=end_pos[0];
            last_vertix[1]=end_pos[1];

            cout<<"Start Pos = "<<start_pos[0]<<" - "<<start_pos[1]<<endl;
            cout<<"End Pos Pos = "<<end_pos[0]<<" - "<<end_pos[1]<<endl<<endl;
        }

};

float orgBranch::last_vertix[3]={0,0,0};
orgBranch OrganicTree[SIZE_OF_LINES];


void startTree(){

}


void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT);

    /* Esta function hace lineas infinitas en tercera dimension. */
    glBegin (GL_LINES);
        
        for (int i=0; i<SIZE_OF_LINES; i++){
            glVertex3f(OrganicTree[i].start_pos[0], OrganicTree[i].start_pos[1], 0.0f);  //Origin Coordenates
            glVertex3f(OrganicTree[i].end_pos[0], OrganicTree[i].end_pos[1], 0.0f); //Dest Coordenates    
        }

        //glVertex3f(0.0f, 0.0f, 0.0f);
        //glVertex3f(1.0f, 1.0f, 0.0f);


    glEnd();

    glutSwapBuffers();    
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
    glutDisplayFunc(display);

    glutMainLoop();


    return 0;
}
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
#define SIZE_OF_LINES             500
const float pi = 3.14159265;

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

            //cout<<"Start Pos = "<<start_pos[0]<<" - "<<start_pos[1]<<endl;
            //cout<<"End Pos Pos = "<<end_pos[0]<<" - "<<end_pos[1]<<endl<<endl;
        }

};

float orgBranch::last_vertix[3]={0,0,0};
orgBranch OrganicTree[SIZE_OF_LINES];


void startTree(){

}


void _generateTreeBranches(int newPosition,//const Point3f& newPosition,
                       float length,
                       float rotation,
                       const int depth)
{
#if 0
  if(depth > MAX_DEPTH) return;
  cout << "at depth = " << depth << endl;


  if(depth == 0){
      glColor3f(1.0f,1.0f,1.0f);
  }else if(depth == 1){
      glColor3f(1.0f,0.0f,0.0f);
  }else{
      glColor3f(0.0f,1.0f,0.0f);
  }

  glTranslatef(newPosition.x,newPosition.y,newPosition.z);
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);
  //drawLine(length);
  glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
  glTranslatef(-newPosition.x,-newPosition.y,-newPosition.z);

  const float newLength = length * BRANCH_LENGTH_DECREASE_FACTOR;
  int nextDepth = depth + 1;
  Point3f nextPosition = {newPosition.x+length, newPosition.y, newPosition.z};

  float leftRotation = rotation + CHILD_BRANCH_ANGLE * nextDepth;
  _generateTreeBranches(nextPosition,newLength,leftRotation,nextDepth);

  float rightRotation = rotation - CHILD_BRANCH_ANGLE * nextDepth;
  _generateTreeBranches(nextPosition,newLength,rightRotation,nextDepth);
#endif
}


void generateTree(){
#if 0    
  Point3f startPoint({0.0f,0.0f,0.0f});
  Point3f endPoint({1.0f,0.0f,0.0f});
  float rotation = 90.0f;
  glutWireSphere(0.05, 4, 4);
  _generateTreeBranches(startPoint,1.0f,rotation,0);
#endif
}

void drawTree(GLfloat _x, GLfloat _y, GLfloat _branch_len, GLfloat _len_fac, GLfloat _angle, GLfloat _angle_factor, int _n){
    
    GLfloat branch_len = _branch_len;
    GLfloat x0=_x, x1, y0=_y, y1;    
    GLfloat angle = _angle;
    GLfloat new_angle = angle*_angle_factor;
    GLfloat lenFactor = _len_fac;   
    int n=_n;
    
    if (--n)
    {
        x1=x0+sin(angle)*branch_len;
        y1=y0+cos(angle)*branch_len;
        
        // glRotatef(angle,0.0,0.0,1.0) ; // rotate by angle degrees about the y axis

        glVertex2f(x0, y0);  //Origin Coordenates        
        glVertex2f(x1, y1);  //Origin Coordenates
        drawTree(x1, y1, lenFactor*branch_len, lenFactor, new_angle, _angle_factor, n);
        
        x1=x0 -sin(angle)*branch_len;
        y1=y0 +cos(angle)*branch_len;        

        glVertex2f(x0, y0);  //Origin Coordenates        
        glVertex2f(x1, y1);  //Origin Coordenates
        drawTree(x1, y1, lenFactor*branch_len, lenFactor, new_angle, _angle_factor, n);
    }
    // cout<<"First coord --->  x0 = "<<x0<<"   y0 = "<<y0<<endl;
    // cout<<"Second coord --->  x1 = "<<x1<<"   y1 = "<<y1<<endl<<endl;
}


void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT);

    /* Esta function hace lineas infinitas en tercera dimension. */
    glBegin (GL_LINES);

    glVertex2f(0.0, -0.4);
    glVertex2f(0.0,0.0);
    
    /*       x0,   y0,  lenght, len_factor, angle,    angle_factor,  iterations*/
    drawTree(0.0,  0.0,   0.4,      0.5,    3*pi/12,    1.15,   20);
 
    glEnd();
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
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
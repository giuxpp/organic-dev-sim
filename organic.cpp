#include <iostream>

using namespace std;

void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin (GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(50.0f, 50.0f, 0.0f);
    glEnd();

    glutSwatBuffers();    
}

int main(){
    cout<<endl<<"!Hi there"<<endl;
    renderScene();

    getchar();

    return 0;
}
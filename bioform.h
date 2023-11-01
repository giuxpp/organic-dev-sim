#include <GL/gl.h>
#include <iostream>

extern const float pi;

#define RAD2GRADE(xrad)    (360*xrad/(2*pi))


class bioformClass {
    private:
        GLfloat angle_main;
    
    public:
        GLfloat branch_len; 
        GLfloat len_fac; 
        GLfloat angle; 
        GLfloat angle_factor; 
        GLfloat angle_trunk;
        uint8_t nlevels;

        bioformClass(GLfloat _branch_len, GLfloat _len_fac, GLfloat _angle, GLfloat _angle_factor, GLfloat _angle_trunk, uint8_t _nlevels){
            branch_len=_branch_len; 
            len_fac=_len_fac; 
            angle=_angle; 
            angle_factor=_angle_factor; 
            angle_trunk = _angle_trunk;
            nlevels = _nlevels;
        }  

        GLfloat get_angle_main(){
            return angle_main;
        }
};


void drawBioForm(GLfloat _x, GLfloat _y, GLfloat _branch_len, GLfloat _len_fac, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n);
#include <GL/gl.h>
#include <iostream>

extern const float pi;

#define RAD2GRADE(xrad)    (360*xrad/(2*pi))


class bioformClass {
    private:


    public:
        GLfloat trunkLen;        // Trunk Lenght (lenght of first unique branch) 
        GLfloat firstBranchLen;  // First real branches Lenght
        GLfloat branchLenFact;   // Branches lenght factor (increse/decrease branches lenght)
        GLfloat angleBranches;   // Angle for the branches
        GLfloat angleFactor;     // Angle factor: Increse/decrease the branches angle
        GLfloat angleTrunk;      // Angle of the trunk
        uint8_t levels;

        bioformClass(GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle, GLfloat _angle_factor, GLfloat _angle_trunk, uint8_t _nlevels){
            trunkLen       = _trunkLen;
            firstBranchLen = _firstBranchLen; 
            branchLenFact  = _branchLenFact; 
            angleBranches  = _angle; 
            angleFactor    = _angle_factor; 
            angleTrunk     = _angle_trunk;
            levels         = _nlevels;
        }  
};


void drawBioForm(GLfloat _x, GLfloat _y, GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle0, GLfloat _angle_factor, GLfloat _newAngle, uint8_t _n);


/*#########   SOME INSTERESTING FIGURES ############
  # - Androide Tribal
  # bioformClass tree(0.1, 1.1, 2.25*pi/12, -1.1, 0, 5)
  # 
  # 
  # 
  # 
  # 
  # 
  ##################################################*/
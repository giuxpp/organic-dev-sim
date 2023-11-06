/**********************************
 *******  INCLUDE Section  ********
 ***********************************/
#include <GL/gl.h>
#include <iostream>

#define RAD2GRADE(xrad)    (360*xrad/(2*pi))
#define Pi (3.14158)

typedef struct {
    char name[20];
    GLfloat val;
    GLfloat min;
    GLfloat max;
    GLfloat step;
}geneParams;

static geneParams  gene_trunkLen      = {  "TrunkLen",       0.25f,     0.001f,      0.08f,         0.001f };
static geneParams  gene_branchLen     = {  "BranchLen",      0.25f,     0.001f,      0.08f,         0.001f };
static geneParams  gene_branchLenFact = {  "BranchLenFact",   1.0f,       0.5f,       1.5f,         0.002f };
static geneParams  gene_angleBranches = {  "angleBranches",   Pi/4,    0.05*Pi,    0.235*Pi,      Pi/240.0f };
static geneParams  gene_angleFactor   = {  "angleFactor",     1.0f,       0.5f,       1.5f,         0.002f };
static geneParams  gene_angleTrunk    = {  "angleTrunk",      Pi/4,       0.0f,    0.235*Pi,      Pi/240.0f };
static geneParams  gene_Levels        = {  "Levels",           3.0,       2.0f,       5.0f,           1.0f };

/**************************************
 *******  Main BIOFORM Class   ********
 **************************************/
class bioformClass {
    private:

    public:
        /* Genes */
        GLfloat trunkLen;        // Trunk Lenght (lenght of first unique branch) 
        GLfloat branchLen;       // First real branches Lenght
        GLfloat branchLenFact;   // Branches lenght factor (increse/decrease branches lenght)
        GLfloat angleTrunk;      // Angle of the trunk
        GLfloat angleBranches;   // Angle for the branches
        GLfloat angleFactor;     // Angle factor: Increse/decrease the branches angle    
        uint8_t levels;
        bioformClass * prevNode;

        /* Constructor */
        bioformClass(GLfloat _trunkLen, GLfloat _firstBranchLen, GLfloat _branchLenFact, GLfloat _angle_trunk, GLfloat _angleBranch, GLfloat _angle_factor, uint8_t _nlevels){
            trunkLen       = _trunkLen;
            branchLen      = _firstBranchLen; 
            branchLenFact  = _branchLenFact;             
            angleTrunk     = _angle_trunk;
            angleBranches  = _angleBranch; 
            angleFactor    = _angle_factor; 
            levels         = _nlevels;
        }  

        bioformClass(){

        }
        
};

int getMutation(void);

void bioformMutation (bioformClass *bioform);

void bioFormClone (bioformClass * src, bioformClass * dest);

/*############################################################*/
/*#############   SOME INSTERESTING FIGURES 3#################
  # 1) Androide Tribal 
  #    bioformClass tree(0.3, 0.1, 1.1, 2.25*pi/12, -1.1, 0, 5);
  # 
  # 2) Cat Face
  #    bioformClass tree(0.0,  0.005, 2, 1.85*Pi/12, 1.2, 0, 5); 
  # 
  # 
  # 
  ###########################################################
  ###########################################################*/
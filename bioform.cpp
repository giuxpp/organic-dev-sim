/**********************************
 *******  INCLUDE Section  ********
 ***********************************/
#include "bioform.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


/**************   MutationLevelsParam ()    ******************
 *   This function mutate the level parameter
 *************************************************************/
void MutationLevelsParam(uint8_t * genePtr) {
    uint8_t res=0;

    cout << "Muting param: " << gene_Levels.name << endl;
    cout << "Old value = " << (uint8_t)*genePtr <<endl;

    if (rand()%20==0) {
        res = 1;
    }
    if ((rand()%40==0) && (*genePtr>1)) {
        res -= 1;
    }
    if (*genePtr<gene_Levels.max) {
        *genePtr += res;
    }
        
    cout << "New value = " << *genePtr <<endl<<endl;
}


/**************       mutateGen      ******************
 *   This function mutate a gene
 ******************************************************/
void mutateGen(GLfloat * genePtr, geneParams * geneParamPtr)
{
    int n, res=0;//, i=20;        
    GLfloat newVal;
    
    for (int i=1; i<5; i++){
        if (rand()%(i+1)==0) {
            res = i;
        }           
    }                
    
    if (0==rand()%2){
        newVal = *genePtr - res*geneParamPtr->step_down;
    }
    else{
        newVal = *genePtr + res*geneParamPtr->step_up;
    }

    cout << "Muting param: " << geneParamPtr->name << endl;
    cout << "Old value = " << *genePtr <<endl;
    
    /* Evaluate new gene */
    if ((newVal<geneParamPtr->max) && (newVal>geneParamPtr->min))
    {
        *genePtr = newVal;
    }
    else{
        /*  TODO:
         *  This object must die */
    }
    
    cout << "New value = " << *genePtr <<endl<<endl;
}


/*************     bioformMutation    *****************
 *   Mutate a full bioform by mutating every gene
 ******************************************************/
void bioformMutation (bioformClass * bioform){
    cout << endl << "****************"<<endl<<"Starting mutation..."<<endl;
    mutateGen(&bioform->trunkLen,      &gene_trunkLen);  
    mutateGen(&bioform->branchLen,     &gene_branchLen);  
    mutateGen(&bioform->branchLenFact, &gene_branchLenFact);
    //mutateGen(&bioform->angleTrunk,    &gene_angleTrunk); 
    mutateGen(&bioform->angleBranches, &gene_angleBranches);
    mutateGen(&bioform->angleFactor,   &gene_angleFactor);  
    MutationLevelsParam(&bioform->levels); 
}

/*************     bioFormClone    *****************
 *   Clone a bioform   from  src to dest  
 ******************************************************/
void bioFormClone (bioformClass * src, bioformClass * dest)
{
    dest->trunkLen = src->trunkLen;
    dest->branchLen = src->branchLen;
    dest->branchLenFact = src->branchLenFact;
    dest->angleTrunk = src->angleTrunk;
    dest->angleBranches = src->angleBranches;
    dest->angleFactor = src->angleFactor;
    dest->levels = src->levels;
}
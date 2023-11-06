/**********************************
 *******  INCLUDE Section  ********
 ***********************************/
#include "bioform.h"
#include <iostream>
#include <stdlib.h>


using namespace std;


/******************   getMutationSteps ()    **********************
 *   This function returns the number of steps to be added or 
 *   substracted from a gene.
 *   The algorithm generates an int from -20 to +20, being the 
 *   smaller number more probable and the highest less.
 *************************************************************/
int getMutationSteps(){
    int n, res=0;//, i=20;        
    
    for (int i=1; i<5; i++){
        if (rand()%(i+1)==0) {
            res = i;
            if (0==rand()%2){
                res = -res;
            }
            return res;
        }        
    }
    return res;
}

void MutationLevelsParam(uint8_t * genePtr){
    uint8_t res=0;

    cout << "Muting param: " << gene_Levels.name << endl;
    cout << "Old value = " << (uint8_t)*genePtr <<endl;

    if (rand()%20==0) {
        res = 1;
    }
    if ((rand()%40==0) && (*genePtr>1)){
        res -= 1;
    }
    if (*genePtr<gene_Levels.max) {
        *genePtr += res;
    }
        
    cout << "New value = " << *genePtr <<endl<<endl;
}

void mutateGen(GLfloat * genePtr, geneParams * geneParamPtr)
{
    GLfloat newVal = *genePtr + getMutationSteps()*geneParamPtr->step;
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


void bioformMutation (bioformClass * bioform){
    cout << endl << "****************"<<endl<<"Starting mutation..."<<endl;
    mutateGen(&bioform->trunkLen,      &gene_trunkLen);  //cout<<"Gene trunkLen"<<endl;
    mutateGen(&bioform->branchLen,     &gene_branchLen);  //cout<<"Gene branchLen"<<endl;
    mutateGen(&bioform->branchLenFact, &gene_branchLenFact); // cout<<"Gene branchLenFact"<<endl;
    //mutateGen(&bioform->angleTrunk,    &gene_angleTrunk);  //cout<<"Gene angleTrunk"<<endl;
    mutateGen(&bioform->angleBranches, &gene_angleBranches); // cout<<"Gene angleBranches"<<endl;
    mutateGen(&bioform->angleFactor,   &gene_angleFactor);  //cout<<"Gene angleFactor"<<endl;
    MutationLevelsParam(&bioform->levels); // cout<<"Gene Levels"<<endl;
}

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
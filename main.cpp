/**********************************
 *******  INCLUDE Section  ********
 ***********************************/
#include <iostream>
//#include "bioform.h"
#include "glutInterface.h"


/**********************************
 ****    LOCAL DECLARATIONS  ******
 **********************************/ 
using namespace std;



/************   BIOFORM   OBJECTS     ************************/


/*******       main()    ***************
 *       Program starts here.     
 ***************************************/
int main(int argc, char** argv){
       
    initGlutRoutine(argc, argv);
    
        
    while (1){
        /**     glutMainLoop()  
         *  Enters the GLUT event processing loop. This routine should be called at most 
         *  once in a GLUT program.  Once called, this routine will never return. 
         *  It will call as necessary any callbacks that have been registered   */        
        EnterGlutLoop();
        
    }    
    
    return 0;
}



/**********************************
 *******  INCLUDE Section  ********
 ***********************************/
#include <iostream>
#include "bioform.h"
#include "glutInterface.h"


/**********************************
 ****    LOCAL DECLARATIONS  ******
 **********************************/ 
using namespace std;


/*******       main()    ***************
 *       Program starts here.     
 ***************************************/
int main(int argc, char** argv){
       
    initGlutRoutine(argc, argv);
    startNodes();
    srand(time(0));//seed the rand function. Timer changes every second.  time(0)
        
    while (1){
        /**     glutMainLoop()  
         *  Enters the GLUT event processing loop. This routine should be called at most 
         *  once in a GLUT program.  Once called, this routine will never return. 
         *  It will call as necessary any callbacks that have been registered   */        
        EnterGlutLoop();
    }    
    
    return 0;
}



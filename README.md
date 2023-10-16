*** ORGANIC DEVELOP SIMULATOR ***

By: Giux  
           
         Description:
            Simulates the develope of organic-like figures from a set of simple rules
            and their mutations trough several generations.
  
         Requirements:
            To have GL libraries installed.
  
         Build Command:
            Since this code uses OpenGL library they need to be     
            called in the build command in the same order as in the
            include section. Use the next command:

            g++ organic.cpp -o organic.out -lGL -lGLU -lglut

 *          Notes: Find demos/examples for using GL library at:
*           https://cs.lmu.edu/~ray/notes/openglexamples/           
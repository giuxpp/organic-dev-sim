*** ORGANIC DEVELOPER SIMULATOR ***

By: Giuxpp  
           
         Description:
            Simulates the develope of organic-like figures or "bioforms" from a set of
            simple rules or "genes" and their mutations trough several generations.
  
         Requirements:
            To have GL libraries installed and Gcc compiler.
  
         Build Command:
            Since this code uses OpenGL library they need to be     
            called in the build command in the same order as in the
            include section. Use the next command:

            g++ organic.cpp bioform.cpp -o organic.out -lGL -lGLU -lglut 

         Build Express:
            Just use the makefile by sending this command on terminal:
            >> make



- HOW TO INSTALL OPEN GL LIBRARY -

Linux: 
   Follow next steps or visit:
      https://utho.com/docs/tutorial/how-to-install-the-opengl-library-on-ubuntu-20-04/

      # Step 1: Update Server
      >> sudo apt update && sudo apt upgrade

      # Step 2: Install OpenGL Library
      >> sudo apt install freeglut3-dev

      # Step 3: Verify Installation
      >> dpkg -L freeglut3-dev

      # Step 4: Uninstall OpenGL Library (optional)
      # After you have finished making use of the freeglut library
      >> sudo apt remove freeglut3-dev



         .....::::::::::::::::::......
         :::::::: ENJOY LIFE :::::::::
         :::::::::::::::::::::::::::::
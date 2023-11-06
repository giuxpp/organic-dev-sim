#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>


/* Glut Configuration */
#define window_width               600
#define window_height              600
#define disp_x_range_min          (-0.6)
#define disp_x_range_max          ( 0.6)
#define disp_y_range_min          (-0.8)
#define disp_y_range_max          ( 0.8)

typedef struct {
    GLfloat x;
    GLfloat y;
}point;


/** Color in RGB. From 0.0 to 1.0 */
typedef struct {
    float red;
    float green;
    float blue;
}gxp_color;

#define COLOR_WHITE       {1.0f, 1.0f, 1.0f}

/* Glut library related interfaces */
void initGlutRoutine(int argc, char** argv);
void EnterGlutLoop(void);
void startNodes (void);



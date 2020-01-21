#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

/* world size and storage array */
#define WORLDX 100
#define WORLDY 50
#define WORLDZ 100

/* list of cubes to draw with each screen update */
#define MAX_DISPLAY_LIST 500000

/* maximum number of user defined colours */
#define NUMBERCOLOURS 100

GLubyte world[WORLDX][WORLDY][WORLDZ];

/* initilize graphics information and mob data structure */
void graphicsInit(int *argc, char **argv);

/* Functions for user defined colours */
int setUserColour(int id, GLfloat ambRed, GLfloat ambGreen, GLfloat ambBlue,
                  GLfloat ambAlpha, GLfloat difRed, GLfloat difGreen,
                  GLfloat difBlue, GLfloat difAlpha);

/***** Mob Controls *****/
/* create mob with identifier "number" at x,y,z with */
/* heading of rotx, roty, rotz */
void createMob(int number, float x, float y, float z, float mobroty);

/***** Player Controls *****/
/* create player with identifier "number" at x,y,z with */
/* heading of rotx, roty, rotz */
void createPlayer(int number, float x, float y, float z, float playerroty);

/* Viewpoint Control */
void setViewPosition(float, float, float);
void getViewPosition(float *, float *, float *);

int withinBounds(int xLoc, int yLoc, int zLoc);
#endif

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

/* Entity Counts */
#define MOB_COUNT 10
#define PLAYER_COUNT 10
#define TUBE_COUNT 10

/* list of cubes to draw with each screen update */
#define MAX_DISPLAY_LIST 500000

/* maximum number of user defined colours */
#define NUMBERCOLOURS 100

GLubyte world[WORLDX][WORLDY][WORLDZ];

/*** Command arguments and flags ***/

int flycontrol; // flag which is set to 0 when flying behaviour is desired
int testWorld;  // flag used to indicate that the test world should be used
int fps;        // flag to print out frames per sxecond
int space;      // flag to indicate the space bar has been pressed
int netClient;  // flag indicates the program is a client when set = 1
int netServer;  // flag indicates the program is a server when set = 1
int screenWidth, screenHeight; // size of the window in pixels
int displayMap;                // flag indicates if map is to be printed
int fixedVP;                   // flag indicates use of a fixed viewpoint
double fastFly;                // speedier flying flag, is true when = 1.0

/* list of cubes to display */
int displayList[MAX_DISPLAY_LIST][3];
int displayCount; // count of cubes in displayList[][]

/***** Graphics Initiallization *****/
void graphicsInit(int *argc, char **argv);

/***** Lighing Controls *****/
void setLightPosition(GLfloat, GLfloat, GLfloat);
GLfloat *getLightPosition();

/***** 3D Drawing Functions *****/
void addDisplayList(int, int, int);

/***** 2D Drawing Functions *****/
void draw2Dline(int, int, int, int, int);
void draw2Dbox(int, int, int, int);
void draw2Dtriangle(int, int, int, int, int, int);
void set2Dcolour(float[]);

/***** User defined Colours *****/
int setUserColour(int id, GLfloat ambRed, GLfloat ambGreen, GLfloat ambBlue,
                  GLfloat ambAlpha, GLfloat difRed, GLfloat difGreen,
                  GLfloat difBlue, GLfloat difAlpha);
void unsetUserColour(int);
void getUserColour(int, GLfloat *, GLfloat *, GLfloat *, GLfloat *, GLfloat *,
                   GLfloat *, GLfloat *, GLfloat *);

/***** Mob Controls *****/
void createMob(int number, float x, float y, float z, float mobroty);
void setMobPosition(int, float, float, float, float);
void hideMob(int);
void showMob(int);

/***** Player Controls *****/
void createPlayer(int number, float x, float y, float z, float playerroty);
void setPlayerPosition(int, float, float, float, float);
void hidePlayer(int);
void showPlayer(int);

/***** Tube Controls *****/
void createTube(int, float, float, float, float, float, float, int);
void hideTube(int);
void showTube(int);

/***** Viewpoint Controls *****/
void setViewPosition(float, float, float);
void getViewPosition(float *, float *, float *);
void getOldViewPosition(float *, float *, float *);
void setOldViewPosition(float, float, float);
void setViewOrientation(float, float, float);
void getViewOrientation(float *, float *, float *);

/* World boundary collision detection */
int withinBounds(int xLoc, int yLoc, int zLoc);
#endif

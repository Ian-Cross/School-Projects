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
#define MOB_COUNT 1000
#define PLAYER_COUNT 10
#define TUBE_COUNT 10

/* list of cubes to draw with each screen update */
#define MAX_DISPLAY_LIST 500000

/* maximum number of user defined colours */
#define NUMBERCOLOURS 100

GLubyte world[WORLDX][WORLDY][WORLDZ];

/*** Command arguments and flags ***/

int flycontrol; // flag which is set to 0 when flying behaviour is desired
int fps;        // flag to print out frames per sxecond
int space;      // flag to indicate the space bar has been pressed
int netClient;  // flag indicates the program is a client when set = 1
int netServer;  // flag indicates the program is a server when set = 1
int screenWidth, screenHeight; // size of the window in pixels
int displayMap;                // flag indicates if map is to be printed
int displayAllCubes;           // draw all of the cubes in the world when 1
int fixedVP;                   // flag indicates use of a fixed viewpoint
double fastFly;                // speedier flying flag, is true when = 1.0

/* list of cubes to display */
int displayList[MAX_DISPLAY_LIST][3];
int displayCount; // count of cubes in displayList[][]

/* list of mobs - number of mobs, xyz values and rotation about y */
float mobPosition[MOB_COUNT][4];
/* visibility of mobs, 0 not drawn, 1 drawn */
short mobVisible[MOB_COUNT];

/* flags used to control the appearance of the image */
int lineDrawing;   // draw polygons as solid or lines
int lighting;      // use diffuse and specular lighting
int smoothShading; // smooth or flat shading
int textures;

/* texture data */
GLubyte Image[64][64][4];
GLuint textureID[1];

/* viewpoint coordinates */
float vpx, vpy, vpz;
float oldvpx, oldvpy, oldvpz;

/* mouse direction coordiates */
float mvx, mvy, mvz;

/* stores current mouse position value */
float oldx, oldy;

/* sky cube size */
float skySize;

/* list of players - number of mobs, xyz values and rotation about y */
float playerPosition[PLAYER_COUNT][4];
/* visibility of players, 0 not drawn, 1 drawn */
short playerVisible[PLAYER_COUNT];

/* list of tubes - number of tubes, staring x, y, z position, ending  */
/*  x, y, z position */
float tubeData[TUBE_COUNT][6];
/* tube colour for each tube */
int tubeColour[TUBE_COUNT];
/* visibility of tubes, 0 not drawn, 1 drawn */
short tubeVisible[TUBE_COUNT];

/* list of user defined colours */
/* ambient (RGBA) followed by diffuse (RGBA) */
GLfloat uAmbColour[NUMBERCOLOURS][4];
GLfloat uDifColour[NUMBERCOLOURS][4];
/* flag indicating user defined colour has been allocated */
/* initialized to 0, set to 1 when colour stored in uColour[][] */
int uColourUsed[NUMBERCOLOURS];

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
int setUserColour(int, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,
                  GLfloat, GLfloat);
void unsetUserColour(int);
void getUserColour(int, GLfloat *, GLfloat *, GLfloat *, GLfloat *, GLfloat *,
                   GLfloat *, GLfloat *, GLfloat *);

/***** Mob Controls *****/
void createMob(int, float, float, float, float);
void setMobPosition(int, float, float, float, float);
void hideMob(int);
void showMob(int);

/***** Player Controls *****/
void createPlayer(int, float, float, float, float);
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
#endif

#ifndef TEST_HEADER
#define TEST_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define TRUE 1
#define FALSE 0

typedef struct rect {
  int x;
  int z;
  int hx;
  int hz;
} Rect;

typedef struct Coords {
  int x;
  int y;
  int z;
} Coord;

typedef enum userColours {
  GRASS_1 = 9,
  GRASS_2 = 10,
  GRASS_3 = 11,
  GRASS_4 = 12,
  GRASS_5 = 13,

  DIRT_1 = 14,
  DIRT_2 = 15,
  DIRT_3 = 16,
  DIRT_4 = 17,
  DIRT_5 = 18,

  OLD_BASE = 19,
  CLOUD_1 = 20,
  CLOUD_2 = 21,
  CLOUD_3 = 22,
  FIRE_1 = 23,
  FIRE_2 = 24,
  FIRE_3 = 25,
  METEOR = 26,
  BASE_1 = 27,
  BASE_2 = 28,
  IDENTIFIED_METEOR = 29,
  VEHICLE_1 = 30,
  VEHICLE_2 = 31,
  TIRES = 32,
} UserColours;

#include "graphics.h"
#include "visible.h"

#include "base.h"
#include "cloud.h"
#include "generation.h"
#include "hill.h"
#include "meteor.h"
#include "team.h"
#include "valley.h"

typedef struct projectile Projectile;

typedef struct worldData {
  int worldId;
  Object *objects[BASE_COUNT + MAX_VALLEY_COUNT + MAX_HILL_COUNT];
  Cloud *clouds[MAX_CLOUD_COUNT];
  Meteor *meteors;
  Team *teams[2];
  Projectile *projectiles;
} WorldData;

WorldData *newWorld;

#include "projectile.h"
#include "timing.h"
#include "tower.h"
#include "truck.h"

int paused;
GLfloat ambRed, ambGreen, ambBlue, ambAlpha, difRed, difGreen, difBlue,
    difAlpha;

/*** withinBounds() ***/
/* - Checks to ensure the given location is inside the defined world array */
int withinBounds(float, float, float);

/*** collisionResponse() ***/
/* -performs collision detection and response */
/*  sets new xyz  to position of the viewpoint after collision */
/* -can also be used to implement gravity by updating y position of vp*/
/* note that the world coordinates returned from getViewPosition()
   will be the negative value of the array indices */
void collisionResponse();

/******* draw2D() *******/
/* - draws 2D shapes on screen */
/* - use the following functions: */
/* - draw2Dline(int, int, int, int, int); */
/* - draw2Dbox(int, int, int, int);	*/
/* - draw2Dtriangle(int, int, int, int, int, int); */
/* - set2Dcolour(float []); */
/* - colour must be set before other functions are called	*/
void draw2D();

/*** update() ***/
/* background process, it is called when there are no other events */
/* -used to control animations and perform calculations while the  */
/*  system is running */
/* -gravity must also implemented here, duplicate collisionResponse */
void update();

/* called by GLUT when a mouse button is pressed or released */
/* -button indicates which button was pressed or released */
/* -state indicates a button down or button up event */
/* -x,y are the screen coordinates when the mouse is pressed or */
/*  released */
void mouse(int, int, int, int);

#endif

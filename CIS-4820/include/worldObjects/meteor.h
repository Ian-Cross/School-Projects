#ifndef METEOR_HEADER
#define METEOR_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define METEOR_MOVE_SPEED 50

typedef struct Meteors {
  int xLoc;
  int zLoc;
  int yLoc;
  int xVel;
  int zVel;
  int yVel;
  int falling;
  int render;
  struct Meteors *next;
  struct Meteors *prev;
} Meteor;

/******* createFalseMeteor() *******/
/* - Allocate memory space for the Meteor */
/* - fill everything in with garbage values */
/* - set render to false, so it will never show */
/* - only use this for list managment */
Meteor *createFalseMeteor();

/******* createMeteor() *******/
/* - Allocate memory space for the Meteor */
/* - Generate random landing location */
/* - Generate random direction unit vector */
/* - calculate starting location from landing location and direction */
Meteor *createMeteor();

/******* drawMeteor() *******/
/* - Input Meteor object  */
/* - Draw the meteor at its location, add on flame tail */
/* - Only draw the meteor or tail if it is within the world bounds */
void drawMeteor(Meteor *meteor);

/******* moveMeteor() *******/
/* - Input Meteor object */
/* - add the metoros velocity vector onto its position to move it */
/* - Check if the meteor will hit something, stop its movement */
/*   and remove its tail if it will */
void moveMeteor(Meteor *meteor);

/******* clearMeteor() *******/
/* - Input meteor object */
/* - Remove the meteor and tail from the world array */
/* - Ensure the meteor spot is within the world */
void clearMeteor(Meteor *meteor);

/******* clearTail() *******/
/* - Input meteor object */
/* - Remove the meteor's trailing flames from the world array */
/* - Ensure the tail spot is in the world bounds */
void clearTail(Meteor *meteor);

#endif

#ifndef CLOUD_HEADER
#define CLOUD_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define MAX_CLOUD_COUNT 2000
#define GROWTH_CHANCE 100

#define CLOUD_MOVE_SPEED 1

typedef struct Clouds {
  int xLoc;
  int zLoc;
  int yLoc;
} Cloud;

/******* createCloud() *******/
/* - Allocate memory space for the cloud */
/* - Generate random location and render to screen */
Cloud *createCloud(int xLoc, int zLoc);

/******* moveCloud() *******/
/* - Inputs cloud object and moves by 1 in the x direction*/
/* - Wrap around if hits the edge of the world */
void moveCloud(Cloud *cloud);

/******* drawCloud() *******/
/* - Inputs cloud object and renders to the world */
/* - Picks a random colour from a group of greys */
void drawCloud(Cloud *cloud);

/******* clearCloud() *******/
/* - Inputs cloud object and clears that spot in the world */
void clearCloud(Cloud *cloud);

#endif

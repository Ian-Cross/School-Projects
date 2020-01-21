#ifndef CLOUD_HEADER
#define CLOUD_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define MAX_CLOUD_COUNT 2000
#define GROWTH_CHANCE 100

#define MOVE_SPEED 1

typedef struct Clouds {
  int xLoc;
  int zLoc;
  int yLoc;
} Cloud;

Cloud *createCloud(int xLoc, int zLoc);
void drawCloud(Cloud *cloud);
void moveCloud(Cloud *cloud);
void clearCloud(Cloud *cloud);

#endif

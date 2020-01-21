#ifndef VALLEY_HEADER
#define VALLEY_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define VALLEY_SIZE 7
#define MAX_VALLEY_COUNT 10
#define MIN_VALLEY_COUNT 5

typedef struct Valleys {
  int radius;
  int xLoc;
  int zLoc;
  int depth;
  int render;
} Valley;

Valley *createValley();

void drawValley(Valley *valley);

#endif

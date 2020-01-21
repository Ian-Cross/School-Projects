#ifndef HILL_HEADER
#define HILL_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define HILL_SIZE 7
#define MAX_HILL_COUNT 10
#define MIN_HILL_COUNT 5

typedef struct Hills {
  int radius;
  int xLoc;
  int zLoc;
  int height;
  int render;
} Hill;

Hill *createHill();

void drawHill(Hill *hill);

#endif

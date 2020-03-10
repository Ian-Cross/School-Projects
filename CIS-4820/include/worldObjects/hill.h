#ifndef HILL_HEADER
#define HILL_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define HILL_SIZE 7
#define MAX_HILL_COUNT 15
#define MIN_HILL_COUNT 7

typedef struct Hills {
  int radius;
  int xLoc;
  int zLoc;
  int height;
  Rect *(*getSurrounding)(struct Hills *);
  void (*changeLocation)(struct Hills *);
} Hill;

/******* createHill() *******/
/* - Allocate memory space for the Hill */
/* - Generate random location and sizes */
Hill *createHill();

/******* drawHill() *******/
/* - Input Hill object  */
/* - Builds the circles line by line */
/* - Dig into the world in shinking circles to build a Hill */
void drawHill(Hill *hill);

#endif

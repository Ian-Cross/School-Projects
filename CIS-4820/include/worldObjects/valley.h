#ifndef VALLEY_HEADER
#define VALLEY_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define VALLEY_SIZE 7
#define MAX_VALLEY_COUNT 15
#define MIN_VALLEY_COUNT 7

typedef struct Valleys {
  int radius;
  int xLoc;
  int zLoc;
  int depth;
  Rect *(*getSurrounding)(struct Valleys *);
  void (*changeLocation)(struct Valleys *);
} Valley;

/******* createValley() *******/
/* - Allocate memory space for the valley */
/* - Generate random location and sizes */
Valley *createValley();

/******* drawValley() *******/
/* - Input Valley object  */
/* - Builds the circles line by line */
/* - Dig into the world in shinking circles to build a Valley */
void drawValley(Valley *valley);

#endif

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

#ifndef RECT_OBJ
typedef struct Rects {
  int x;
  int z;
  int hx;
  int hz;
} Rect;
#define RECT_OBJ
#endif

typedef struct Valleys {
  int radius;
  int xLoc;
  int zLoc;
  int depth;
  Rect *(*getSurrounding)(struct Valleys *);
  void (*changeLocation)(struct Valleys *);
} Valley;

Valley *createValley();

void drawValley(Valley *valley);

#endif

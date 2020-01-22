#ifndef BASE_HEADER
#define BASE_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define BASE_SIZE 10
#define BASE_COUNT 2

#ifndef RECT_OBJ
typedef struct Rects {
  int x;
  int z;
  int hx;
  int hz;
} Rect;
#define RECT_OBJ
#endif

typedef struct Bases {
  int width;
  int length;
  int height;
  int xLoc;
  int zLoc;
  Rect *(*getSurrounding)(struct Bases *);
} Base;

void createBase(Base *base, int baseNum);

void drawBase(Base *base);

#endif

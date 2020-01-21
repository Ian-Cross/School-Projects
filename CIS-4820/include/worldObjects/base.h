#ifndef BASE_HEADER
#define BASE_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define BASE_SIZE 10
#define BASE_COUNT 2

typedef struct Bases {
  int width;
  int length;
  int height;
  int xLoc;
  int zLoc;
} Base;

void createBase(Base *base, int baseNum);

void drawBase(Base *base);

#endif

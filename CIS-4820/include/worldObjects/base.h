#ifndef BASE_HEADER
#define BASE_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define BASE_SIZE 5
#define BASE_COUNT 2

typedef struct Bases {
  int width;
  int length;
  int height;
  int xLoc;
  int zLoc;
  int colour;
  Rect *(*getSurrounding)(struct Bases *);
} Base;

/******* createBase() *******/
/* - Input base id */
/* - allocate memory for the base */
/* - randomize values and fill the object returning it */
Base *createBase(int);

/******* drawBase() *******/
/* - Input base object  */
/* - Iterate over 3 dimensions to build the base block by block */
void drawBase(Base *);

#endif

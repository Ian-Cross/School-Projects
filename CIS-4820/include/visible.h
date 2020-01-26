#ifndef VISIBLE_HEADER
#define VISIBLE_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

/* frustum corner coordinates, used for visibility determination  */
float corners[4][3];
/* determine which cubes are visible e.g. in view frustum */
void ExtractFrustum();
void tree(float, float, float, float, float, float, int);

#endif

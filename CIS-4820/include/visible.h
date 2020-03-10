#ifndef VISIBLE_HEADER
#define VISIBLE_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define OCTREE_LEVEL 1

/* frustum corner coordinates, used for visibility determination  */
float corners[4][3];
float frustum[6][4];

/* calculate the viewing frustum and test if cubes fall inside it */
/* code from */
/* http://www.crownandcutlass.com/features/technicaldetails/frustum.html */
/* determine which cubes are visible e.g. in view frustum */
void ExtractFrustum();

// if frustum test shows box in view
//    if level == max level then draw contents of cube
//    else call 8 subdivisions, increment level
// assumes all t[xyz] are larger than b[xyz] respectively
void tree(float, float, float, float, float, float, int);

/* determines which cubes are to be drawn and puts them into */
/* the displayList  */
/* write your cube culling code here */
void buildDisplayList();

#endif

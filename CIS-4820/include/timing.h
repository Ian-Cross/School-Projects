#ifndef TIMING_HEADER
#define TIMING_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

/******* moveClouds() *******/
/* - Iterate over all the clouds */
/* - Move each cloud by 1 space every 1 second */
void moveClouds();

#endif

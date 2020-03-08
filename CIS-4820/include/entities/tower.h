#ifndef TOWER_HEADER
#define TOWER_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "generation.h"

typedef struct tower {
  int xLoc;
  int zLoc;
  int yLoc;
  int projectile;
} Tower;

Tower *createTower();

void drawTower();

void towerSurvey();

#endif

#ifndef TEAM_HEADER
#define TEAM_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "base.h"
#include "truck.h"

#define TRUCKCOUNT 5

typedef struct Teams {
  int teamNumber;
  int teamColour;
  Base *base;
  Truck *trucks[TRUCKCOUNT];
} Team;

void createTeams();

#endif

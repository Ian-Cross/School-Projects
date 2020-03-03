#ifndef TRUCK_HEADER
#define TRUCK_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "generation.h"

typedef enum truckState {
  searching = 0,
  moving,
  loading,
  returning,
} TruckState;

typedef struct truck {
  int xLoc;
  int zLoc;
  int yLoc;
  int state;
} Truck;

Truck *createTruck();

void drawTruck();

#endif

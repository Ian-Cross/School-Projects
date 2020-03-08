#ifndef TRUCK_HEADER
#define TRUCK_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "generation.h"

#define TRUCK_SPEED 200

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
  int searchX;
  int searchZ;
  int searchY;
  int state;
  int hasMeteor;
  double lastTimeMoved;
  int loadCount;
  int health;
  int team;
} Truck;

Truck *createTruck();

void drawTruck();

void moveTruck();
void clearTruck();
int wasHit();

Truck *truckLookup();
void teleportToBase();

#endif

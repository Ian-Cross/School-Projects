#ifndef TRUCK_HEADER
#define TRUCK_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define TRUCK_SPEED 200
#define TRUCK_SEARCH_RADIUS 10
#define TRUCK_EXPLOSION_RADIUS 4

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
  struct truck *next;
} Truck;

/*** createTruck() ***/
/* - Allocate space and fill values for the truck object */
Truck *createTruck(Base *, int);

void addTruck(int);

/*** drawTruck() ***/
/* - Render the truck at its current x and z location */
/* - Pick a y location that puts it ontop of the world to account for hills and
 * valleys */
/* - uses two offset arrays to build the truck based on 1 (x,z) location */
void drawTruck(Truck *);

/*** moveTruck() ***/
/* - parent function to decide, based on the truck state machine, how the truck
 * is going to move */
/* - Possible states are:
       seaching for meteor,
       moving towards meteor,
       loading meteor,
       returning to base */
void moveTruck(Truck *, Team *);

/*** clearTruck() ***/
/* - when the truck moves, remove the old truck from the world array */
void clearTruck(Truck *);

/*** truckLookup() ***/
/* - used for when a projectile hits a truck */
/* - input with the world location that was hit */
/* - check if the inputted location matches any that would be a part of a truck
on an enemy team */
/* - return the truck if anything mathes, null on error /not found */
Truck *truckLookup(int, int, int);

/*** teleportToBase() ***/
/* - used when the truck is hit and killed */
/* - moves the truck back to its spawn location and resets stats */
/* - leaves an "explosion crater" where the truck was killed */
void teleportToBase(Truck *);

#endif

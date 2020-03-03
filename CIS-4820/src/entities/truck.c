#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generation.h"
#include "graphics.h"

Coord TRUCKSHAPE[5] = {{-1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {-1, 1, 0}};
Coord TRUCKTIRES[4] = {{-1, 0, -1}, {-1, 0, 1}, {1, 0, -1}, {1, 0, 1}};

int TRUCKADJUST[5] = {-8, -4, 0, 4, 8};

int direction[4][3] = {{1, 1, 1}, {-1, 1, 1}, {1, 1, -1}, {1, 1, -1}};

/*** createTruck() ***/
/* - */
Truck *createTruck(Base *base, int truckNum, int teamNumber) {
  Truck *newTruck = (Truck *)malloc(sizeof(Truck));
  if (newTruck == NULL)
    printf("Unable to allocate space for truck");

  newTruck->xLoc = base->xLoc + (teamNumber == 0 ? -10 : 10);
  newTruck->yLoc = 0;
  newTruck->zLoc = base->zLoc + TRUCKADJUST[truckNum];
  newTruck->state = searching;
  return newTruck;
}

int getGroundHeight(Truck *truck) {
  int heighestY = 0;
  int length = sizeof(TRUCKTIRES) / sizeof(TRUCKTIRES[0]);
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < WORLDY; j++) {
      if (world[truck->xLoc + TRUCKTIRES[i].x][j]
               [truck->zLoc + TRUCKTIRES[i].z] == 0) {
        if (j > heighestY)
          heighestY = j;
        break;
      }
    }
  }
  return heighestY;
}

int getDirection(Truck *truck, Team *team) {
  int teamMultiplyer = (team->teamNumber == 0 ? -1 : 1);
  switch (truck->state) {
  case searching:
    return 1 * teamMultiplyer;
  case moving:
    return 1 * teamMultiplyer;
  case loading:
    return 1 * teamMultiplyer;
  case returning:
    return -1 * teamMultiplyer;
  }
  return 1;
}

void drawTruck(Truck *truck, Team *team) {
  int length = sizeof(TRUCKSHAPE) / sizeof(TRUCKSHAPE[0]);
  int highestY = getGroundHeight(truck);
  truck->yLoc = highestY;
  int dir = getDirection(truck, team);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCKSHAPE[i].x * dir][highestY + TRUCKSHAPE[i].y]
         [truck->zLoc + TRUCKSHAPE[i].z] = team->teamColour;
  }

  length = sizeof(TRUCKTIRES) / sizeof(TRUCKTIRES[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCKTIRES[i].x * dir][highestY + TRUCKTIRES[i].y]
         [truck->zLoc + TRUCKTIRES[i].z] = 4;
  }
}

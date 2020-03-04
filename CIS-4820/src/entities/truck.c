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

  newTruck->xLoc = base->xLoc + (teamNumber == TEAM_ONE ? -10 : 10);
  newTruck->yLoc = 0;
  newTruck->zLoc = base->zLoc + TRUCKADJUST[truckNum];
  newTruck->state = searching;
  newTruck->hasMeteor = 0;
  newTruck->loadCount = 0;

  newTruck->searchX = rand() % (WORLDX - 20) + 10;
  newTruck->searchZ = rand() % (WORLDZ - 20) + 10;
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
  int teamMultiplyer = (team->teamNumber == TEAM_ONE ? -1 : 1);
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
  if (truck->hasMeteor) {
    world[truck->xLoc + dir][highestY + 1][truck->zLoc] = 29;
  }
}

void clearTruck(Truck *truck, Team *team) {
  int length = sizeof(TRUCKSHAPE) / sizeof(TRUCKSHAPE[0]);
  int dir = getDirection(truck, team);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCKSHAPE[i].x * dir][truck->yLoc + TRUCKSHAPE[i].y]
         [truck->zLoc + TRUCKSHAPE[i].z] = 0;
  }

  length = sizeof(TRUCKTIRES) / sizeof(TRUCKTIRES[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCKTIRES[i].x * dir][truck->yLoc + TRUCKTIRES[i].y]
         [truck->zLoc + TRUCKTIRES[i].z] = 0;
  }
  if (truck->hasMeteor) {
    world[truck->xLoc + dir][truck->yLoc + 1][truck->zLoc] = 0;
  }
}

void newSearchArea(Truck *truck) {
  truck->searchX = rand() % (WORLDX - 20) + 10;
  truck->searchZ = rand() % (WORLDZ - 20) + 10;
}

int searchArea(Truck *truck) {

  int radius = 10;
  for (int y = truck->yLoc - 1; y < truck->yLoc + 1; y++) {
    for (int z = -radius; z < radius; z++) {
      int half_row_width = sqrt(radius * radius - z * z);
      for (int x = -half_row_width; x < half_row_width; x++) {
        if (withinBounds(truck->xLoc + x, y, truck->zLoc + z))
          if (world[truck->xLoc + x][y][truck->zLoc + z] == 26) {
            truck->searchX = truck->xLoc + x;
            truck->searchZ = truck->zLoc + z;
            truck->searchY = y;
            world[truck->xLoc + x][y][truck->zLoc + z] = 29;
            return 1;
          }
      }
    }
  }
  return 0;
}

void moveSearching(Truck *truck) {
  if (truck->xLoc - truck->searchX < 0)
    truck->xLoc += 1;
  else if (truck->xLoc - truck->searchX > 0)
    truck->xLoc -= 1;
  else
    truck->searchX = rand() % (WORLDX - 20) + 10;

  if (truck->zLoc - truck->searchZ < 0)
    truck->zLoc += 1;
  else if (truck->zLoc - truck->searchZ > 0)
    truck->zLoc -= 1;
  else
    truck->searchZ = rand() % (WORLDZ - 20) + 10;
}

int moveTowards(Truck *truck) {
  // Move towards the identified meteor
  if (truck->xLoc - truck->searchX < 0)
    truck->xLoc += 1;
  else if (truck->xLoc - truck->searchX > 0)
    truck->xLoc -= 1;

  if (truck->zLoc - truck->searchZ < 0)
    truck->zLoc += 1;
  else if (truck->zLoc - truck->searchZ > 0)
    truck->zLoc -= 1;

  // Landed on the meteor
  if (truck->zLoc - truck->searchZ == 0 && truck->xLoc - truck->searchX == 0) {
    return 1;
  }
  return 0;
}

int moveHome(Truck *truck, Base *home) {
  if (truck->xLoc - home->xLoc < 0)
    truck->xLoc += 1;
  else if (truck->xLoc - home->xLoc > 0)
    truck->xLoc -= 1;

  if (truck->zLoc - home->zLoc < 0)
    truck->zLoc += 1;
  else if (truck->zLoc - home->zLoc > 0)
    truck->zLoc -= 1;

  if (truck->zLoc - home->zLoc == 0 && truck->xLoc - home->xLoc == 0) {
    truck->hasMeteor = 0;
    newSearchArea(truck);
    return 1;
  }
  return 0;
}

void moveTruck(Truck *truck, Team *team) {
  switch (truck->state) {
  case searching: {
    moveSearching(truck);
    if (searchArea(truck))
      truck->state = moving;
    break;
  }
  case moving: {
    if (moveTowards(truck))
      truck->state = loading;
    break;
  }
  case loading: {
    if (truck->loadCount >= 15) {
      truck->loadCount = 0;
      truck->hasMeteor = 1;
      truck->state = returning;
      world[truck->searchX][truck->searchY][truck->searchZ] = 0;
    } else {
      truck->loadCount++;
    }
    break;
  }
  case returning: {
    if (moveHome(truck, team->base)) {
      team->meteorCount++;
      newSearchArea(truck);
      truck->state = searching;
    };
    break;
  }
  }
}

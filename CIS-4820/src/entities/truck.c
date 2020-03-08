#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generation.h"
#include "graphics.h"

Coord TRUCK_SHAPE[5] = {
    {-1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {-1, 1, 0}, {0, 1, 0}};
Coord TRUCK_TIRES[4] = {{-1, 0, -1}, {-1, 0, 1}, {1, 0, -1}, {1, 0, 1}};
//
// Coord TRUCK_SHAPE[18] = {
//     {-1, 0, -1}, {0, 0, -1}, {1, 0, -1}, {-1, 1, -1}, {0, 1, -1}, {1, 1, -1},
//     {-1, 2, -1}, {0, 2, -1}, {1, 2, -1}, {-1, 0, 0},  {0, 0, 0},  {1, 0, 0},
//     {-1, 1, 0},  {0, 1, 0},  {1, 1, 0},  {-1, 2, 0},  {0, 2, 0},  {1, 2, 0}};
// Coord TRUCK_TIRES[9] = {{-1, 0, 1}, {0, 0, 1}, {1, 0, 1},
//                         {-1, 1, 1}, {0, 1, 1}, {1, 1, 1},
//                         {-1, 2, 1}, {0, 2, 1}, {1, 2, 1}};

int TRUCK_ADJUST[5] = {-8, -4, 0, 4, 8};
int direction[4][3] = {{1, 1, 1}, {-1, 1, 1}, {1, 1, -1}, {1, 1, -1}};

/*** createTruck() ***/
/* - */
Truck *createTruck(Base *base, int truckNum, int teamNumber) {
  Truck *newTruck = (Truck *)malloc(sizeof(Truck));
  if (newTruck == NULL)
    printf("Unable to allocate space for truck");

  newTruck->xLoc = base->xLoc + (teamNumber == TEAM_ONE ? -10 : 10);
  newTruck->yLoc = 0;
  newTruck->zLoc = base->zLoc + TRUCK_ADJUST[truckNum];
  newTruck->state = searching;
  newTruck->hasMeteor = 0;
  newTruck->loadCount = 0;
  newTruck->health = 2;
  newTruck->lastTimeMoved = 0;
  newTruck->searchX = rand() % (WORLDX - 20) + 10;
  newTruck->searchZ = rand() % (WORLDZ - 20) + 10;
  newTruck->team = teamNumber;

  return newTruck;
}

int getGroundHeight(Truck *truck, int dir) {
  int heighestY = 0;

  int length = sizeof(TRUCK_SHAPE) / sizeof(TRUCK_SHAPE[0]);
  for (int i = 0; i < length; i++) {
    for (int k = 0; k < WORLDY; k++) {
      if (world[truck->xLoc + TRUCK_SHAPE[i].x * dir][k]
               [truck->zLoc + TRUCK_SHAPE[i].z] == 0) {
        if (k > heighestY)
          heighestY = k;
        break;
      }
    }
  }

  length = sizeof(TRUCK_TIRES) / sizeof(TRUCK_TIRES[0]);
  for (int i = 0; i < length; i++) {
    for (int k = 0; k < WORLDY; k++) {
      if (world[truck->xLoc + TRUCK_TIRES[i].x * dir][k]
               [truck->zLoc + TRUCK_TIRES[i].z] == 0) {
        if (k > heighestY)
          heighestY = k;
        break;
      }
    }
  }
  return heighestY;
}

int getDirection(Truck *truck, int teamNumber) {
  int teamMultiplyer = (teamNumber == TEAM_ONE ? -1 : 1);
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

Truck *truckLookup(int x, int y, int z) {
  for (int i = 0; i < TEAM_COUNT; i++) {
    Team *team = newWorld->teams[i];
    for (int j = 0; j < TRUCK_COUNT; j++) {
      Truck *truck = team->trucks[j];
      int length = sizeof(TRUCK_SHAPE) / sizeof(TRUCK_SHAPE[0]);
      int dir = getDirection(truck, i);
      for (int k = 0; k < length; k++) {
        if (truck->xLoc + TRUCK_SHAPE[k].x * dir == x &&
            truck->yLoc + TRUCK_SHAPE[k].y == y &&
            truck->zLoc + TRUCK_SHAPE[k].z == z)
          return truck;
      }

      length = sizeof(TRUCK_TIRES) / sizeof(TRUCK_TIRES[0]);
      for (int k = 0; k < length; k++) {
        if (truck->xLoc + TRUCK_TIRES[k].x * dir == x &&
            truck->yLoc + TRUCK_TIRES[k].y == y &&
            truck->zLoc + TRUCK_TIRES[k].z == z)
          return truck;
      }
    }
  }
  return NULL;
}

void drawTruck(Truck *truck) {
  int length = sizeof(TRUCK_SHAPE) / sizeof(TRUCK_SHAPE[0]);
  int dir = getDirection(truck, truck->team);
  truck->yLoc = getGroundHeight(truck, dir);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_SHAPE[i].x * dir][truck->yLoc + TRUCK_SHAPE[i].y]
         [truck->zLoc + TRUCK_SHAPE[i].z] = VEHICLE_1 + truck->team;
  }

  length = sizeof(TRUCK_TIRES) / sizeof(TRUCK_TIRES[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_TIRES[i].x * dir][truck->yLoc + TRUCK_TIRES[i].y]
         [truck->zLoc + TRUCK_TIRES[i].z] = TIRES;
  }
  if (truck->hasMeteor) {
    world[truck->xLoc - dir][truck->yLoc + 1][truck->zLoc] = IDENTIFIED_METEOR;
  }
}

void teleportToBase(Truck *truck) {
  truck->hasMeteor = 0;
  truck->health = 2;

  clearTruck(truck);

  // create a crater where the truck was
  for (int y = 0; y < 2; y++) {
    int radius = 4 - y; // shrink the circle
    for (int z = -radius; z < radius; z++) {
      // calculate the length of current line by the distance from the centre
      int half_row_width = sqrt(radius * radius - z * z);
      for (int x = -half_row_width; x < half_row_width; x++) {
        world[truck->xLoc - 2 + y + radius + x][truck->yLoc - y]
             [truck->zLoc - 2 + y + radius + z] = 0;
      }
    }
  }

  Base *base = (Base *)newWorld->teams[truck->team]->base;
  truck->xLoc = base->xLoc + (truck->team == TEAM_ONE ? -10 : 10);
  truck->yLoc = 0;
  truck->zLoc = base->zLoc + TRUCK_ADJUST[2];
  truck->state = searching;
}

void clearTruck(Truck *truck) {

  int length = sizeof(TRUCK_SHAPE) / sizeof(TRUCK_SHAPE[0]);
  int dir = getDirection(truck, truck->team);

  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_SHAPE[i].x * dir][truck->yLoc + TRUCK_SHAPE[i].y]
         [truck->zLoc + TRUCK_SHAPE[i].z] = 0;
  }

  length = sizeof(TRUCK_TIRES) / sizeof(TRUCK_TIRES[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_TIRES[i].x * dir][truck->yLoc + TRUCK_TIRES[i].y]
         [truck->zLoc + TRUCK_TIRES[i].z] = 0;
  }
  if (truck->hasMeteor) {
    world[truck->xLoc - dir][truck->yLoc + 1][truck->zLoc] = 0;
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

  if (world[truck->searchX][truck->searchY][truck->searchZ] == 0) {
    newSearchArea(truck);
    truck->state = searching;
    return 0;
  }

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
    // if (searchArea(truck))
    //   truck->state = moving;
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
      // team->meteorCount++;
      newSearchArea(truck);
      truck->state = searching;
    };
    break;
  }
  }
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

Coord TRUCK_SHAPE[5] = {
    {-1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {-1, 1, 0}, {0, 1, 0}};
Coord TRUCK_TIRES[4] = {{-1, 0, -1}, {-1, 0, 1}, {1, 0, -1}, {1, 0, 1}};

int direction[4][3] = {{1, 1, 1}, {-1, 1, 1}, {1, 1, -1}, {1, 1, -1}};

/*** newSearchArea() ***/
/* - Randomly select a new location for the truck to move to */
void newSearchArea(Truck *truck) {
  truck->searchX = rand() % (WORLDX - 20) + 10;
  truck->searchZ = rand() % (WORLDZ - 20) + 10;
}

/*** createTruck() ***/
/* - Allocate space and fill values for the truck object */
Truck *createTruck(Base *base, int teamNumber) {
  Truck *newTruck = (Truck *)malloc(sizeof(Truck));
  if (newTruck == NULL)
    printf("Unable to allocate space for truck");

  newTruck->xLoc = base->xLoc + (teamNumber == TEAM_ONE ? -10 : 10);
  newTruck->yLoc = 0;
  newTruck->zLoc = base->zLoc;
  newTruck->state = searching;
  newTruck->hasMeteor = 0;
  newTruck->loadCount = 0;
  newTruck->health = 2;
  newTruck->lastTimeMoved = 0;
  newSearchArea(newTruck);
  newTruck->team = teamNumber;
  newTruck->next = NULL;

  return newTruck;
}

void addTruck(int teamNumber) {
  Team *team = newWorld->teams[teamNumber];
  Truck *currTruck = team->trucks;
  while (currTruck->next != NULL) {
    currTruck = currTruck->next;
  }
  currTruck->next = createTruck(team->base, teamNumber);
  team->truckCount++;
}

/*** getDirection() ***/
/* - uses the truck state to determin which way the truck is facing */
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

/*** getGroundHeight ***/
/* -checks each square a piece of the truck will be rendered in and returns the
highest space avaliable to allow the whole truck to spawn without clipping with
the world */
int getGroundHeight(Truck *truck, int dir) {
  int heighestY = 0;

  // Iterate over the truck body
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

  // Iterate over the truck tires
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

/*** drawTruck() ***/
/* - Render the truck at its current x and z location */
/* - Pick a y location that puts it ontop of the world to account for hills and
 * valleys */
/* - uses two offset arrays to build the truck based on 1 (x,z) location */
void drawTruck(Truck *truck) {
  int dir = getDirection(truck, truck->team);
  truck->yLoc = getGroundHeight(truck, dir);

  // Build the truck Body
  int length = sizeof(TRUCK_SHAPE) / sizeof(TRUCK_SHAPE[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_SHAPE[i].x * dir][truck->yLoc + TRUCK_SHAPE[i].y]
         [truck->zLoc + TRUCK_SHAPE[i].z] = VEHICLE_1 + truck->team;
  }

  // Build the truck tires
  length = sizeof(TRUCK_TIRES) / sizeof(TRUCK_TIRES[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_TIRES[i].x * dir][truck->yLoc + TRUCK_TIRES[i].y]
         [truck->zLoc + TRUCK_TIRES[i].z] = TIRES;
  }

  if (truck->hasMeteor) {
    world[truck->xLoc - dir][truck->yLoc + 1][truck->zLoc] = IDENTIFIED_METEOR;
  }
}

/*** clearTruck() ***/
/* - when the truck moves, remove the old truck from the world array */
void clearTruck(Truck *truck) {

  int dir = getDirection(truck, truck->team);
  // clear the truck body
  int length = sizeof(TRUCK_SHAPE) / sizeof(TRUCK_SHAPE[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_SHAPE[i].x * dir][truck->yLoc + TRUCK_SHAPE[i].y]
         [truck->zLoc + TRUCK_SHAPE[i].z] = 0;
  }

  // clear the truck tires
  length = sizeof(TRUCK_TIRES) / sizeof(TRUCK_TIRES[0]);
  for (int i = 0; i < length; i++) {
    world[truck->xLoc + TRUCK_TIRES[i].x * dir][truck->yLoc + TRUCK_TIRES[i].y]
         [truck->zLoc + TRUCK_TIRES[i].z] = 0;
  }

  if (truck->hasMeteor) {
    world[truck->xLoc - dir][truck->yLoc + 1][truck->zLoc] = 0;
  }
}

/*** truckLookup() ***/
/* - used for when a projectile hits a truck */
/* - input with the world location that was hit */
/* - check if the inputted location matches anyx that would be a part of a truck
on an enemy team */
/* - return the truck if anything mathes, null on error/not found */
Truck *truckLookup(int x, int y, int z) {
  for (int i = 0; i < TEAM_COUNT; i++) {
    Team *team = newWorld->teams[i];
    Truck *truck = team->trucks;
    while (truck != NULL) {
      int dir = getDirection(truck, i);

      // check the truck body
      int length = sizeof(TRUCK_SHAPE) / sizeof(TRUCK_SHAPE[0]);
      for (int k = 0; k < length; k++) {
        if (truck->xLoc + TRUCK_SHAPE[k].x * dir == x &&
            truck->yLoc + TRUCK_SHAPE[k].y == y &&
            truck->zLoc + TRUCK_SHAPE[k].z == z)
          return truck;
      }

      // check the truck tires
      length = sizeof(TRUCK_TIRES) / sizeof(TRUCK_TIRES[0]);
      for (int k = 0; k < length; k++) {
        if (truck->xLoc + TRUCK_TIRES[k].x * dir == x &&
            truck->yLoc + TRUCK_TIRES[k].y == y &&
            truck->zLoc + TRUCK_TIRES[k].z == z)
          return truck;
      }
      truck = truck->next;
    }
  }
  return NULL;
}

/*** teleportToBase() ***/
/* - used when the truck is hit and killed */
/* - moves the truck back to its spawn location and resets stats */
/* - leaves an "explosion crater" where the truck was killed */
void teleportToBase(Truck *truck) {
  truck->hasMeteor = 0;
  truck->health = 2;

  clearTruck(truck);

  // create a crater where the truck was
  for (int y = 0; y < 2; y++) {
    int radius = TRUCK_EXPLOSION_RADIUS - y; // shrink the circle
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
  truck->zLoc = base->zLoc;
  truck->state = searching;
  newSearchArea(truck);
}

/*** searchArea() ***/
/* - represents a cylinder of 3 height and 10 radius */
/* - if a meteor is identified within this area, move to state moving towards
 * meteor */
int searchArea(Truck *truck) {

  for (int y = truck->yLoc - 1; y < truck->yLoc + 1; y++) {
    for (int z = -TRUCK_SEARCH_RADIUS; z < TRUCK_SEARCH_RADIUS; z++) {
      int half_row_width =
          sqrt(TRUCK_SEARCH_RADIUS * TRUCK_SEARCH_RADIUS - z * z);
      for (int x = -half_row_width; x < half_row_width; x++) {
        if (withinBounds(truck->xLoc + x, y, truck->zLoc + z))
          if (world[truck->xLoc + x][y][truck->zLoc + z] == 26) {
            truck->searchX = truck->xLoc + x;
            truck->searchZ = truck->zLoc + z;
            truck->searchY = y;
            world[truck->xLoc + x][y][truck->zLoc + z] = 29;
            return TRUE;
          }
      }
    }
  }
  return FALSE;
}

/*** moveHome() ***/
/* - Represents truck state: Searching for meteor*/
/* - determine the direction of and move towards the search location */
/* - once reached, pick a new location to search if not interuppted */
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

/*** moveHome() ***/
/* - Represents truck state: Moving towards meteor*/
/* - Determine which way the identified meteor is and move */
/* - once reached the meteor, move to state loading */
/* - if the meteor is taken before arriving, move to state searching */
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

  // if another truck takes the meteor before getting there
  if (world[truck->searchX][truck->searchY][truck->searchZ] == 0) {
    newSearchArea(truck);
    truck->state = searching;
    return TRUE;
  }

  // Arrived at meteor
  if (truck->zLoc - truck->searchZ == 0 && truck->xLoc - truck->searchX == 0) {
    return TRUE;
  }
  return FALSE;
}

/*** moveHome() ***/
/* - Represents truck state: Returning to base */
/* - use the provided base to decide which direction to move in */
/* - once reached home, "unload" the meteor and move to state searching */
int moveHome(Truck *truck, Base *home) {
  if (truck->xLoc - home->xLoc < 0)
    truck->xLoc += 1;
  else if (truck->xLoc - home->xLoc > 0)
    truck->xLoc -= 1;

  if (truck->zLoc - home->zLoc < 0)
    truck->zLoc += 1;
  else if (truck->zLoc - home->zLoc > 0)
    truck->zLoc -= 1;

  // unloading
  if (truck->zLoc - home->zLoc == 0 && truck->xLoc - home->xLoc == 0) {
    truck->hasMeteor = 0;
    newSearchArea(truck);
    return TRUE;
  }
  return FALSE;
}

/*** moveTruck() ***/
/* - parent function to decide, based on the truck state machine, how the truck
 * is going to move */
/* - Possible states are:
       seaching for meteor,
       moving towards meteor,
       loading meteor,
       returning to base */
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

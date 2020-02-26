#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generation.h"
#include "graphics.h"
#include "hill.h"
#include "meteor.h"
#include "valley.h"

int x, y, z, idx, jdx;
int hillCount, valleyCount;
int cloudHeight = WORLDY - 3;

Coord flatPlusSign[4] = {{-1, 0, 0}, {1, 0, 0}, {0, 0, -1}, {0, 0, 1}};

/******* initWorld() *******/
/* - initialize world array to empty */
void initWorld() {

  for (x = 0; x < WORLDX; x++)
    for (y = 0; y < WORLDY; y++)
      for (z = 0; z < WORLDZ; z++)
        world[x][y][z] = 0;
}

/******* convertColour() *******/
/* TODO: Write the helper function */
void setColourAmbDif(int colourCode, int r, int g, int b) {
  double aRed = roundf(((double)r / (double)256) * 1000) / 1000;
  double aGreen = roundf(((double)g / (double)256) * 1000) / 1000;
  double aBlue = roundf(((double)b / (double)256) * 1000) / 1000;
  double dRed = roundf(((double)r / (double)512) * 1000) / 1000;
  double dGreen = roundf(((double)g / (double)512) * 1000) / 1000;
  double dBlue = roundf(((double)b / (double)512) * 1000) / 1000;
  setUserColour(colourCode, aRed, aGreen, aBlue, 1.0, dRed, dGreen, dBlue, 1.0);
}

/******* setColours() *******/
/* - register predefind user colours with the game engine */
void setColours() {
  // Grass Greens
  setColourAmbDif(9, 19, 136, 52);
  setColourAmbDif(10, 19, 110, 52);
  setColourAmbDif(11, 19, 162, 52);
  setColourAmbDif(12, 19, 187, 52);
  setColourAmbDif(13, 19, 85, 52);
  // Dirt Brown
  setColourAmbDif(14, 68, 60, 10);
  setColourAmbDif(15, 123, 91, 24);
  setColourAmbDif(16, 102, 67, 15);
  setColourAmbDif(17, 80, 66, 12);
  setColourAmbDif(18, 125, 99, 15);
  // Base Grey
  setColourAmbDif(19, 89, 94, 94);
  // cloud grey
  setColourAmbDif(20, 244, 244, 244);
  setColourAmbDif(21, 250, 250, 250);
  setColourAmbDif(22, 237, 237, 237);
  // fire reds
  setColourAmbDif(23, 206, 22, 32);
  setColourAmbDif(24, 226, 88, 34);
  setColourAmbDif(25, 255, 222, 173);
  // meteorite black
  setColourAmbDif(26, 48, 25, 52);
}

/******* makeFloor() *******/
/* - fill the bottom 4 rows with *dirtColor* */
/* - fill the 5th rows with *grassColor* */
/* - *dirtColor* and *grassColor* are random between 5 colour options */
void makeFloor() {
  for (x = 0; x < WORLDX; x++) {
    for (z = 0; z < WORLDZ; z++) {
      int grassColor = rand() % 12 + 2;
      for (y = 0; y < 4; y++) {
        int dirtColor = rand() % 12 + 6;
        world[x][y][z] = dirtColor < 14 ? 14 : dirtColor;
      }
      world[x][4][z] = grassColor < 9 ? 9 : grassColor;
    }
  }
}

/******* identifyRect() *******/
/* - input a Unknown object */
/* - derive the identity of the object with the id */
/* - retreive the collision rectangle around that object */
Rect *identifyRect(Object *obj) {
  Rect *rect;
  switch (obj->id) {
  case hillId: {
    Hill *hill = obj->structure;
    rect = hill->getSurrounding(hill);
    break;
  }
  case valleyId: {
    Valley *valley = obj->structure;
    rect = valley->getSurrounding(valley);
    break;
  }
  case baseId: {
    Base *base = obj->structure;
    rect = base->getSurrounding(base);
    break;
  }
  default:
    printf("Bad id during rectangle retrieval\n");
    exit(1);
  }
  return rect;
}

/******* doesOverlap() *******/
/* - input two objects */
/* - determine if the collision rectanlges of either opbject overlap */
int doesOverlap(Object *objectA, Object *objectB) {
  Rect *rectA = identifyRect(objectA);
  Rect *rectB = identifyRect(objectB);
  int overlap = 1;

  // Simpler to check if the object are not overlapping
  if (rectA->x > rectB->hx || rectB->x > rectA->hx)
    overlap = 0;
  if (rectA->z > rectB->hz || rectB->z > rectA->hz)
    overlap = 0;

  free(rectA);
  free(rectB);
  return overlap;
}

/******* checkOverlap() *******/
/* - input an object, and its index */
/* - compare the object to all others in the world array */
/* - attempt to relocate the object if it is found to be overlapping. */
/* Only attempt RELOCATE_CHANCE times, then remove the object */
void checkOverlap(Object *objectA, int idx) {
  for (jdx = 0; jdx < valleyCount + hillCount + BASE_COUNT; jdx++) {
    Object *objectB = newWorld->objects[jdx];
    // Skip over the object itself
    // any objects that have be removed,
    // or non objects
    if (jdx == idx)
      continue;
    if (objectB->render == 0)
      continue;
    if (objectB->id == invaldId)
      break;

    if (doesOverlap(objectA, objectB)) {
      if (objectA->moveCount < RELOCATE_CHANCE) {
        switch (objectA->id) {
        case hillId: {
          Hill *hill = objectA->structure;
          hill->changeLocation(hill);
          break;
        }
        case valleyId: {
          Valley *valley = objectA->structure;
          valley->changeLocation(valley);
          break;
        }
        default:
          break;
        }
        objectA->moveCount += 1;
        checkOverlap(objectA, idx);
        break;
      } else {
        objectA->render = 0;
      }
    }
  }
}

/******* fixOverlap() *******/
/* - check all objects for overlaps */
/* - try to replace objects that do */
void fixOverlap() {
  // Skip over the bases which shouldn't move
  for (idx = BASE_COUNT; idx < valleyCount + hillCount + BASE_COUNT; idx++) {
    if (newWorld->objects[idx]->render == 0)
      continue;
    if (newWorld->objects[idx]->id == invaldId)
      break;
    checkOverlap(newWorld->objects[idx], idx);
  }
}

/******* growCloud() *******/
/* - input a cloud location, remaining clouds, and the growth_rate */
/* - use the growth_rate to add onto that cloud in all 4 directions  */
/* - recursively move outward to grow the newly added clouds */
void growCloud(int xLoc, int zLoc, int *totalCloudsPtr, int growth_rate) {
  int newX, newZ;
  for (idx = 0; idx < 4; idx++) {
    if (*totalCloudsPtr < 0)
      return;
    newX = xLoc + flatPlusSign[idx].x;
    newZ = zLoc + flatPlusSign[idx].z;
    if (withinBounds(newX, cloudHeight, newZ) &&
        world[newX][cloudHeight][newZ] == 0) {
      if ((rand() % GROWTH_CHANCE) < growth_rate) {
        newWorld->clouds[*totalCloudsPtr] = createCloud(newX, newZ);
        *totalCloudsPtr = *totalCloudsPtr - 1;
        // lower the growth rate to stop growth eventually
        growCloud(newX, newZ, totalCloudsPtr, growth_rate - 10);
      }
    }
  }
}

/******* makeClouds() *******/
/* - create 9 clouds in a 3x3 pattern in a random location */
/* - start the cloud growth in a random direction */
void makeClouds() {
  int totalClouds = MAX_CLOUD_COUNT - 1;
  int *totalCloudsPtr = &totalClouds;
  while (*totalCloudsPtr >= 0) {
    int xLoc = rand() % (WORLDX - 2) + 1;
    int zLoc = rand() % (WORLDZ - 2) + 1;
    // make sure there is no cloud there already
    if (world[xLoc][WORLDY - 3][zLoc] == 0) {
      for (x = xLoc - 1; x < xLoc + 2; x++) {
        for (z = zLoc - 1; z < zLoc + 2; z++) {
          // make sure the cloud is still in the map
          if (withinBounds(x, cloudHeight, z)) {
            newWorld->clouds[*totalCloudsPtr] = createCloud(x, z);
            *totalCloudsPtr = *totalCloudsPtr - 1;
            if (*totalCloudsPtr < 0)
              return;
          }
        }
      }
      // Pick a random direction to start growing in
      switch (rand() % 4) {
      case 0:
        growCloud(xLoc - 1, zLoc, totalCloudsPtr, 70);
        break;
      case 1:
        growCloud(xLoc, zLoc - 1, totalCloudsPtr, 70);
        break;
      case 2:
        growCloud(xLoc, zLoc + 1, totalCloudsPtr, 70);
        break;
      case 3:
        growCloud(xLoc + 1, zLoc, totalCloudsPtr, 70);
        break;
      }
    }
  }
}

/******* makeMeteors() *******/
void makeMeteors() {
  newWorld->meteors = NULL;
  for (idx = 0; idx < 30; idx++) {
    addMeteor(createMeteor(idx + 1));
  }
}

void addMeteor(Meteor *newMeteor) {
  Meteor *meteor = newWorld->meteors;
  // If the meteor list is empty
  if (meteor == NULL) {
    newWorld->meteors = newMeteor;
    return;
  }
  while (meteor->next != NULL) {
    meteor = meteor->next;
  }
  meteor->next = newMeteor;
  newMeteor->prev = meteor;
}

Meteor *removeMeteor(Meteor *meteor) {
  if (meteor == NULL)
    return NULL;
  Meteor *next = meteor->next;
  Meteor *prev = meteor->prev;

  // if this is the only item in the list
  if (next == NULL && prev == NULL) {
    free(meteor);
    newWorld->meteors = NULL;
    return NULL;
  }
  // if this is the last item in the list
  if (next == NULL) {
    prev->next = NULL;
    free(meteor);
    return NULL;
  }
  // if this is the first item in the list
  if (prev == NULL) {
    next->prev = NULL;
    newWorld->meteors = next;
    free(meteor);
    return next;
  }
  prev->next = next;
  next->prev = prev;
  free(meteor);
  return next;
}

/******* makeBases() *******/
/* - Generate two base objects */
/* - fill with random values */
void makeBases() {

  for (idx = 0; idx < 2; idx++) {
    // Create space for and fill a base object
    Base *newBase = (Base *)malloc(sizeof(Base));
    createBase(newBase, idx);

    newWorld->objects[idx]->id = baseId;
    newWorld->objects[idx]->render = 1;
    newWorld->objects[idx]->moveCount = 0;
    newWorld->objects[idx]->structure = newBase;
  }
}

/******* makeValleys() *******/
/* - Generate valleyCount number of valley objects */
/* - fill with random values */
void makeValleys() {
  // offset the start to account for the objects already created
  for (idx = BASE_COUNT; idx < valleyCount + BASE_COUNT; idx++) {

    // load into the world object array
    newWorld->objects[idx]->id = valleyId;
    newWorld->objects[idx]->render = 1;
    newWorld->objects[idx]->moveCount = 0;
    newWorld->objects[idx]->structure = createValley();
  }
}

/******* makeHills() *******/
/* - Generate hillCount number of hill objects */
/* - fill with random values */
void makeHills() {
  // offset the start to account for the objects already created
  for (idx = valleyCount + BASE_COUNT;
       idx < valleyCount + hillCount + BASE_COUNT; idx++) {

    // load a new hill into the world objects array
    newWorld->objects[idx]->id = hillId;
    newWorld->objects[idx]->render = 1;
    newWorld->objects[idx]->moveCount = 0;
    newWorld->objects[idx]->structure = createHill();
  }
}

/* the first part of this if statement builds a sample */
/* world which will be used for testing */
/* DO NOT remove this code. */
/* Put your code in the else statment below */
/* The testworld is only guaranteed to work with a world of
        with dimensions of 100,50,100. */
void genTestWorld() {
  int i, j, k;
  /* initialize world to empty */
  initWorld();

  /* some sample objects */
  /* build a red platform */
  for (i = 0; i < WORLDX; i++) {
    for (j = 0; j < WORLDZ; j++) {
      world[i][24][j] = 3;
    }
  }
  /* create some green and blue cubes */
  world[50][25][50] = 1;
  world[49][25][50] = 1;
  world[49][26][50] = 1;
  world[52][25][52] = 2;
  world[52][26][52] = 2;

  /* create user defined colour and draw cube */
  setUserColour(9, 0.7, 0.3, 0.7, 1.0, 0.3, 0.15, 0.3, 1.0);
  world[54][25][50] = 9;

  /* blue box shows xy bounds of the world */
  for (i = 0; i < WORLDX - 1; i++) {
    world[i][25][0] = 2;
    world[i][25][WORLDZ - 1] = 2;
  }
  for (i = 0; i < WORLDZ - 1; i++) {
    world[0][25][i] = 2;
    world[WORLDX - 1][25][i] = 2;
  }

  /* create two sample mobs */
  /* these are animated in the update() function */
  createMob(0, 50.0, 25.0, 52.0, 0.0);
  createMob(1, 50.0, 25.0, 52.0, 0.0);

  /* create sample player */
  createPlayer(0, 52.0, 27.0, 52.0, 0.0);
}

/******* drawStructures() *******/
/* - Iterate and render all of the world objects */
void drawStructures() {
  for (idx = 0; idx < valleyCount + hillCount + BASE_COUNT; idx++) {
    if (!newWorld->objects[idx]->render)
      continue;

    if (newWorld->objects[idx]->id == hillId) {
      drawHill((Hill *)newWorld->objects[idx]->structure);
    } else if (newWorld->objects[idx]->id == valleyId) {
      drawValley((Valley *)newWorld->objects[idx]->structure);
    } else if (newWorld->objects[idx]->id == baseId) {
      drawBase((Base *)newWorld->objects[idx]->structure);
    } else {
      printf(" Unknown ID, something went wrong\n");
    }
  }
}

/******* genWorld() *******/
/* - Fill the world object */
/* - Create user defined colours */
void genWorld() {
  srand((unsigned)time(NULL));

  initWorld();
  setColours();
  makeFloor();

  // Generate random structure counts
  valleyCount =
      rand() % (MAX_VALLEY_COUNT - MIN_VALLEY_COUNT) + MIN_VALLEY_COUNT;
  hillCount = rand() % (MAX_HILL_COUNT - MIN_HILL_COUNT) + MIN_HILL_COUNT;

  // Making space for the world and the objects in the world
  newWorld = (WorldData *)malloc(sizeof(WorldData));
  if (newWorld == NULL)
    printf("Unable to allocate space for the worldData");

  for (idx = 0; idx < valleyCount + hillCount + BASE_COUNT; idx++) {
    newWorld->objects[idx] = (Object *)malloc(sizeof(Object));
    if (newWorld->objects[idx] == NULL) {
      printf("Unable to allocate space for the world Objects %d", idx);
      exit(1);
    }
    newWorld->objects[idx]->id = invaldId;
  }

  // place player
  setViewPosition(-1, -10, -1);

  // Generate random values for structures
  makeBases();
  makeValleys();
  makeHills();
  makeClouds();
  makeMeteors();
  fixOverlap();

  drawStructures();
}
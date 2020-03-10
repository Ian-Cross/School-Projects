#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"
// #include "meteor.h"

int hillCount, valleyCount;

Coord flatPlusSign[4] = {{-1, 0, 0}, {1, 0, 0}, {0, 0, -1}, {0, 0, 1}};

/******* initWorld() *******/
/* - initialize world array to empty */
void initWorld() {

  for (int x = 0; x < WORLDX; x++)
    for (int y = 0; y < WORLDY; y++)
      for (int z = 0; z < WORLDZ; z++)
        world[x][y][z] = 0;
}

/******* convertColour() *******/
/* - a helper function to convert regular RGB (255) to percentages used by
 * setUserColour() */
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

  // setColourAmbDif(GRASS_1, 19, 136, 52);
  // setColourAmbDif(GRASS_2, 19, 110, 52);
  // setColourAmbDif(GRASS_3, 19, 162, 52);
  // setColourAmbDif(GRASS_4, 19, 187, 52);
  // setColourAmbDif(GRASS_5, 19, 122, 52);
  setColourAmbDif(GRASS_1, 53, 102, 33);
  setColourAmbDif(GRASS_2, 56, 95, 40);
  setColourAmbDif(GRASS_3, 58, 89, 46);
  setColourAmbDif(GRASS_4, 39, 70, 26);
  setColourAmbDif(GRASS_5, 77, 126, 58);
  // setColourAmbDif(DIRT_1, 68, 60, 10);
  // setColourAmbDif(DIRT_2, 123, 91, 24);
  // setColourAmbDif(DIRT_3, 102, 67, 15);
  // setColourAmbDif(DIRT_4, 80, 66, 12);
  // setColourAmbDif(DIRT_5, 125, 99, 15);
  setColourAmbDif(DIRT_1, 134, 88, 44);
  setColourAmbDif(DIRT_2, 125, 88, 53);
  setColourAmbDif(DIRT_3, 118, 88, 60);
  setColourAmbDif(DIRT_4, 94, 64, 36);
  setColourAmbDif(DIRT_5, 122, 88, 54);
  setColourAmbDif(OLD_BASE, 89, 94, 94);
  setColourAmbDif(CLOUD_1, 244, 244, 244);
  setColourAmbDif(CLOUD_2, 250, 250, 250);
  setColourAmbDif(CLOUD_3, 237, 237, 237);
  setColourAmbDif(FIRE_1, 206, 22, 32);
  setColourAmbDif(FIRE_2, 226, 88, 34);
  setColourAmbDif(FIRE_3, 255, 222, 173);
  setColourAmbDif(METEOR, 48, 25, 52);
  setColourAmbDif(BASE_1, 200, 50, 50);
  setColourAmbDif(BASE_2, 50, 50, 200);
  setColourAmbDif(IDENTIFIED_METEOR, 48, 25, 52);
  setColourAmbDif(VEHICLE_1, 200, 50, 50);
  setColourAmbDif(VEHICLE_2, 50, 50, 200);
  setColourAmbDif(TIRES, 50, 50, 50);
}

/******* makeFloor() *******/
/* - fill the bottom 4 rows with *dirtColor* */
/* - fill the 5th row with *grassColor* */
/* - *dirtColor* and *grassColor* are random between 5 colour options */
void makeFloor() {
  int grassColours[5] = {GRASS_1, GRASS_2, GRASS_3, GRASS_4, GRASS_5};
  int dirtColours[5] = {DIRT_1, DIRT_2, DIRT_3, DIRT_4, DIRT_5};

  for (int x = 0; x < WORLDX; x++) {
    for (int z = 0; z < WORLDZ; z++) {
      int grassColor = rand() % 5;
      for (int y = 0; y < 4; y++) {
        int dirtColor = rand() % 5;
        world[x][y][z] = dirtColours[dirtColor];
      }
      world[x][4][z] = grassColours[grassColor];
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
  int overlap = TRUE;

  // Simpler to check if the object are not overlapping
  if (rectA->x > rectB->hx || rectB->x > rectA->hx)
    overlap = FALSE;
  if (rectA->z > rectB->hz || rectB->z > rectA->hz)
    overlap = FALSE;

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
  for (int jdx = 0; jdx < valleyCount + hillCount + BASE_COUNT; jdx++) {
    Object *objectB = newWorld->objects[jdx];
    // Skip over the object itself
    // any objects that have be removed,
    // or non objects
    if (jdx == idx)
      continue;
    if (objectB->render == FALSE)
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
        objectA->render = FALSE;
      }
    }
  }
}

/******* fixOverlap() *******/
/* - check all objects for overlaps */
/* - try to replace objects that do */
void fixOverlap() {
  // Skip over the bases which shouldn't move
  for (int idx = BASE_COUNT; idx < BASE_COUNT + valleyCount + hillCount;
       idx++) {
    // skip it if it isn't going to be shown
    if (newWorld->objects[idx]->render == FALSE)
      continue;
    // stop once all objects are reached
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
  for (int idx = 0; idx < 4; idx++) {
    if (*totalCloudsPtr < 0)
      return;
    newX = xLoc + flatPlusSign[idx].x;
    newZ = zLoc + flatPlusSign[idx].z;
    if (withinBounds(newX, CLOUD_HEIGHT, newZ) &&
        world[newX][CLOUD_HEIGHT][newZ] == 0) {
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
      for (int x = xLoc - 1; x < xLoc + 2; x++) {
        for (int z = zLoc - 1; z < zLoc + 2; z++) {
          // make sure the cloud is still in the map
          if (withinBounds(x, CLOUD_HEIGHT, z)) {
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
  // initialize the meteor list with 30 to start
  newWorld->meteors = NULL;
  for (int idx = 0; idx < 30; idx++) {
    addMeteor(createMeteor());
  }
  Meteor *currMeteor = newWorld->meteors;
  while (currMeteor != NULL) {
    drawMeteor(currMeteor);
    currMeteor = currMeteor->next;
  }
}

/******* makeBases() *******/
/* - Generate base objects for the number of teams */
/* - fill with random values */
void makeBases() {
  for (int idx = 0; idx < TEAM_COUNT; idx++) {
    // Create space for and fill a base object
    newWorld->objects[idx]->id = baseId;
    newWorld->objects[idx]->render = TRUE;
    newWorld->objects[idx]->moveCount = 0;
    newWorld->objects[idx]->structure = createBase(idx);
    ;
  }
}

/******* makeValleys() *******/
/* - Generate valleyCount number of valley objects */
/* - fill with random values */
void makeValleys() {
  // offset the start to account for the objects already created
  for (int idx = BASE_COUNT; idx < valleyCount + BASE_COUNT; idx++) {
    // load into the world object array
    newWorld->objects[idx]->id = valleyId;
    newWorld->objects[idx]->render = TRUE;
    newWorld->objects[idx]->moveCount = 0;
    newWorld->objects[idx]->structure = createValley();
  }
}

/******* makeHills() *******/
/* - Generate hillCount number of hill objects */
/* - fill with random values */
void makeHills() {
  // offset the start to account for the objects already created
  for (int idx = valleyCount + BASE_COUNT;
       idx < valleyCount + hillCount + BASE_COUNT; idx++) {

    // load a new hill into the world objects array
    newWorld->objects[idx]->id = hillId;
    newWorld->objects[idx]->render = TRUE;
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
  for (int idx = 0; idx < BASE_COUNT + valleyCount + hillCount; idx++) {
    Object *currObject = newWorld->objects[idx];
    if (!currObject->render)
      continue;

    switch (currObject->id) {
    case hillId:
      drawHill((Hill *)currObject->structure);
      break;
    case valleyId:
      drawValley((Valley *)currObject->structure);
      break;
    case baseId:
      drawBase((Base *)currObject->structure);
      break;
    default:
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

  for (int idx = 0; idx < BASE_COUNT + valleyCount + hillCount; idx++) {
    newWorld->objects[idx] = (Object *)malloc(sizeof(Object));
    if (newWorld->objects[idx] == NULL) {
      printf("Unable to allocate space for the world Objects %d", idx);
      exit(1);
    }
    newWorld->objects[idx]->id = invaldId;
  }

  // place player
  setViewPosition(-25, -15, -25);

  // Generate random values for structures
  makeBases();
  makeValleys();
  makeHills();

  fixOverlap();

  makeClouds();
  makeMeteors();

  drawStructures();
}

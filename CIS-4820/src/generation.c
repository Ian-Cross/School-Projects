#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/generation.h"
#include "../include/graphics.h"
#include "../include/worldObjects/hill.h"
#include "../include/worldObjects/valley.h"

int x, y, z, idx, jdx;
int hillCount, valleyCount;
int cloudHeight = WORLDY - 3;

typedef struct Coords {
  int x;
  int y;
  int z;
} Coord;

Coord flatPlusSign[4] = {{-1, 0, 0}, {1, 0, 0}, {0, 0, -1}, {0, 0, 1}};

void initWorld() {
  /* initialize world to empty */
  for (x = 0; x < WORLDX; x++)
    for (y = 0; y < WORLDY; y++)
      for (z = 0; z < WORLDZ; z++)
        world[x][y][z] = 0;
}

void setColours() {
  // Grass Greens
  setUserColour(9, 0.074, 0.529, 0.203, 1.0, 0.037, 0.264, 0.101, 1.0);
  setUserColour(10, 0.074, 0.429, 0.203, 1.0, 0.037, 0.264, 0.101, 1.0);
  setUserColour(11, 0.074, 0.629, 0.203, 1.0, 0.037, 0.264, 0.101, 1.0);
  setUserColour(12, 0.074, 0.729, 0.203, 1.0, 0.037, 0.264, 0.101, 1.0);
  setUserColour(13, 0.074, 0.329, 0.203, 1.0, 0.037, 0.264, 0.101, 1.0);
  // Dirt Brown
  setUserColour(14, 0.262, 0.234, 0.039, 1.0, 0.131, 0.117, 0.02, 1.0);
  setUserColour(15, 0.477, 0.355, 0.094, 1.0, 0.238, 0.178, 0.047, 1.0);
  setUserColour(16, 0.398, 0.262, 0.059, 1.0, 0.199, 0.131, 0.029, 1.0);
  setUserColour(17, 0.309, 0.258, 0.047, 1.0, 0.154, 0.129, 0.023, 1.0);
  setUserColour(18, 0.488, 0.387, 0.059, 1.0, 0.244, 0.193, 0.029, 1.0);
  // Base Grey
  setUserColour(19, 0.344, 0.367, 0.367, 1.0, 0.172, 0.184, 0.184, 1.0);
  // cloud grey
  setUserColour(20, 0.95, 0.95, 0.95, 0.5, 0.95, 0.95, 0.95, 0.5);
  setUserColour(21, 0.975, 0.975, 0.975, 0.5, 0.975, 0.975, 0.975, 0.5);
  setUserColour(22, 0.925, 0.925, 0.925, 0.5, 0.925, 0.925, 0.925, 0.5);
}

/* Create a flat world 5 blocks deep, top level with "grass" and bottom with
 * "dirt" */
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

int doesOverlap(Valley valley1, Valley valley2) {
  if (valley1.xLoc > valley2.xLoc + 2 * valley2.radius ||
      valley2.xLoc > valley1.xLoc + 2 * valley1.radius)
    return 0;
  if (valley1.zLoc > valley2.zLoc + 2 * valley2.radius ||
      valley2.zLoc > valley1.zLoc + 2 * valley1.radius)
    return 0;
  return 1;
}

void fixOverlap(WorldData *worldData) {}

void growCloud(int xLoc, int zLoc, int *totalCloudsPtr, int growth_rate) {

  int newX, newZ;
  printf("Growing Cloud %d\n", *totalCloudsPtr);
  // for (idx = 0; idx < 4; idx++) {
  //   if (*totalCloudsPtr < 0)
  //     return;
  //   newX = xLoc + flatPlusSign[idx].x;
  //   newZ = zLoc + flatPlusSign[idx].z;
  //   if (withinBounds(newX, cloudHeight, newZ) &&
  //       world[newX][cloudHeight][newZ] == 0) {
  //     if ((rand() % GROWTH_CHANCE) < growth_rate) {
  //       newWorld->clouds[*totalCloudsPtr] = createCloud(newX, newZ);
  //       *totalCloudsPtr = *totalCloudsPtr - 1;
  //       growCloud(newX, newZ, totalCloudsPtr, growth_rate - 10);
  //     }
  //   }
  // }

  if (withinBounds(xLoc - 1, cloudHeight, zLoc) &&
      world[xLoc - 1][cloudHeight][zLoc] == 0) {
    if ((rand() % GROWTH_CHANCE) < growth_rate) {
      newWorld->clouds[*totalCloudsPtr] = createCloud(xLoc - 1, zLoc);
      *totalCloudsPtr = *totalCloudsPtr - 1;
      growCloud(xLoc + 1, zLoc, totalCloudsPtr, growth_rate - 10);
    }
  }

  if (withinBounds(xLoc + 1, cloudHeight, zLoc) &&
      world[xLoc + 1][cloudHeight][zLoc] == 0) {
    if ((rand() % GROWTH_CHANCE) < growth_rate) {
      newWorld->clouds[*totalCloudsPtr] = createCloud(xLoc + 1, zLoc);
      *totalCloudsPtr = *totalCloudsPtr - 1;
      growCloud(xLoc + 1, zLoc, totalCloudsPtr, growth_rate - 10);
    }
  }

  if (withinBounds(xLoc, cloudHeight, zLoc - 1) &&
      world[xLoc][cloudHeight][zLoc - 1] == 0) {
    if ((rand() % GROWTH_CHANCE) < growth_rate) {
      newWorld->clouds[*totalCloudsPtr] = createCloud(xLoc, zLoc - 1);
      *totalCloudsPtr = *totalCloudsPtr - 1;
      growCloud(xLoc, zLoc - 1, totalCloudsPtr, growth_rate - 10);
    }
  }

  if (withinBounds(xLoc, cloudHeight, zLoc + 1) &&
      world[xLoc][cloudHeight][zLoc + 1] == 0) {
    if ((rand() % GROWTH_CHANCE) < growth_rate) {
      newWorld->clouds[*totalCloudsPtr] = createCloud(xLoc, zLoc + 1);
      *totalCloudsPtr = *totalCloudsPtr - 1;
      growCloud(xLoc, zLoc + 1, totalCloudsPtr, growth_rate - 10);
    }
  }
}

void makeClouds() {
  int totalClouds = MAX_CLOUD_COUNT - 1;
  int *totalCloudsPtr = &totalClouds;
  while (*totalCloudsPtr >= 0) {
    int xLoc = rand() % (WORLDX - 2) + 1;
    int zLoc = rand() % (WORLDZ - 2) + 1;
    if (world[xLoc][WORLDY - 3][zLoc] == 0) {
      for (x = xLoc - 1; x < xLoc + 2; x++) {
        for (z = zLoc - 1; z < zLoc + 2; z++) {
          if (withinBounds(x, cloudHeight, z)) {
            newWorld->clouds[*totalCloudsPtr] = createCloud(x, z);
            *totalCloudsPtr = *totalCloudsPtr - 1;
            if (*totalCloudsPtr < 0)
              return;
          }
        }
      }
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

void makeBases() {
  Base *newBase1 = (Base *)malloc(sizeof(Base));
  Base *newBase2 = (Base *)malloc(sizeof(Base));
  createBase(newBase1, 0);
  createBase(newBase2, 1);

  newWorld->objects[0]->id = baseId;
  newWorld->objects[0]->structure = newBase1;
  newWorld->objects[1]->id = baseId;
  newWorld->objects[1]->structure = newBase2;
}

void makeValleys() {
  for (idx = BASE_COUNT; idx < valleyCount + BASE_COUNT; idx++) {

    // load into the world object array
    newWorld->objects[idx]->id = valleyId;
    newWorld->objects[idx]->structure = createValley();

    Valley *test = (Valley *)newWorld->objects[idx]->structure;
    printf("%d: Creating valey of size %d at %d,%d\n", idx, test->radius,
           test->xLoc, test->zLoc);
  }
}

void makeHills() {
  for (idx = valleyCount + BASE_COUNT;
       idx < valleyCount + hillCount + BASE_COUNT; idx++) {

    // load a new hill into the world objects array
    newWorld->objects[idx]->id = hillId;
    newWorld->objects[idx]->structure = createHill();
    ;

    Hill *test = (Hill *)newWorld->objects[idx]->structure;
    printf("%d: Creating hill of size %d at %d,%d\n", idx, test->radius,
           test->xLoc, test->zLoc);
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

void genWorld() {
  srand((unsigned)time(NULL));

  initWorld();
  setColours();
  makeFloor();

  valleyCount =
      rand() % (MAX_VALLEY_COUNT - MIN_VALLEY_COUNT) + MIN_VALLEY_COUNT;
  hillCount = rand() % (MAX_HILL_COUNT - MIN_HILL_COUNT) + MIN_HILL_COUNT;

  // Making space for the world and the objects in the world
  newWorld = (WorldData *)malloc(sizeof(WorldData));
  if (newWorld == NULL)
    printf("Unable to allocate space for the worldData");

  printf("%d\n", valleyCount + hillCount + BASE_COUNT);
  for (idx = 0; idx < valleyCount + hillCount + BASE_COUNT; idx++) {
    newWorld->objects[idx] = (Object *)malloc(sizeof(Object));
    if (newWorld->objects[idx] == NULL)
      printf("Unable to allocate space for the world Objects %d", idx);
  }

  makeBases();
  makeValleys();
  makeHills();
  makeClouds();

  setViewPosition(-1, -10, -1);

  // fixOverlap(newWorld);

  // Draw Structres
  for (idx = 0; idx < valleyCount + hillCount + BASE_COUNT; idx++) {
    printf("%d: Drawing", idx);
    if (newWorld->objects[idx]->id == hillId) {
      Hill *test = (Hill *)newWorld->objects[idx]->structure;
      printf(" hill of size %d at %d,%d -> ", test->radius, test->xLoc,
             test->zLoc);
      drawHill(test);
    } else if (newWorld->objects[idx]->id == valleyId) {
      Valley *test = (Valley *)newWorld->objects[idx]->structure;
      printf(" valley of size %d at %d,%d -> ", test->radius, test->xLoc,
             test->zLoc);
      drawValley(test);
    } else if (newWorld->objects[idx]->id == baseId) {
      Base *test = (Base *)newWorld->objects[idx]->structure;
      printf(" base of size %d,%d at %d,%d -> ", test->width, test->length,
             test->xLoc, test->zLoc);
      drawBase(test);
    } else {
      printf(" Unknown ID, something went wrong\n");
    }
  }
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "generation.h"
#include "graphics.h"

int x, y, z, idx;

/******* getSurroudingRect() *******/
/* - Input Base object, allocate memory for a rectangle object */
/* - Retrieve the collision object around Base object */
Rect *getSurroudingRect(Base *base) {
  Rect *newRect = malloc(sizeof(Rect));
  newRect->x = base->xLoc;
  newRect->z = base->zLoc;
  newRect->hx = base->xLoc + base->width;
  newRect->hz = base->zLoc + base->length;
  return newRect;
}

/******* createBase() *******/
/* - Input base object, and base id */
/* - randomize values and fill the object */
void createBase(Base *base, int baseNum) {
  // find a random location to place the base
  int xLoc = rand() % WORLDX * 0.2 + WORLDX * (baseNum == 0 ? 0.7 : 0.1);
  int zLoc = rand() % (WORLDZ - BASE_SIZE * 3) + BASE_SIZE * 1.5;

  // randomize base values
  base->width = BASE_SIZE;
  base->length = BASE_SIZE - 2;
  base->height = 5;
  base->xLoc = xLoc;
  base->zLoc = zLoc;
  base->getSurrounding = getSurroudingRect;
}

/******* drawBase() *******/
/* - Input base object  */
/* - Iterate over 3 dimensions to build the base block by block */
void drawBase(Base *base) {
  for (y = 0; y < base->height; y++)
    for (z = 0; z < base->length; z++)
      for (x = 0; x < base->width; x++)
        world[base->xLoc + x][5 + y][base->zLoc + z] = 19;
}

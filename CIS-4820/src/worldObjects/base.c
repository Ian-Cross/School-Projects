#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"

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
/* - Input base id */
/* - allocate memory for the base */
/* - randomize values and fill the object returning it */
Base *createBase(int baseNum) {
  Base *newBase = (Base *)malloc(sizeof(Base));
  // find a random location to place the base
  int xLoc = rand() % WORLDX * 0.2 + WORLDX * (baseNum == 0 ? 0.7 : 0.1);
  int zLoc = rand() % (WORLDZ - BASE_SIZE * 3) + BASE_SIZE * 1.5;

  // randomize base values
  newBase->width = BASE_SIZE;
  newBase->length = BASE_SIZE;
  newBase->height = 3;
  newBase->xLoc = xLoc;
  newBase->zLoc = zLoc;
  newBase->colour = BASE_1 + baseNum;
  newBase->getSurrounding = getSurroudingRect;
  return newBase;
}

/******* drawBase() *******/
/* - Input base object  */
/* - Iterate over 3 dimensions to build the base block by block */
void drawBase(Base *base) {
  for (int y = 0; y < base->height; y++)
    for (int z = 0; z < base->length; z++)
      for (int x = 0; x < base->width; x++)
        world[base->xLoc + x][5 + y][base->zLoc + z] = base->colour;
}

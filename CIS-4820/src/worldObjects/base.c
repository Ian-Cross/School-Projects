#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "generation.h"
#include "graphics.h"

int x, y, z, idx;

Rect *getSurroudingRect(Base *base) {
  Rect *newRect = malloc(sizeof(Rect));
  newRect->x = base->xLoc;
  newRect->z = base->zLoc;
  newRect->hx = base->xLoc + base->width;
  newRect->hz = base->zLoc + base->length;
  return newRect;
}

void createBase(Base *base, int baseNum) {
  int xLoc;
  if (baseNum == 0)
    xLoc = rand() % WORLDX * 0.2 + WORLDX * 0.7;
  if (baseNum == 1)
    xLoc = rand() % WORLDX * 0.2 + WORLDX * 0.1;
  int zLoc = rand() % (WORLDZ - BASE_SIZE * 3) + BASE_SIZE * 1.5;

  printf("%d\n", BASE_SIZE);
  base->width = BASE_SIZE;
  base->length = BASE_SIZE - 2;
  base->height = 5;
  base->xLoc = xLoc;
  base->zLoc = zLoc;
  base->getSurrounding = getSurroudingRect;
}

void drawBase(Base *base) {
  printf("Rendering base of size %dx%d at %d,%d\n", base->width, base->length,
         base->xLoc, base->zLoc);

  for (y = 0; y < base->height; y++) {
    for (z = 0; z < base->length; z++) {
      for (x = 0; x < base->width; x++) {
        world[base->xLoc + x][5 + y][base->zLoc + z] = 19;
      }
    }
  }
}

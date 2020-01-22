#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generation.h"
#include "graphics.h"
#include "valley.h"

int x, y, z, idx;

Rect *getValleyRect(Valley *valley) {
  Rect *newRect = malloc(sizeof(Rect));
  newRect->x = valley->xLoc;
  newRect->z = valley->zLoc;
  newRect->hx = valley->xLoc + 2 * valley->radius;
  newRect->hz = valley->zLoc + 2 * valley->radius;
  return newRect;
}

void moveValley(Valley *valley) {
  valley->xLoc = rand() % (WORLDX - valley->radius * 2 - 2);
  valley->zLoc = rand() % (WORLDZ - valley->radius * 2 - 2);
}

Valley *createValley() {
  // Create space for the new valley
  Valley *newValley = (Valley *)malloc(sizeof(Valley));
  if (newValley == NULL) {
    printf("Unable to allocate memory for a valley");
    exit(1);
  }
  newValley->radius = (rand() % VALLEY_SIZE / 2) + VALLEY_SIZE;
  newValley->xLoc = rand() % (WORLDX - newValley->radius * 2 - 2);
  newValley->zLoc = rand() % (WORLDZ - newValley->radius * 2 - 2);
  newValley->depth = rand() % 2 + 2;
  newValley->getSurrounding = getValleyRect;
  newValley->changeLocation = moveValley;
  return newValley;
}

void drawValley(Valley *valley) {
  printf("Rendering valley of size %d at %d,%d\n", valley->radius, valley->xLoc,
         valley->zLoc);
  for (y = 0; y < valley->depth; y++) {
    int radius = valley->radius - y;
    for (z = -radius; z < radius; z++) {
      int half_row_width = sqrt(radius * radius - z * z);
      for (x = -half_row_width; x < half_row_width; x++) {
        if ((z != 0 || x != half_row_width - 1) &&
            (z != 0 || x != -half_row_width)) {
          world[valley->xLoc + y + radius + x][4 - y]
               [valley->zLoc + y + radius + z] = 0;
        }
      }
    }
  }
}

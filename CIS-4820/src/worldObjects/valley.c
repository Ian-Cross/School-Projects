#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/generation.h"
#include "../../include/graphics.h"
#include "../../include/worldObjects/valley.h"

int x, y, z, idx;

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
  newValley->render = 1;
  return newValley;
}

void drawValley(Valley *valley) {
  printf("Rendering valley of size %d at %d,%d\n", valley->radius, valley->xLoc,
         valley->zLoc);
  if (!valley->render)
    return;
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

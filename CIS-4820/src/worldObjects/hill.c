#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/generation.h"
#include "../../include/graphics.h"
#include "../../include/worldObjects/hill.h"

int x, y, z, idx;

Hill *createHill() {
  // Create space for the new hill
  Hill *newHill = (Hill *)malloc(sizeof(Hill));
  if (newHill == NULL) {
    printf("Unable to allocate memory for a hill");
    exit(1);
  }
  // fill the new hill with random values
  newHill->radius = (rand() % HILL_SIZE / 2) + HILL_SIZE;
  newHill->xLoc = rand() % (WORLDX - newHill->radius * 2 - 2);
  newHill->zLoc = rand() % (WORLDZ - newHill->radius * 2 - 2);
  newHill->height = rand() % 2 + 2;
  newHill->render = 1;
  return newHill;
}

void drawHill(Hill *hill) {
  printf("Rendering hill of size %d at %d,%d\n", hill->radius, hill->xLoc,
         hill->zLoc);
  if (!hill->render)
    return;
  for (y = 0; y < hill->height; y++) {
    int radius = hill->radius - y;
    for (z = -radius; z < radius; z++) {
      int half_row_width = sqrt(radius * radius - z * z);
      for (x = -half_row_width; x < half_row_width; x++) {
        if ((z != 0 || x != half_row_width - 1) &&
            (z != 0 || x != -half_row_width)) {
          int grassColor = rand() % 12 + 2;
          world[hill->xLoc + y + radius + x][5 + y]
               [hill->zLoc + y + radius + z] = grassColor < 9 ? 9 : grassColor;
        }
      }
    }
  }
}

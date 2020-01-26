#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generation.h"
#include "graphics.h"
#include "hill.h"

int x, y, z, idx;

/******* getHillRect() *******/
/* - Input Hill object, allocate memory for a rectangle object */
/* - Retrieve the collision object around Hill object */
Rect *getHillRect(Hill *hill) {
  Rect *newRect = malloc(sizeof(Rect));
  newRect->x = hill->xLoc;
  newRect->z = hill->zLoc;
  newRect->hx = hill->xLoc + 2 * hill->radius;
  newRect->hz = hill->zLoc + 2 * hill->radius;
  return newRect;
}

/******* moveHill() *******/
/* - Input Hill object */
/* - Rerandomize the location of the object */
void moveHill(Hill *hill) {
  hill->xLoc = rand() % (WORLDX - hill->radius * 2 - 2);
  hill->zLoc = rand() % (WORLDZ - hill->radius * 2 - 2);
}

/******* createHill() *******/
/* - Allocate memory space for the Hill */
/* - Generate random location and sizes */
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
  newHill->getSurrounding = getHillRect;
  newHill->changeLocation = moveHill;
  return newHill;
}

/******* drawHill() *******/
/* - Input Hill object  */
/* - Builds the circles line by line */
/* - Dig into the world in shinking circles to build a Hill */
void drawHill(Hill *hill) {
  for (y = 0; y < hill->height; y++) {
    int radius = hill->radius - y; // shrink the circle
    for (z = -radius; z < radius; z++) {
      // calculate the length of current line by the distance from the centre
      int half_row_width = sqrt(radius * radius - z * z);
      for (x = -half_row_width; x < half_row_width; x++) {
        // keep from a 1 length line at the very edge
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

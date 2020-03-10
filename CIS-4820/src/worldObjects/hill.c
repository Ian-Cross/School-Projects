#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"

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
  int grassColours[5] = {GRASS_1, GRASS_2, GRASS_3, GRASS_4, GRASS_5};
  for (int y = 0; y < hill->height; y++) {
    int radius = hill->radius - y; // shrink the circle
    for (int z = -radius; z < radius; z++) {
      // calculate the length of current line by the distance from the centre
      int half_row_width = sqrt(radius * radius - z * z);
      for (int x = -half_row_width; x < half_row_width; x++) {
        // keep from a 1 length line at the very edge
        if ((z != 0 || x != half_row_width - 1) &&
            (z != 0 || x != -half_row_width)) {
          int grassColor = rand() % 5;
          world[hill->xLoc + y + radius + x][5 + y]
               [hill->zLoc + y + radius + z] = grassColours[grassColor];
        }
      }
    }
  }
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cloud.h"
#include "generation.h"
#include "graphics.h"

int x, y, z, idx;

/******* createCloud() *******/
/* - Allocate memory space for the cloud */
/* - Generate random location and render to screen */
Cloud *createCloud(int xLoc, int zLoc) {
  Cloud *newCloud = (Cloud *)malloc(sizeof(Cloud));
  if (newCloud == NULL) {
    printf("Unable to allocate memory for a cloud\n");
    exit(1);
  }
  newCloud->xLoc = xLoc;
  newCloud->yLoc = WORLDY - 3;
  newCloud->zLoc = zLoc;
  newCloud->colour = rand() % 3 + 20;
  drawCloud(newCloud);
  return (newCloud);
}

/******* moveCloud() *******/
/* - Inputs cloud object and moves by 1 in the x direction*/
/* - Wrap around if hits the edge of the world */
void moveCloud(Cloud *cloud) { cloud->xLoc = (cloud->xLoc + 1) % WORLDX; }

/******* drawCloud() *******/
/* - Inputs cloud object and renders to the world */
/* - Picks a random colour from a group of greys */
void drawCloud(Cloud *cloud) {
  world[cloud->xLoc][cloud->yLoc][cloud->zLoc] = cloud->colour;
}

/******* clearCloud() *******/
/* - Inputs cloud object and clears that spot in the world */
void clearCloud(Cloud *cloud) {
  world[cloud->xLoc][cloud->yLoc][cloud->zLoc] = 0;
}

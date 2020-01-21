#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/generation.h"
#include "../../include/graphics.h"
#include "../../include/worldObjects/cloud.h"

int x, y, z, idx;

Cloud *createCloud(int xLoc, int zLoc) {
  Cloud *newCloud = (Cloud *)malloc(sizeof(Cloud));
  if (newCloud == NULL) {
    printf("Unable to allocate memory for a cloud\n");
    exit(1);
  }
  newCloud->xLoc = xLoc;
  newCloud->yLoc = WORLDY - 3;
  newCloud->zLoc = zLoc;
  drawCloud(newCloud);
  return (newCloud);
}

void moveCloud(Cloud *cloud) { cloud->xLoc = (cloud->xLoc + 1) % 100; }

void drawCloud(Cloud *cloud) {
  // for (x = cloud->xLoc - 1; x < cloud->xLoc + 2; x++) {
  //   for (z = cloud->zLoc - 1; z < cloud->zLoc + 2; z++) {
  //     if (withinBounds(x, WORLDY - 3, z)) {
  //       if (x == cloud->xLoc && z == cloud->zLoc)
  //         world[x][cloud->yLoc][z] = 5;
  //       else
  //         world[x][cloud->yLoc][z] = rand() % 3 + 20;
  //     }
  //   }
  // }
  world[cloud->xLoc][cloud->yLoc][cloud->zLoc] = rand() % 3 + 20;
}
void clearCloud(Cloud *cloud) {
  // for (x = cloud->xLoc - 1; x < cloud->xLoc + 2; x++) {
  //   for (z = cloud->zLoc - 1; z < cloud->zLoc + 2; z++) {
  //     if (withinBounds(x, WORLDY - 3, z)) {
  //       world[x][cloud->yLoc][z] = 0;
  //     }
  //   }
  // }
  world[cloud->xLoc][cloud->yLoc][cloud->zLoc] = 0;
}

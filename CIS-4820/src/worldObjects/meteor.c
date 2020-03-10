#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"

int x, y, z, idx;
int groundBlocks[] = {
    GRASS_1, GRASS_2, GRASS_3, GRASS_4, GRASS_5,           DIRT_1, DIRT_2,
    DIRT_3,  DIRT_4,  DIRT_5,  METEOR,  IDENTIFIED_METEOR, BASE_1, BASE_2};

/******* hitGround *******/
/* - test against a specific set of blocks to see if the meteor has reached
 * GROUND_HEIGHT*/
int hitGround(int x, int y, int z) {
  size_t length = sizeof(groundBlocks) / sizeof(groundBlocks[0]);
  for (int i = 0; i < length; i++) {
    if (world[x][y][z] == groundBlocks[i])
      return TRUE;
  }
  return FALSE;
}

/******* moveMeteor() *******/
/* - Input Meteor object */
/* - add the metoros velocity vector onto its position to move it */
/* - Check if the meteor will hit something, stop its movement */
/*   and remove its tail if it will */
void moveMeteor(Meteor *meteor) {
  if (meteor->falling == 1) {
    int newXLoc = meteor->xLoc - meteor->xVel;
    int newYLoc = meteor->yLoc + meteor->yVel;
    int newZLoc = meteor->zLoc - meteor->zVel;

    if (withinBounds(newXLoc, newYLoc, newZLoc) &&
        hitGround(newXLoc, newYLoc, newZLoc)) {
      meteor->falling = 0;
      return;
    }
    meteor->xLoc = newXLoc;
    meteor->yLoc = newYLoc;
    meteor->zLoc = newZLoc;
  }
}

/******* createMeteor() *******/
/* - Allocate memory space for the Meteor */
/* - Generate random landing location */
/* - Generate random direction unit vector */
/* - calculate starting location from landing location and direction */
Meteor *createMeteor() {
  // Create space for the new meteor
  Meteor *newMeteor = (Meteor *)malloc(sizeof(Meteor));
  if (newMeteor == NULL) {
    printf("Unable to allocate memory for a meteor");
    exit(1);
  }
  // Generate a landing location
  newMeteor->xLoc = rand() % (WORLDX - 2) + 1;
  newMeteor->zLoc = rand() % (WORLDZ - 2) + 1;
  newMeteor->yLoc = 0;
  newMeteor->falling = 1;
  newMeteor->render = 1;
  for (int i = 0; i < 4; i++)
    newMeteor->oldColours[i] = 0;
  newMeteor->next = NULL;
  newMeteor->prev = NULL;

  // Pick the diagonal direction the metoer will fall from
  // make sure if it is landing right next to an edge, have
  // it come in from the middle so it is seen
  int xVel = 0, zVel = 0;
  newMeteor->yVel = -1;
  if (newMeteor->xLoc >= WORLDX - 20) {
    xVel = -1;
  } else if (newMeteor->xLoc <= 20) {
    xVel = 1;
  } else {
    xVel = (rand() % 2 == 1) ? -1 : 1;
  }
  if (newMeteor->zLoc >= WORLDZ - 20) {
    zVel = -1;
  } else if (newMeteor->zLoc <= 20) {
    zVel = 1;
  } else {
    zVel = (rand() % 2 == 1) ? -1 : 1;
  }

  newMeteor->xVel = xVel;
  newMeteor->zVel = zVel;

  // calculate starting location
  for (int i = 0; i < WORLDY - rand() % 5; i++) {
    newMeteor->xLoc += newMeteor->xVel;
    newMeteor->yLoc -= newMeteor->yVel;
    newMeteor->zLoc += newMeteor->zVel;
  }
  return newMeteor;
}

/*** saveColour ***/
/* - Used for the replacement of blocks as the metoer moves, */
/* - any block it passes through will be replaced, except itself */
int saveColour(int colour) {
  switch (colour) {
  case METEOR:
  case FIRE_1:
  case FIRE_2:
  case FIRE_3:
    return 0;
  default:
    return colour;
  }
}

/******* drawMeteor() *******/
/* - Input Meteor object  */
/* - Draw the meteor at its location, add on flame tail */
/* - Only draw the meteor or tail if it is within the world bounds */
void drawMeteor(Meteor *meteor) {
  // ensure the meteor is in the world bounds before drawing
  if (withinBounds(meteor->xLoc, meteor->yLoc, meteor->zLoc)) {

    meteor->oldColours[0] = world[meteor->xLoc][meteor->yLoc][meteor->zLoc];
    world[meteor->xLoc][meteor->yLoc][meteor->zLoc] = METEOR;
  }

  // Draw flame trails, ensure each new trail block is in the world bounds
  for (int i = 1; i <= 3; i++) {
    if (withinBounds(meteor->xLoc + i * meteor->xVel,
                     meteor->yLoc - i * meteor->yVel,
                     meteor->zLoc + i * meteor->zVel)) {
      meteor->oldColours[i] = world[meteor->xLoc + i * meteor->xVel]
                                   [meteor->yLoc - i * meteor->yVel]
                                   [meteor->zLoc + i * meteor->zVel];
      // meteor->oldColours[i] = FIRE_1 + i - 1;
      world[meteor->xLoc + i * meteor->xVel][meteor->yLoc - i * meteor->yVel]
           [meteor->zLoc + i * meteor->zVel] = FIRE_1 + i - 1;
    }
  }
}

/******* clearMeteor() *******/
/* - Input meteor object */
/* - Remove the meteor and tail from the world array */
/* - Ensure the meteor spot is within the world */
void clearMeteor(Meteor *meteor) {
  if (withinBounds(meteor->xLoc, meteor->yLoc, meteor->zLoc))
    world[meteor->xLoc][meteor->yLoc][meteor->zLoc] =
        saveColour(meteor->oldColours[0]);
  clearTail(meteor);
}

/******* clearTail() *******/
/* - Input meteor object */
/* - Remove the meteor's trailing flames from the world array */
/* - Ensure the tail spot is in the world bounds */
void clearTail(Meteor *meteor) {
  for (int i = 1; i <= 3; i++) {
    if (withinBounds(meteor->xLoc + i * meteor->xVel,
                     meteor->yLoc - i * meteor->yVel,
                     meteor->zLoc + i * meteor->zVel))
      world[meteor->xLoc + i * meteor->xVel][meteor->yLoc - i * meteor->yVel]
           [meteor->zLoc + i * meteor->zVel] =
               saveColour(meteor->oldColours[i]);
  }
}
/*** addMeteor() ***/
/* - Add the input meteor onto the list of meteors in the world object */
void addMeteor(Meteor *newMeteor) {
  Meteor *meteor = newWorld->meteors;
  // If the meteor list is empty
  if (meteor == NULL) {
    newWorld->meteors = newMeteor;
  } else {
    // otherwise move to the end of the list and add the meteor
    while (meteor->next != NULL) {
      meteor = meteor->next;
    }
    meteor->next = newMeteor;
    newMeteor->prev = meteor;
  }
}

/*** removeMeteor() ***/
/* - Remove the input meteor from its place in the list */
/* - adjust the list around it so no errors occur */
Meteor *removeMeteor(Meteor *meteor) {
  if (meteor == NULL)
    return NULL;
  Meteor *next = meteor->next;
  Meteor *prev = meteor->prev;

  // if this is the only item in the list besides the head
  if (next == NULL && prev == NULL) {
    free(meteor);
    newWorld->meteors = NULL;
    return NULL;
  }

  // if this is the last item in the list
  if (next == NULL) {
    free(meteor);
    prev->next = NULL;
    return NULL;
  }

  // if this is the first item in the list
  if (prev == NULL) {
    free(meteor);
    next->prev = NULL;
    newWorld->meteors = next;
    return next;
  }

  free(meteor);
  prev->next = next;
  next->prev = prev;
  return prev;
}

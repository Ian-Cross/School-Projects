#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graphics.h"

extern GLubyte world[WORLDX][WORLDY][WORLDZ];

/* the first part of this if statement builds a sample */
/* world which will be used for testing */
/* DO NOT remove this code. */
/* Put your code in the else statment below */
/* The testworld is only guaranteed to work with a world of
        with dimensions of 100,50,100. */
void genTestWorld() {
  int i, j, k;
  /* initialize world to empty */
  for (i = 0; i < WORLDX; i++)
    for (j = 0; j < WORLDY; j++)
      for (k = 0; k < WORLDZ; k++)
        world[i][j][k] = 0;

  /* some sample objects */
  /* build a red platform */
  for (i = 0; i < WORLDX; i++) {
    for (j = 0; j < WORLDZ; j++) {
      world[i][24][j] = 3;
    }
  }
  /* create some green and blue cubes */
  world[50][25][50] = 1;
  world[49][25][50] = 1;
  world[49][26][50] = 1;
  world[52][25][52] = 2;
  world[52][26][52] = 2;

  /* create user defined colour and draw cube */
  setUserColour(9, 0.7, 0.3, 0.7, 1.0, 0.3, 0.15, 0.3, 1.0);
  world[54][25][50] = 9;

  /* blue box shows xy bounds of the world */
  for (i = 0; i < WORLDX - 1; i++) {
    world[i][25][0] = 2;
    world[i][25][WORLDZ - 1] = 2;
  }
  for (i = 0; i < WORLDZ - 1; i++) {
    world[0][25][i] = 2;
    world[WORLDX - 1][25][i] = 2;
  }

  /* create two sample mobs */
  /* these are animated in the update() function */
  createMob(0, 50.0, 25.0, 52.0, 0.0);
  createMob(1, 50.0, 25.0, 52.0, 0.0);

  /* create sample player */
  createPlayer(0, 52.0, 27.0, 52.0, 0.0);
}

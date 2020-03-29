
/* Derived from scene.c in the The OpenGL Programming Guide */
/* Keyboard and mouse rotation taken from Swiftless Tutorials #23 Part 2 */
/* http://www.swiftless.com/tutorials/opengl/camera2.html */

/* Frames per second code taken from : */
/* http://www.lighthouse3d.com/opengl/glut/index.php?fps */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int paused = 0;

/*** withinBounds() ***/
/* - Checks to ensure the given location is inside the defined world array */
int withinBounds(float xLoc, float yLoc, float zLoc) {
  if (xLoc >= WORLDX || xLoc < 0)
    return FALSE;
  if (yLoc >= WORLDY || yLoc < 0)
    return FALSE;
  if (zLoc >= WORLDZ || zLoc < 0)
    return FALSE;
  return TRUE;
}

/******* doesCollide() *******/
/* - checks the identity of the provided block */
/* - returns true or false if that block is solid */
int doesCollide(int x, int y, int z) {
  if (world[x][y][z] != 0)
    return TRUE;
  return FALSE;
}

/*** collisionResponse() ***/
/* -performs collision detection and response */
/*  sets new xyz  to position of the viewpoint after collision */
/* -can also be used to implement gravity by updating y position of vp*/
/* note that the world coordinates returned from getViewPosition()
   will be the negative value of the array indices */
void collisionResponse() {
  float x, xx, y, yy, z, zz;
  // int collisionPoints = 16;
  int interpolationRounds = 1000;

  getViewPosition(&x, &y, &z);
  getOldViewPosition(&xx, &yy, &zz);

  // Keeps the viewpoint in the map, and below the clouds
  if (!withinBounds(-floor(x), -(floor(y) + 5), -floor(z)))
    setViewPosition(xx, yy, zz);

  // Iterate through the 26 points surrounding the viewpoint to draw a simulated
  // hitbox
  for (float j = -y - 0.15; j < -y + 0.3; j += 0.15) {
    for (float i = -x - 0.15; i < -x + 0.3; i += 0.15) {
      for (float k = -z - 0.15; k < -z + 0.3; k += 0.15) {
        if (doesCollide((int)i, (int)j, (int)k))
          setViewPosition(xx, yy, zz);
      }
    }
  }
  // printf("(%lf, %lf, %lf) => (%lf, %lf, %lf) \n", xx, yy, zz, x, y, z);
}

/*** drawMap() ***/
/* - Creates a 2d representation of the landscape, ignoreing the clouds */
/* - The size of the map depends on the parameters */
void drawMap(int startX, int startY, int width, int height, int cubeWidth,
             int cubeHeight) {
  GLfloat white[] = {1.0, 1.0, 1.0, 1};
  // Draw view point on map
  float x, y, z;
  getViewPosition(&x, &y, &z);
  set2Dcolour(white);
  int cubeStartX = startX + -x * cubeWidth;
  int cubeStartY = startY + -z * cubeWidth;
  draw2Dbox(cubeStartX, cubeStartY, cubeStartX + cubeWidth,
            cubeStartY + cubeWidth);

  // Draw a box to contain the map,
  GLfloat black[] = {0.0, 0.0, 0.0, 1};
  set2Dcolour(black);
  draw2Dline(startX, startY, startX + width, startY, 5);
  draw2Dline(startX, startY, startX, startY + height, 5);
  draw2Dline(startX + width, startY, startX + width, startY + height, 5);
  draw2Dline(startX, startY + height, startX + width, startY + height, 5);

  for (int i = 0; i < WORLDX; i++) {
    for (int j = 0; j < WORLDZ; j++) {
      for (int y = WORLDY - 4; y > 0; y--) {
        if (world[i][y][j] != 0 && world[i][y + 1][j] == 0) {
          getUserColour(world[i][y][j], &ambRed, &ambGreen, &ambBlue, &ambAlpha,
                        &difRed, &difGreen, &difBlue, &difAlpha);
          GLfloat colour[] = {ambRed, ambGreen, ambBlue, 1};
          set2Dcolour(colour);

          cubeStartX = startX + i * cubeWidth;
          cubeStartY = startY + width - (j + 1) * cubeWidth;
          draw2Dbox(cubeStartX, cubeStartY, cubeStartX + cubeWidth,
                    cubeStartY + cubeWidth);
        }
      }
    }
  }
}

/*** drawScore() ***/
/* - */
void drawScore(Team *team) {
  int cubeSide = 18;
  int score = team->meteorCount;
  int startX, startY;
  GLfloat white[] = {1, 1, 1, 1};
  getUserColour(METEOR, &ambRed, &ambGreen, &ambBlue, &ambAlpha, &difRed,
                &difGreen, &difBlue, &difAlpha);
  GLfloat meteor[] = {ambRed, ambGreen, ambBlue, 1};
  // Draw score of team
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        set2Dcolour(white);
        startX = 20 + j + i * (cubeSide * 4) + j * cubeSide;
        startY = 20 + k + k * cubeSide;
        if (score > 0) {
          set2Dcolour(meteor);
          draw2Dbox(startX, startY, startX + cubeSide, startY + cubeSide);
          score--;
        } else {
          draw2Dbox(startX, startY, startX + cubeSide, startY + cubeSide);
        }
      }
    }
  }
}

/******* draw2D() *******/
/* - draws 2D shapes on screen */
/* - use the following functions: */
/* - draw2Dline(int, int, int, int, int); */
/* - draw2Dbox(int, int, int, int);	*/
/* - draw2Dtriangle(int, int, int, int, int, int); */
/* - set2Dcolour(float []); */
/* - colour must be set before other functions are called	*/
void draw2D() {

  if (displayMap == 1) {
    // define minimap size
    // take off 20 pixles to add a small buffer to the edge of the screen
    int mapWidth = (screenWidth / 4) / WORLDX * WORLDX;
    int mapStartX = screenWidth - mapWidth - 20;
    int mapStartY = screenHeight - mapWidth - 20;
    int cubeWidth = mapWidth / WORLDX;
    drawMap(mapStartX, mapStartY, mapWidth, mapWidth, cubeWidth, cubeWidth);
  } else if (displayMap == 2) {
    // define fullmap size
    // take off 50 pixles to add a small buffer to the edge of the screen
    int mapHeight = (screenHeight - 50) / WORLDZ * WORLDZ;
    int mapStartX = (screenWidth - mapHeight) / 2;
    int mapStartY = (screenHeight - mapHeight) / 2;
    int cubeWidth = mapHeight / WORLDX;
    drawMap(mapStartX, mapStartY, mapHeight, mapHeight, cubeWidth, cubeWidth);
  }
  drawScore(newWorld->teams[1]);
}

/*** update() ***/
/* background process, it is called when there are no other events */
/* -used to control animations and perform calculations while the  */
/*  system is running */
/* -gravity must also implemented here, duplicate collisionResponse */
void update() {
  if (!paused) {
    moveClouds();
    moveMeteors();
    moveTrucks();
    moveProjectiles();

    // try and fire towers
    towerSurvey();

    if (isPlacingTower == TRUE) {
      pickTowerLocation(placingTower);
    }
    opponentMove();

    // check win condition
    checkVault();
  }
}

/* called by GLUT when a mouse button is pressed or released */
/* -button indicates which button was pressed or released */
/* -state indicates a button down or button up event */
/* -x,y are the screen coordinates when the mouse is pressed or */
/*  released */
void mouse(int button, int state, int x, int y) {

  if (button == GLUT_LEFT_BUTTON) {
    fireMouseProjectile();
  } else if (button == GLUT_MIDDLE_BUTTON)
    printf("middle button - ");
  else
    printf("right button - ");

  if (state == GLUT_UP) {
    // printf("up - ");
  } else {
    // printf("down - ");
  }
}

int main(int argc, char **argv) {
  /* initialize the graphics system */
  graphicsInit(&argc, argv);

  // Making space for the world and the objects in the world
  newWorld = (WorldData *)malloc(sizeof(WorldData));
  if (newWorld == NULL)
    printf("Unable to allocate space for the worldData");

  genWorld();
  createTeams();

  /* starts the graphics processing loop */
  /* code after this will not run until the program exits */
  glutMainLoop();
  return 0;
}

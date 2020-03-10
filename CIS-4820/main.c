
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

//
//
// /* update old position so it contains the correct value */
// /* -otherwise view position is only correct after a key is */
// /*  pressed and keyboard() executes. */
// #if 0
//       // Fire a ray in the direction of forward motion
//       float xx, yy, zz;
//       getViewPosition(&x, &y, &z);
//       getOldViewPosition(&xx, &yy, &zz);
//       printf("%f %f %f %f %f %f\n", xx, yy, zz, x, y, z);
//       printf("%f %f %f\n",  -xx+((x-xx)*25.0), -yy+((y-yy)*25.0),
//       -zz+((z-zz)*25.0)); createTube(2, -xx, -yy, -zz, -xx-((x-xx)*25.0),
//       -yy-((y-yy)*25.0), -zz-((z-zz)*25.0), 5);
// #endif
//
//     getViewPosition(&x, &y, &z);
//     setOldViewPosition(x, y, z);
//
//     /* sample of rotation and positioning of mob */
//     /* coordinates for mob 0 */
//     static float mob0x = 50.0, mob0y = 25.0, mob0z = 52.0;
//     static float mob0ry = 0.0;
//     static int increasingmob0 = 1;
//
//     /* coordinates for mob 1 */
//     static float mob1x = 50.0, mob1y = 25.0, mob1z = 52.0;
//     static float mob1ry = 0.0;
//     static int increasingmob1 = 1;
//     /* counter for user defined colour changes */
//     static int colourCount = 0;
//     static GLfloat offset = 0.0;
//
//     /* move mob 0 and rotate */
//     /* set mob 0 position */
//     setMobPosition(0, mob0x, mob0y, mob0z, mob0ry);
//
//     /* move mob 0 in the x axis */
//     if (increasingmob0 == 1)
//       mob0x += 0.2;
//     else
//       mob0x -= 0.2;
//     if (mob0x > 50)
//       increasingmob0 = 0;
//     if (mob0x < 30)
//       increasingmob0 = 1;
//
//     /* rotate mob 0 around the y axis */
//     mob0ry += 1.0;
//     if (mob0ry > 360.0)
//       mob0ry -= 360.0;
//
//     /* move mob 1 and rotate */
//     setMobPosition(1, mob1x, mob1y, mob1z, mob1ry);
//
//     /* move mob 1 in the z axis */
//     /* when mob is moving away it is visible, when moving back it */
//     /* is hidden */
//     if (increasingmob1 == 1) {
//       mob1z += 0.2;
//       showMob(1);
//     } else {
//       mob1z -= 0.2;
//       hideMob(1);
//     }
//     if (mob1z > 72)
//       increasingmob1 = 0;
//     if (mob1z < 52)
//       increasingmob1 = 1;
//
//     /* rotate mob 1 around the y axis */
//     mob1ry += 1.0;
//     if (mob1ry > 360.0)
//       mob1ry -= 360.0;
//
//     /* change user defined colour over time */
//     if (colourCount == 1)
//       offset += 0.05;
//     else
//       offset -= 0.01;
//     if (offset >= 0.5)
//       colourCount = 0;
//     if (offset <= 0.0)
//       colourCount = 1;
//     setUserColour(9, 0.7, 0.3 + offset, 0.7, 1.0, 0.3, 0.15 + offset,
//     0.3, 1.0);
//
//     /* sample tube creation  */
//     /* draws a purple tube above the other sample objects */
//     createTube(1, 45.0, 30.0, 45.0, 50.0, 30.0, 50.0, 6);
//
//     /* end testworld animation */
//

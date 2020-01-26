
/* Derived from scene.c in the The OpenGL Programming Guide */
/* Keyboard and mouse rotation taken from Swiftless Tutorials #23 Part 2 */
/* http://www.swiftless.com/tutorials/opengl/camera2.html */

/* Frames per second code taken from : */
/* http://www.lighthouse3d.com/opengl/glut/index.php?fps */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generation.h"
#include "graphics.h"
#include "timing.h"
#include "visible.h"

/******* doesCollide() *******/
/* - checks the identity of the provided block */
/* - returns true or false if that block is solid */
int doesCollide(int x, int y, int z) {
  if (world[x][y][z] != 0)
    return 1;
  return 0;
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
  for (float j = -y - 0.1; j < -y + 0.2; j += 0.1) {
    for (float i = -x - 0.1; i < -x + 0.2; i += 0.1) {
      for (float k = -z - 0.1; k < -z + 0.2; k += 0.1) {
        if (doesCollide((int)i, (int)j, (int)k))
          setViewPosition(xx, yy, zz);
      }
    }
  }
  // printf("(%lf, %lf, %lf) => (%lf, %lf, %lf) \n", xx, yy, zz, x, y, z);
}

/******* draw2D() *******/
/* draws 2D shapes on screen */
/* use the following functions: 			*/
/*	draw2Dline(int, int, int, int, int);		*/
/*	draw2Dbox(int, int, int, int);			*/
/*	draw2Dtriangle(int, int, int, int, int, int);	*/
/*	set2Dcolour(float []); 				*/
/* colour must be set before other functions are called	*/
void draw2D() {

  if (testWorld) {
    /* draw some sample 2d shapes */
    if (displayMap == 1) {
      GLfloat green[] = {0.0, 0.5, 0.0, 0.5};
      set2Dcolour(green);
      draw2Dline(0, 0, 500, 500, 15);
      draw2Dtriangle(0, 0, 200, 200, 0, 200);

      GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
      set2Dcolour(black);
      draw2Dbox(500, 380, 524, 388);
    }
  } else {

    /* your code goes here */
  }
}

/*** update() ***/
/* background process, it is called when there are no other events */
/* -used to control animations and perform calculations while the  */
/*  system is running */
/* -gravity must also implemented here, duplicate collisionResponse */
void update() {
  int i, j, k;
  float *la;
  float x, y, z;

  /* sample animation for the testworld, don't remove this code */
  /* demo of animating mobs */
  if (testWorld) {

/* update old position so it contains the correct value */
/* -otherwise view position is only correct after a key is */
/*  pressed and keyboard() executes. */
#if 0
      // Fire a ray in the direction of forward motion
      float xx, yy, zz;
      getViewPosition(&x, &y, &z);
      getOldViewPosition(&xx, &yy, &zz);
      printf("%f %f %f %f %f %f\n", xx, yy, zz, x, y, z);
      printf("%f %f %f\n",  -xx+((x-xx)*25.0), -yy+((y-yy)*25.0), -zz+((z-zz)*25.0));
      createTube(2, -xx, -yy, -zz, -xx-((x-xx)*25.0), -yy-((y-yy)*25.0), -zz-((z-zz)*25.0), 5);
#endif

    getViewPosition(&x, &y, &z);
    setOldViewPosition(x, y, z);

    /* sample of rotation and positioning of mob */
    /* coordinates for mob 0 */
    static float mob0x = 50.0, mob0y = 25.0, mob0z = 52.0;
    static float mob0ry = 0.0;
    static int increasingmob0 = 1;
    /* coordinates for mob 1 */
    static float mob1x = 50.0, mob1y = 25.0, mob1z = 52.0;
    static float mob1ry = 0.0;
    static int increasingmob1 = 1;
    /* counter for user defined colour changes */
    static int colourCount = 0;
    static GLfloat offset = 0.0;

    /* move mob 0 and rotate */
    /* set mob 0 position */
    setMobPosition(0, mob0x, mob0y, mob0z, mob0ry);

    /* move mob 0 in the x axis */
    if (increasingmob0 == 1)
      mob0x += 0.2;
    else
      mob0x -= 0.2;
    if (mob0x > 50)
      increasingmob0 = 0;
    if (mob0x < 30)
      increasingmob0 = 1;

    /* rotate mob 0 around the y axis */
    mob0ry += 1.0;
    if (mob0ry > 360.0)
      mob0ry -= 360.0;

    /* move mob 1 and rotate */
    setMobPosition(1, mob1x, mob1y, mob1z, mob1ry);

    /* move mob 1 in the z axis */
    /* when mob is moving away it is visible, when moving back it */
    /* is hidden */
    if (increasingmob1 == 1) {
      mob1z += 0.2;
      showMob(1);
    } else {
      mob1z -= 0.2;
      hideMob(1);
    }
    if (mob1z > 72)
      increasingmob1 = 0;
    if (mob1z < 52)
      increasingmob1 = 1;

    /* rotate mob 1 around the y axis */
    mob1ry += 1.0;
    if (mob1ry > 360.0)
      mob1ry -= 360.0;

    /* change user defined colour over time */
    if (colourCount == 1)
      offset += 0.05;
    else
      offset -= 0.01;
    if (offset >= 0.5)
      colourCount = 0;
    if (offset <= 0.0)
      colourCount = 1;
    setUserColour(9, 0.7, 0.3 + offset, 0.7, 1.0, 0.3, 0.15 + offset, 0.3, 1.0);

    /* sample tube creation  */
    /* draws a purple tube above the other sample objects */
    createTube(1, 45.0, 30.0, 45.0, 50.0, 30.0, 50.0, 6);

    /* end testworld animation */

  } else {
    moveClouds();
  }
}

/* called by GLUT when a mouse button is pressed or released */
/* -button indicates which button was pressed or released */
/* -state indicates a button down or button up event */
/* -x,y are the screen coordinates when the mouse is pressed or */
/*  released */
void mouse(int button, int state, int x, int y) {

  if (button == GLUT_LEFT_BUTTON)
    printf("left button - ");
  else if (button == GLUT_MIDDLE_BUTTON)
    printf("middle button - ");
  else
    printf("right button - ");

  if (state == GLUT_UP)
    printf("up - ");
  else
    printf("down - ");

  printf("%d %d\n", x, y);
}

int main(int argc, char **argv) {
  /* initialize the graphics system */
  graphicsInit(&argc, argv);

  if (testWorld == 1) {
    genTestWorld();
  } else {
    genWorld();
  }

  /* starts the graphics processing loop */
  /* code after this will not run until the program exits */
  glutMainLoop();
  return 0;
}

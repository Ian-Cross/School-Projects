#ifndef TOWER_HEADER
#define TOWER_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define TOWER_HEIGHT 5

typedef struct tower {
  int xLoc;
  int zLoc;
  int yLoc;
  int projectileID;
} Tower;

/*** createTower() ***/
/* - Allocate memory and fill the tower object */
Tower *createTower(Base *, int, int);

/*** drawTower() ***/
/* - Render the tower at its current x and z location */
/* - Pick a y location that puts it ontop of the world to account for hills and
 * valleys */
void drawTower();

void towerSurvey();

#endif

#ifndef PROJECTILE_HEADER
#define PROJECTILE_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define PROJECTILE_SPEED 10

float mouseRotX, mouseRotY, mouseRotZ;
int totalProjectiles;

typedef struct projectile {
  int id;
  int visible;
  float xLoc;
  float yLoc;
  float zLoc;
  float xVel;
  float yVel;
  float zVel;
  struct projectile *next;
  double lastTimeMoved;
} Projectile;

int totalProjectiles;

/*** canFireProjectile() ***/
/* - Iterate through the world projectiles, and check if the indicated
 * projectile is in use */
int canFireProjectile(int);

void addProjectile();

void moveProjectile();
void moveMouseProjectile();

void fireMouseProjectile();
void fireTowerProjectile();

#endif

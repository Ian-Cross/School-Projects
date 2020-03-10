#ifndef PROJECTILE_HEADER
#define PROJECTILE_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

float mouseRotX, mouseRotY, mouseRotZ;
int totalProjectiles;

typedef struct projectile {
  int id;
  int visible;
  float xLoc;
  float yLoc;
  float zLoc;
  float targetX;
  float targetY;
  float targetZ;
  struct projectile *next;
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

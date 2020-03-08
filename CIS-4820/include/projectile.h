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
} Projectile;

void fireMouseProjectile();
void fireTowerProjectile();

#endif

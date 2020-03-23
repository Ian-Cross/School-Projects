#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"
int totalProjectiles = 0;

Projectile *createProjectile() {
  Projectile *newProjectile = (Projectile *)malloc(sizeof(Projectile));

  newProjectile->visible = 0;
  newProjectile->xLoc = 0;
  newProjectile->yLoc = 0;
  newProjectile->zLoc = 0;
  newProjectile->xVel = 0;
  newProjectile->yVel = 0;
  newProjectile->xVel = 0;
  newProjectile->next = NULL;
  newProjectile->lastTimeMoved = 0;
  return newProjectile;
}

/*** canFireProjectile() ***/
/* - Iterate through the world projectiles, and check if the indicated
 * projectile is in use */
int canFireProjectile(int projectileID) {
  int idx = 0;
  Projectile *currProject = newWorld->projectiles;
  while (currProject != NULL) {
    idx++;
    if (projectileID == idx && currProject->visible == 0) {
      return TRUE;
    }
    currProject = currProject->next;
  }
  return FALSE;
}

/*** addProjectile() ***/
/* - Allocate memory and fill in projectile object */
/* add the new projectile to the world Object */
void addProjectile() {
  Projectile *currProjectile = newWorld->projectiles;
  Projectile *newProjectile = createProjectile();

  if (currProjectile == NULL) {
    newProjectile->id = 1;
    newWorld->projectiles = newProjectile;
  } else {
    while (currProjectile->next != NULL)
      currProjectile = currProjectile->next;

    currProjectile->next = newProjectile;
    newProjectile->id = currProjectile->id + 1;
  }
}

void moveMouseProjectile() {

  float mobX = mobPosition[0][0], mobY = mobPosition[0][1],
        mobZ = mobPosition[0][2];

  float rotx = (mouseRotX / 180.0 * 3.141592);
  float roty = (mouseRotY / 180.0 * 3.141592);
  mobX += sin(roty) * 0.8;
  mobY -= sin(rotx) * 0.8;
  mobZ -= cos(roty) * 0.8;

  setMobPosition(0, mobX, mobY, mobZ, 0.0);
  if (withinBounds(mobX, mobY, mobZ))
    showMob(0);
  else
    hideMob(0);

  for (float j = mobY + 0.4; j > mobY - 0.8; j -= 0.4) {
    for (float i = mobX + 0.4; i > mobX - 0.8; i -= 0.4) {
      for (float k = mobZ + 0.4; k > mobZ - 0.8; k -= 0.4) {
        if (world[(int)i][(int)j][(int)k] != 0) {
          hideMob(0);
          if (world[(int)i][(int)j][(int)k] == VEHICLE_1 ||
              world[(int)i][(int)j][(int)k] == VEHICLE_2 ||
              world[(int)i][(int)j][(int)k] == TIRES) {
            Truck *hurtTruck = truckLookup((int)i, (int)j, (int)k);
            if (hurtTruck != NULL) {
              hurtTruck->health--;
              if (hurtTruck->health == 0)
                teleportToBase(hurtTruck);
            } else {
              printf("Null Hurt truck\n");
            }
          }
          world[(int)i][(int)j][(int)k] = 0;
          return;
        }
      }
    }
  }
}

void moveProjectile(Projectile *projectile) {

  float mobX = projectile->xLoc, mobY = projectile->yLoc,
        mobZ = projectile->zLoc;

  mobX += projectile->xVel * 0.5;
  mobY += projectile->yVel * 0.5;
  mobZ += projectile->zVel * 0.5;

  if (withinBounds(mobX, mobY, mobZ))
    projectile->visible = TRUE;
  else
    projectile->visible = FALSE;

  projectile->xLoc = mobX;
  projectile->yLoc = mobY;
  projectile->zLoc = mobZ;

  for (float j = mobY + 0.4; j > mobY - 0.8; j -= 0.4) {
    for (float i = mobX + 0.4; i > mobX - 0.8; i -= 0.4) {
      for (float k = mobZ + 0.4; k > mobZ - 0.8; k -= 0.4) {
        if (world[(int)i][(int)j][(int)k] != 0) {
          projectile->visible = FALSE;
          if (world[(int)i][(int)j][(int)k] == VEHICLE_1 ||
              world[(int)i][(int)j][(int)k] == VEHICLE_2 ||
              world[(int)i][(int)j][(int)k] == TIRES) {
            Truck *hurtTruck = truckLookup((int)i, (int)j, (int)k);
            if (hurtTruck != NULL) {
              hurtTruck->health--;
              if (hurtTruck->health == 0)
                teleportToBase(hurtTruck);
            } else {
              printf("Null Hurt truck\n");
            }
          }
          world[(int)i][(int)j][(int)k] = 0;
          return;
        }
      }
    }
  }
}

void fireMouseProjectile() {
  float x, y, z;
  getViewPosition(&x, &y, &z);

  if (mobVisible[0] == 0) {
    getViewOrientation(&mouseRotX, &mouseRotY, &mouseRotZ);
    createMob(0, -x, -y, -z, 0.0);
  }
}

void fireTowerProjectile(Tower *tower, Coord target) {
  Projectile *worldProjectile = newWorld->projectiles;
  while (worldProjectile != NULL) {
    if (worldProjectile->id == tower->projectileID) {
      worldProjectile->xLoc = tower->xLoc;
      worldProjectile->zLoc = tower->zLoc;
      worldProjectile->yLoc = tower->yLoc + TOWER_HEIGHT;
      worldProjectile->visible = TRUE;

      float xDif = target.x - worldProjectile->xLoc;
      float yDif = target.y - worldProjectile->yLoc;
      float zDif = target.z - worldProjectile->zLoc;

      float maxDif = 0;
      if (fabs(xDif) > maxDif)
        maxDif = fabs(xDif);
      if (fabs(yDif) > maxDif)
        maxDif = fabs(yDif);
      if (fabs(zDif) > maxDif)
        maxDif = fabs(zDif);
      worldProjectile->xVel = xDif / maxDif;
      worldProjectile->yVel = yDif / maxDif;
      worldProjectile->zVel = zDif / maxDif;

      break;
    }
    worldProjectile = worldProjectile->next;
  }
}

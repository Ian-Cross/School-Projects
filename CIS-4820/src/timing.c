#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "main.h"

double lastCloudTime = 0;
double lastMeteorTime = 0;
int meteorSpawnCount = 0;
int lastMeteorSecond = 0;

double getTimeMS() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}

/******* moveClouds() *******/
/* - Iterate over all the clouds */
/* - Move each cloud by 1 space every 1000 milli-seconds */
void moveClouds() {
  double currTime = getTimeMS();

  if (currTime - lastCloudTime >= CLOUD_MOVE_SPEED) {
    lastCloudTime = currTime;
    for (int i = 0; i < MAX_CLOUD_COUNT; i++) {
      clearCloud(newWorld->clouds[i]);
      moveCloud(newWorld->clouds[i]);
      drawCloud(newWorld->clouds[i]);
    }
  }
}

/******* moveMeteors() *******/
/* - Iterate over all the meteors */
/* - Move each meteor by its velocity vectory 500 milli-seconds */
void moveMeteors() {
  double currTime = getTimeMS();
  // make sure enough time has passed
  if (currTime - lastMeteorTime > METEOR_MOVE_SPEED) {
    lastMeteorTime = currTime;

    Meteor *meteor = newWorld->meteors;
    while (meteor != NULL) {
      clearMeteor(meteor);
      moveMeteor(meteor);
      drawMeteor(meteor);

      if (meteor->falling == 0) {
        clearTail(meteor);
        meteor = removeMeteor(meteor);
      } else {
        meteor = meteor->next;
      }
    }
  }

  if ((int)(currTime / 1000) != lastMeteorSecond) {
    lastMeteorSecond = (int)(currTime / 1000);
    meteorSpawnCount++;
  }

  if (meteorSpawnCount == 10) {
    meteorSpawnCount = 0;
    for (int i = 0; i < 10; i++) {
      addMeteor(createMeteor());
    }
  }
}

/******* moveTrucks() *******/
/* - Iterate over all of the trucks */
/* - Move each by 1 block each time their internal clock allows */
void moveTrucks() {
  double currTime = getTimeMS();
  for (int i = 0; i < TEAM_COUNT; i++) {
    Team *currTeam = newWorld->teams[i];
    for (int j = 0; j < TRUCK_COUNT; j++) {
      Truck *currTruck = currTeam->trucks[j];
      if (currTime - currTruck->lastTimeMoved >= TRUCK_SPEED) {
        currTruck->lastTimeMoved = currTime;
        clearTruck(currTruck);
        moveTruck(currTruck, currTeam);
        drawTruck(currTruck);
      }
    }
  }
}

void moveProjectiles() {
  if (mobVisible[0] == 1) {
    moveMouseProjectile();
  }
  Projectile *worldProjectile = newWorld->projectiles;
  while (worldProjectile != NULL) {
    if (worldProjectile->visible == TRUE)
      moveProjectile(worldProjectile);
    worldProjectile = worldProjectile->next;
  }
}

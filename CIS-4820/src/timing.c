#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "cloud.h"
#include "generation.h"
#include "graphics.h"
#include "meteor.h"
#include "projectile.h"

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
                hurtTruck->health -= 2;
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
}

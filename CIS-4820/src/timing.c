#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "main.h"

double lastCloudTime = 0;
double lastMeteorTime = 0;
double lastOpponentTime = 0;
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
    Truck *currTruck = currTeam->trucks;
    while (currTruck != NULL) {
      if (currTime - currTruck->lastTimeMoved >= TRUCK_SPEED) {
        currTruck->lastTimeMoved = currTime;
        clearTruck(currTruck);
        moveTruck(currTruck, currTeam);
        drawTruck(currTruck);
      }
      currTruck = currTruck->next;
    }
  }
}

void moveProjectiles() {
  double currTime = getTimeMS();
  if (mobVisible[0] == 1) {
    moveMouseProjectile();
  }
  Projectile *worldProjectile = newWorld->projectiles;
  while (worldProjectile != NULL) {
    // if (currTime - worldProjectile->lastTimeMoved >= PROJECTILE_SPEED)
    // worldProjectile->lastTimeMoved = currTime;
    if (worldProjectile->visible == TRUE)
      moveProjectile(worldProjectile);
    worldProjectile = worldProjectile->next;
  }
}

void opponentMove() {
  double currTime = getTimeMS();
  int spawnType = rand() % 25;
  int spawnChance = rand() % 1000;

  if (currTime - lastOpponentTime >= OPPONENT_MOVE_SPEED) {
    lastOpponentTime = currTime;
    Team *team = newWorld->teams[0];
    if (team->truckCount <= MAX_TRUCKS && spawnType >= 15 &&
        team->meteorCount >= 1) {
      if (spawnChance < TRUCK_BUILD_CHANCE) {
        addTruck(0);
        team->meteorCount--;
      }
    } else if (team->towerCount <= MAX_TOWERS && spawnType >= 10 &&
               team->meteorCount >= 2) {
      if (spawnChance < TOWER_BUILD_CHANCE) {
        Tower *newTower = createTower();
        Tower *teamTowers = team->towers;

        if (teamTowers == NULL) {
          // Add the first tower next to the base
          newTower->xLoc = team->base->xLoc - 8;
          newTower->zLoc = team->base->zLoc + rand() % 5;
        } else {
          // search through the towers that are added and extend the train
          while (teamTowers->next != NULL) {
            teamTowers = teamTowers->next;
          }
          newTower->xLoc = teamTowers->xLoc - 8;
          newTower->zLoc = teamTowers->zLoc + rand() % 5;
        }

        if (withinBounds(newTower->xLoc, 5, newTower->zLoc)) {
          // Add Tower to the teams list
          if (teamTowers == NULL) {
            team->towers = newTower;
          } else {
            while (teamTowers->next != NULL) {
              teamTowers = teamTowers->next;
            }
            teamTowers->next = newTower;
          }
          team->towerCount++;
          team->meteorCount -= 2;
          drawTower(newTower, team);
        }
      }
    }
  }
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generation.h"
#include "graphics.h"
#include "projectile.h"

/*** createTower() ***/
/* - */
Tower *createTower(Base *base, int truckNum, int teamNumber) {
  Tower *newTower = (Tower *)malloc(sizeof(Tower));
  if (newTower == NULL)
    printf("Unable to allocate space for truck");

  newTower->xLoc = rand() % (WORLDX - 20) + 10;
  newTower->yLoc = WORLDY;
  newTower->zLoc = rand() % (WORLDZ - 20) + 10;
  newTower->projectile = 0;
  return newTower;
}

void drawTower(Tower *tower, Team *team) {
  int highestY = 0;
  for (int i = 0; i < WORLDY; i++) {
    if (world[tower->xLoc][i][tower->zLoc] == 0) {
      highestY = i;
      break;
    }
  }
  tower->yLoc = highestY < tower->yLoc ? highestY : tower->yLoc;

  for (int i = 0; i < 5; i++) {
    world[tower->xLoc][highestY + i][tower->zLoc] = team->teamBaseColour;
  }
}

// void fireProjectile() {}

int checkSurroundings(Tower *tower, Team *team) {
  int enemyColour = team->teamNumber == TEAM_ONE ? VEHICLE_2 : VEHICLE_1;
  int radius = 10;
  for (int y = tower->yLoc - 3; y < tower->yLoc + 3; y++) {
    for (int z = -radius; z < radius; z++) {
      int half_row_width = sqrt(radius * radius - z * z);
      for (int x = -half_row_width; x < half_row_width; x++) {
        if (withinBounds(tower->xLoc + x, y, tower->zLoc + z)) {
          // world[tower->xLoc + x][y][tower->zLoc + z] = 3;
          if (world[tower->xLoc + x][y][tower->zLoc + z] == enemyColour) {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

void towerSurvey() {
  for (int i = 0; i < TEAM_COUNT; i++) {
    Team *team = newWorld->teams[i];
    for (int j = 0; j < TOWER_COUNT; j++) {
      Tower *tower = team->towers[j];
      if (checkSurroundings(tower, team)) {
        if (tower->projectile == 0) {
          fireTowerProjectile();
        }
      }
    }
  }
}

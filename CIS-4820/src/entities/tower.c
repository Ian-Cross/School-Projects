#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int isPlacingTower = FALSE;
Tower *placingTower = NULL;
int lastPlaceColour = -1;
Coord lastPlaceLocation = {0, 0, 0};

/*** createTower() ***/
/* - Allocate memory and fill the tower object */
Tower *createTower() {
  Tower *newTower = (Tower *)malloc(sizeof(Tower));
  if (newTower == NULL)
    printf("Unable to allocate space for truck");

  // newTower->xLoc = rand() % (WORLDX - 20) + 10;
  newTower->xLoc = 0;
  newTower->yLoc = WORLDY;
  // newTower->zLoc = rand() % (WORLDZ - 20) + 10;
  newTower->zLoc = 0;
  newTower->projectileID = ++totalProjectiles;
  newTower->next = NULL;
  addProjectile();
  return newTower;
}

/*** drawTower() ***/
/* - Render the tower at its current x and z location */
/* - Pick a y location that puts it ontop of the world to account for hills and
 * valleys */
void drawTower(Tower *tower, Team *team) {
  int highestY = 0;
  for (int i = 0; i < WORLDY; i++) {
    if (world[tower->xLoc][i][tower->zLoc] == 0) {
      highestY = i;
      break;
    }
  }
  tower->yLoc = highestY < tower->yLoc ? highestY : tower->yLoc;

  for (int i = 0; i < TOWER_HEIGHT; i++) {
    world[tower->xLoc][highestY + i][tower->zLoc] = team->teamBaseColour;
  }
}

Coord checkSurroundings(Tower *tower, Team *team) {
  Coord target = {-1, -1, -1};
  int enemyColour = team->teamNumber == TEAM_ONE ? VEHICLE_2 : VEHICLE_1;
  int radius = 10;
  for (int y = tower->yLoc - 3; y < tower->yLoc + 5; y++) {
    for (int z = -radius; z < radius; z++) {
      int half_row_width = sqrt(radius * radius - z * z);
      for (int x = -half_row_width; x < half_row_width; x++) {
        if (withinBounds(tower->xLoc + x, y, tower->zLoc + z)) {
          if (world[tower->xLoc + x][y][tower->zLoc + z] == enemyColour) {
            target.x = tower->xLoc + x;
            target.y = y;
            target.z = tower->zLoc + z;
            return target;
          }
        }
      }
    }
  }
  return target;
}

/*** towerSurvey() ***/
/* - check the area around the tower for enemies */
/* - if an enemy is found, attempt to shoot at it */
void towerSurvey() {
  for (int i = 0; i < TEAM_COUNT; i++) {
    Team *team = newWorld->teams[i];
    Tower *currTower = team->towers;
    while (currTower != NULL) {
      // Quickly redraw the tower incase they have been shot
      for (int i = 0; i < TOWER_HEIGHT; i++) {
        world[currTower->xLoc][currTower->yLoc + i][currTower->zLoc] =
            team->teamBaseColour;
      }

      Coord attackLocation = checkSurroundings(currTower, team);
      if (attackLocation.x != -1) {
        if (canFireProjectile(currTower->projectileID)) {
          fireTowerProjectile(currTower, attackLocation);
        }
      }
      currTower = currTower->next;
    }
  }
}

void pickTowerLocation(Tower *tower) {

  float x, y, z;
  float mouseRotX, mouseRotY, mouseRotZ;
  getViewPosition(&x, &y, &z);
  getViewOrientation(&mouseRotX, &mouseRotY, &mouseRotZ);

  float rotx = (mouseRotX / 180.0 * 3.141592);
  float roty = (mouseRotY / 180.0 * 3.141592);
  float towerX = -x, towerY = -y, towerZ = -z;
  int found = 0;

  while (withinBounds(towerX, towerY, towerZ)) {
    towerX += sin(roty) * 0.8;
    towerY -= sin(rotx) * 0.8;
    towerZ -= cos(roty) * 0.8;

    if (world[(int)towerX][(int)towerY][(int)towerZ] != 0) {
      found = 1;
      break;
    }
  }

  if (found) {
    if (lastPlaceColour != -1)
      world[lastPlaceLocation.x][lastPlaceLocation.y][lastPlaceLocation.z] =
          lastPlaceColour;
    lastPlaceColour = world[(int)towerX][(int)towerY][(int)towerZ];
    lastPlaceLocation.x = (int)towerX;
    lastPlaceLocation.y = (int)towerY;
    lastPlaceLocation.z = (int)towerZ;
    world[(int)towerX][(int)towerY][(int)towerZ] = 4;
  }
}

int isStructureNearby(Tower *tower) {
  int radius = 10;
  for (int y = tower->yLoc - 3; y < tower->yLoc + 5; y++) {
    for (int z = -radius; z < radius; z++) {
      int half_row_width = sqrt(radius * radius - z * z);
      for (int x = -half_row_width; x < half_row_width; x++) {
        if (withinBounds(tower->xLoc + x, y, tower->zLoc + z)) {
          if (world[tower->xLoc + x][y][tower->zLoc + z] == BASE_2) {
            return TRUE;
          }
        }
      }
    }
  }
  return FALSE;
}

void placeTower() {
  placingTower->xLoc = lastPlaceLocation.x;
  placingTower->zLoc = lastPlaceLocation.z;

  int highestY = 0;
  for (int i = 0; i < WORLDY; i++) {
    if (world[placingTower->xLoc][i][placingTower->zLoc] == 0) {
      highestY = i;
      break;
    }
  }
  placingTower->yLoc = highestY;

  if (isStructureNearby(placingTower)) {
    drawTower(placingTower, newWorld->teams[1]);
    isPlacingTower = FALSE;
  } else {
    printf("Cannot Place There\n");
    placingTower->xLoc = -1;
    placingTower->zLoc = -1;
    placingTower->yLoc = -1;
  }
}

void addTower(int teamNumber) {
  Tower *newTower = createTower();
  Team *team = newWorld->teams[teamNumber];
  Tower *teamTowers = team->towers;

  if (teamTowers == NULL) {
    newWorld->teams[teamNumber]->towers = newTower;
  } else {
    while (teamTowers->next != NULL)
      teamTowers = teamTowers->next;
    teamTowers->next = newTower;
  }
  isPlacingTower = TRUE;
  placingTower = newTower;
}

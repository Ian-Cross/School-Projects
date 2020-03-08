#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generation.h"
#include "graphics.h"
#include "tower.h"
#include "truck.h"

/*** createTeams() ***/
/* - */
void createTeams() {
  for (int i = 0; i < 2; i++) {
    newWorld->teams[i] = (Team *)malloc(sizeof(Team));
    if (newWorld->teams[i] == NULL)
      printf("Unable to allocate space for team %d", i);

    newWorld->teams[i]->teamNumber = i;
    newWorld->teams[i]->teamBaseColour = BASE_1 + i;
    newWorld->teams[i]->teamVehicleColour = VEHICLE_1 + i;
    newWorld->teams[i]->meteorCount = 0;
    newWorld->teams[i]->base = (Base *)newWorld->objects[i]->structure;

    for (int j = 0; j < TRUCK_COUNT; j++) {
      newWorld->teams[i]->trucks[j] =
          createTruck(newWorld->teams[i]->base, j, i);
      drawTruck(newWorld->teams[i]->trucks[j], newWorld->teams[i]);
    }

    for (int j = 0; j < TOWER_COUNT; j++) {
      newWorld->teams[i]->towers[j] =
          createTower(newWorld->teams[i]->base, j, i);
      drawTower(newWorld->teams[i]->towers[j], newWorld->teams[i]);
    }
  }
}

void checkVault() {
  for (int i = 0; i < TEAM_COUNT; i++) {
    if (newWorld->teams[i]->meteorCount >= 27) {
      printf("Congradulations Team %s, you have won!\n",
             i == 0 ? "RED!" : "BLUE!");
      exit(0);
    }
    drawVault(newWorld->teams[i]);
  }
}

int lastMeteorCount = 0;
void drawVault(Team *team) {
  int meteorCount = team->meteorCount;
  if (meteorCount == lastMeteorCount)
    return;

  int vaultX = team->base->xLoc +
               (team->teamNumber == TEAM_ONE ? BASE_SIZE + 2 : -BASE_SIZE);
  int vaultZ = team->base->zLoc + 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        if (meteorCount == 0)
          return;
        world[vaultX + i][5 + j][vaultZ + k] = IDENTIFIED_METEOR;
        meteorCount--;
      }
    }
  }
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generation.h"
#include "graphics.h"
#include "truck.h"

/*** createTeams() ***/
/* - */
void createTeams() {
  for (int i = 0; i < 2; i++) {
    newWorld->teams[i] = (Team *)malloc(sizeof(Team));
    if (newWorld->teams[i] == NULL)
      printf("Unable to allocate space for team %d", i);

    newWorld->teams[i]->teamNumber = i;
    newWorld->teams[i]->teamColour = 27 + i;
    newWorld->teams[i]->meteorCount = 0;
    newWorld->teams[i]->base = (Base *)newWorld->objects[i]->structure;

    for (int j = 0; j < TRUCK_COUNT; j++) {
      newWorld->teams[i]->trucks[j] =
          createTruck(newWorld->teams[i]->base, j, i);
      drawTruck(newWorld->teams[i]->trucks[j], newWorld->teams[i]);
    }
  }
}

int lastMeteorCount = 0;

void drawVault(Team *team) {
  int meteorCount = team->meteorCount;
  if (meteorCount == lastMeteorCount)
    return;

  int vaultX = team->base->xLoc +
               (team->teamNumber == TEAM_ONE ? BASE_SIZE * 2 : -BASE_SIZE);
  int vaultZ = team->base->zLoc + 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        if (meteorCount == 0)
          return;
        world[vaultX + i][6 + j][vaultZ + k] = IDENTIFIED_METEOR;
        meteorCount--;
      }
    }
  }
}

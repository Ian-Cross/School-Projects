#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

/*** createTeams() ***/
/* - Allocate Memory for, and fill the team objects */
/* - Contains:
      a reference to the team base,
      a winCounter (meteorCount),
      a list of the team trucks,
      a list of the team towers */
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

    newWorld->teams[i]->trucks = createTruck(newWorld->teams[i]->base, i);
    drawTruck(newWorld->teams[i]->trucks);

    newWorld->teams[i]->towers = NULL;
  }
}

int lastMeteorCount = 0;
/*** drawVault() ***/
/* - draws a pile of meteors behind the base to signify score */
/* - only redraws if there is a new value */
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

/*** checkVault() ***/
/* - Checks both teams for the win condition */
/* - Randomly chooses which team to check first to remove bias */
void checkVault() {
  int firstTeam = rand() % 2;

  if (newWorld->teams[firstTeam]->meteorCount >= 27) {
    printf("Congradulations Team %s, you have won!\n",
           firstTeam == 0 ? "RED!" : "BLUE!");
    exit(0);
  }

  int secondTeam = firstTeam == TEAM_ONE ? TEAM_TWO : TEAM_ONE;

  if (newWorld->teams[secondTeam]->meteorCount >= 27) {
    printf("Congradulations Team %s, you have won!\n",
           secondTeam == 0 ? "RED!" : "BLUE!");
    exit(0);
  }

  drawVault(newWorld->teams[TEAM_ONE]);
  drawVault(newWorld->teams[TEAM_TWO]);
}

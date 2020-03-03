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
    newWorld->teams[i]->base = (Base *)newWorld->objects[i]->structure;

    for (int j = 0; j < TRUCKCOUNT; j++) {
      newWorld->teams[i]->trucks[j] =
          createTruck(newWorld->teams[i]->base, j, i);
      drawTruck(newWorld->teams[i]->trucks[j], newWorld->teams[i]);
    }
  }
}

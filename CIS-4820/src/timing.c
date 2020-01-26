#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cloud.h"
#include "generation.h"
#include "graphics.h"

int previousSecond = 0;

/******* moveClouds() *******/
/* - Iterate over all the clouds */
/* - Move each cloud by 1 space every 1 second */
void moveClouds() {
  time_t seconds = time(NULL);

  // make sure enough time has passed
  if (seconds != previousSecond && (seconds % CLOUD_MOVE_SPEED) == 0) {
    previousSecond = seconds;
    for (int i = 0; i < MAX_CLOUD_COUNT; i++) {
      clearCloud(newWorld->clouds[i]);
      moveCloud(newWorld->clouds[i]);
      drawCloud(newWorld->clouds[i]);
    }
  }
}

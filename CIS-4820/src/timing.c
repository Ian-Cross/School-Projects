#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/generation.h"
#include "../../include/graphics.h"
#include "../../include/worldObjects/cloud.h"

int lastSecond = 0;

void moveClouds() {
  time_t seconds;
  seconds = time(NULL);

  if (seconds != lastSecond && (seconds % MOVE_SPEED) == 0) {
    lastSecond = seconds;
    for (int i = 0; i < MAX_CLOUD_COUNT; i++) {
      clearCloud(newWorld->clouds[i]);
      moveCloud(newWorld->clouds[i]);
      drawCloud(newWorld->clouds[i]);
    }
    // printf("Moving Cloud \n");
  }
}

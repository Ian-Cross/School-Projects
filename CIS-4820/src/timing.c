#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cloud.h"
#include "generation.h"
#include "graphics.h"
#include "meteor.h"

int meteorMoveCount = 0;
int lastMeteorSecond = 0;
int cloudMoveCount = 0;

/******* moveClouds() *******/
/* - Iterate over all the clouds */
/* - Move each cloud by 1 space every 1000 second */
void moveClouds() {
  cloudMoveCount++;
  // make sure enough time has passed
  if ((cloudMoveCount % CLOUD_MOVE_SPEED) == 0) {
    cloudMoveCount /= CLOUD_MOVE_SPEED;
    for (int i = 0; i < MAX_CLOUD_COUNT; i++) {
      clearCloud(newWorld->clouds[i]);
      moveCloud(newWorld->clouds[i]);
      drawCloud(newWorld->clouds[i]);
    }
  }
}

/******* moveMeteors() *******/
/* - Iterate over all the meteors */
/* - Move each meteor by its velocity vectory 0.5 seconds */
void moveMeteors() {
  meteorMoveCount++;
  time_t seconds = time(NULL);
  // make sure enough time has passed
  if ((meteorMoveCount % METEOR_MOVE_SPEED) == 0) {
    meteorMoveCount /= METEOR_MOVE_SPEED;
    // printf("MOVING METEORS:\n");
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

  if (seconds != lastMeteorSecond && (seconds % 10) == 0) {
    lastMeteorSecond = seconds;
    for (int i = 0; i < 10; i++) {
      addMeteor(createMeteor());
    }
  }
}

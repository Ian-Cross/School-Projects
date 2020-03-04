#ifndef WORLD_HEADER
#define WORLD_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "base.h"
#include "cloud.h"
#include "hill.h"
#include "meteor.h"
#include "team.h"
#include "timing.h"
#include "valley.h"

#define RELOCATE_CHANCE 100

typedef enum userColours {
  GRASS_1 = 9,
  GRASS_2 = 10,
  GRASS_3 = 11,
  GRASS_4 = 12,
  GRASS_5 = 13,

  DIRT_1 = 14,
  DIRT_2 = 15,
  DIRT_3 = 16,
  DIRT_4 = 17,
  DIRT_5 = 18,

  OLD_BASE = 19,
  CLOUD_1 = 20,
  CLOUD_2 = 21,
  CLOUD_3 = 22,
  FIRE_1 = 23,
  FIRE_2 = 24,
  FIRE_3 = 25,
  METEOR = 26,
  BASE_1 = 27,
  BASE_2 = 28,
  IDENTIFIED_METEOR = 29,
  VEHICLE_1 = 30,
  VEHICLE_2 = 31,
  TIRES = 32,
} UserColours;

typedef struct Coords {
  int x;
  int y;
  int z;
} Coord;

typedef enum StructureId {
  invaldId = 0,
  valleyId,
  hillId,
  baseId,
} structureId;

typedef struct Objects {
  structureId id;
  void *structure;
  int render;
  int moveCount;
} Object;

typedef struct WorldDatas {
  int worldId;
  Object *objects[MAX_VALLEY_COUNT + MAX_HILL_COUNT + BASE_COUNT];
  Cloud *clouds[MAX_CLOUD_COUNT];
  Meteor *meteors;
  Team *teams[2];
} WorldData;

WorldData *newWorld;

/* the first part of this if statement builds a sample */
/* world which will be used for testing */
/* DO NOT remove this code. */
/* Put your code in the else statment below */
/* The testworld is only guaranteed to work with a world of
        with dimensions of 100,50,100. */
void genTestWorld();

void addMeteor(Meteor *newMeteor);
Meteor *removeMeteor(Meteor *meteor);

/******* genWorld() *******/
/* - Fill the world object */
/* - Create user defined colours */
void genWorld();

#endif

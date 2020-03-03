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

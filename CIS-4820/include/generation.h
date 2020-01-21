#ifndef WORLD_HEADER
#define WORLD_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "timing.h"
#include "worldObjects/base.h"
#include "worldObjects/cloud.h"
#include "worldObjects/hill.h"
#include "worldObjects/valley.h"

typedef enum StructureId {
  invalId = 0,
  valleyId,
  hillId,
  baseId,
} structureId;

typedef struct Objects {
  structureId id;
  void *structure;
} Object;

typedef struct WorldDatas {
  int worldId;
  Object *objects[MAX_VALLEY_COUNT + MAX_HILL_COUNT + BASE_COUNT];
  Cloud *clouds[MAX_CLOUD_COUNT];
} WorldData;

WorldData *newWorld;

/* the first part of this if statement builds a sample */
/* world which will be used for testing */
/* DO NOT remove this code. */
/* Put your code in the else statment below */
/* The testworld is only guaranteed to work with a world of
        with dimensions of 100,50,100. */
void genTestWorld();

void genWorld();

void fixOverlap(WorldData *worldData);

#endif

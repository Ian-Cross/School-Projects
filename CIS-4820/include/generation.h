#ifndef WORLD_HEADER
#define WORLD_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define RELOCATE_CHANCE 100
#define CLOUD_HEIGHT WORLDY - 3
#define GROUND_HEIGHT 5

typedef enum structureId {
  invaldId = 0,
  valleyId,
  hillId,
  baseId,
} StructureId;

typedef struct object {
  StructureId id;
  void *structure;
  int render;
  int moveCount;
} Object;

// void addMeteor(Meteor *newMeteor);
// Meteor *removeMeteor(Meteor *meteor);

/******* genWorld() *******/
/* - Fill the world object */
/* - Create user defined colours */
void genWorld();

#endif

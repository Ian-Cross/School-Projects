#ifndef TEAM_HEADER
#define TEAM_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include "base.h"
#include "tower.h"
#include "truck.h"

#define TRUCK_COUNT 5
#define TOWER_COUNT 5
#define TEAM_COUNT 2
#define TEAM_ONE 0
#define TEAM_TWO 1

typedef struct Teams {
  int teamNumber;
  int teamBaseColour;
  int teamVehicleColour;
  int meteorCount;
  Base *base;
  Truck *trucks[TRUCK_COUNT];
  Tower *towers[TOWER_COUNT];
} Team;

void createTeams();
void checkVault();
void drawVault();

#endif

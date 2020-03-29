#ifndef TEAM_HEADER
#define TEAM_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define TRUCK_COUNT 5
#define TOWER_COUNT 5
#define TEAM_COUNT 2
#define TEAM_ONE 0
#define TEAM_TWO 1

typedef struct truck Truck;
typedef struct tower Tower;

typedef struct Teams {
  int teamNumber;
  int teamBaseColour;
  int teamVehicleColour;
  int meteorCount;
  int lastMeteorCount;
  Base *base;
  Truck *trucks;
  Tower *towers;
  int truckCount;
  int towerCount;
} Team;

/*** createTeams() ***/
/* - Allocate Memory for, and fill the team objects */
/* - Contains:
      a reference to the team base,
      a winCounter (meteorCount),
      a list of the team trucks,
      a list of the team towers */
void createTeams();

/*** checkVault() ***/
/* - Checks both teams for the win condition */
/* - Randomly chooses which team to check first to remove bias */
void checkVault();

#endif

#ifndef OPPONENT_HEADER
#define OPPONENT_HEADER

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#define OPPONENT_MOVE_SPEED 100
#define TRUCK_BUILD_CHANCE 50
#define TOWER_BUILD_CHANCE 50

#define MAX_TRUCKS 10
#define MAX_TOWERS 5

void buildTower();
void buildTruck();

#endif

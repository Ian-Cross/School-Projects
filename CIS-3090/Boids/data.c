/* Boids using ASCII graphics
        -original NCurses code from "Game Programming in C with the Ncurses
   Library"
         https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/
         and from "NCURSES Programming HOWTO"
         http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
        -Boids algorithms from "Boids Pseudocode:
         http://www.kfish.org/boids/pseudocode.html
*/

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef NOGRAPHICS
#include <ncurses.h>
#include <unistd.h>
#endif

#define DELAY 50000
// default population size, number of boids
#define POPSIZE 50
// default number of threads
#define THREADCOUNT 1
// maximum screen size, both height and width
#define SCREENSIZE 100
// default number of iterations to run before exiting, only used
// when graphics are turned off
#define ITERATIONS 1000

// boid location (x,y,z) and velocity (vx,vy,vz) in boidArray[][]
#define BX 0
#define BY 1
#define BZ 2
#define VX 3
#define VY 4
#define VZ 5

#ifndef NOGRAPHICS
// maximum screen dimensions
int max_y = 0, max_x = 0;
#endif

// user defined number of boids to create in the population
int popsize;
int threadCount;
// location and velocity of boids
float **boidArray;
// change in velocity is stored for each boid (x,y,z)
float **boidUpdate;

void initBoids() {
  int i;
  // calculate initial random locations for each boid, scaled based on the
  // screen size
  for (i = 0; i < popsize; i++) {
    boidArray[i][BX] = (float)(random() % SCREENSIZE);
    boidArray[i][BY] = (float)(random() % SCREENSIZE);
    boidArray[i][BZ] = (float)(random() % SCREENSIZE);
    boidArray[i][VX] = 0.0;
    boidArray[i][VY] = 0.0;
    boidArray[i][VZ] = 0.0;
  }
}

#ifndef NOGRAPHICS
int drawBoids() {
  int c, i;
  float multx, multy;

  // update screen maximum size
  getmaxyx(stdscr, max_y, max_x);

  // used to scale position of boids based on screen size
  multx = (float)max_x / SCREENSIZE;
  multy = (float)max_y / SCREENSIZE;

  clear();

  // display boids
  for (i = 0; i < popsize; i++) {
    mvprintw((int)(boidArray[i][BX] * multy), (int)(boidArray[i][BY] * multx),
             "o");
  }

  refresh();

  usleep(DELAY);

  // read keyboard and exit if 'q' pressed
  c = getch();
  if (c == 'q')
    return (1);
  else
    return (0);
}
#endif

void rule1(int startRow, int endRow) {
  int i;
  float cx, cy, cz;

  cx = 0.0;
  cy = 0.0;
  cz = 0.0;

  // calculate centre of mass
  // calculated once and used for all updates in rule 1
  for (i = 0; i < popsize; i++) {
    cx += boidArray[i][BX];
    cy += boidArray[i][BY];
    cz += boidArray[i][BZ];
  }
  cx /= popsize;
  cy /= popsize;
  cz /= popsize;

  // update velocity, move towards centre of mass
  // initial use of boidUpdate[][] so overwrite old values
  for (i = startRow; i <= endRow; i++) {
    boidUpdate[i][BX] = (cx - boidArray[i][BX]) / popsize;
    boidUpdate[i][BY] = (cy - boidArray[i][BY]) / popsize;
    boidUpdate[i][BZ] = (cz - boidArray[i][BZ]) / popsize;
  }
}

float distance(int i, int j) {
  return (sqrtf(powf(boidArray[i][BX] - boidArray[j][BX], 2.0) +
                powf(boidArray[i][BY] - boidArray[j][BY], 2.0) +
                powf(boidArray[i][BZ] - boidArray[j][BZ], 2.0)));
}

void rule2(int startRow, int endRow) {
  int i, j;
  float cx, cy, cz;

  // keep boids from overlapping
  for (i = startRow; i <= endRow; i++) {
    cx = 0.0;
    cy = 0.0;
    cz = 0.0;
    for (j = 0; j < popsize; j++) {
      if (i != j) { // calculate when not the same boid
        if (distance(i, j) < 5.0) {
          cx = cx - (boidArray[j][BX] - boidArray[i][BX]);
          cy = cy - (boidArray[j][BY] - boidArray[i][BY]);
          cz = cz - (boidArray[j][BZ] - boidArray[i][BZ]);
        }
      }
    }
    boidUpdate[i][BX] += cx;
    boidUpdate[i][BY] += cy;
    boidUpdate[i][BZ] += cz;
  }
}

void rule3(int startRow, int endRow) {
  int i;
  float cx, cy, cz;

  cx = 0.0;
  cy = 0.0;
  cz = 0.0;

  // calculate average velocity
  // calculate once and use for all updates in rule 3
  for (i = 0; i < popsize; i++) {
    cx += boidArray[i][VX];
    cy += boidArray[i][VY];
    cz += boidArray[i][VZ];
  }
  cx /= popsize;
  cy /= popsize;
  cz /= popsize;

  // update velocity, move towards centre of mass
  for (i = startRow; i <= endRow; i++) {
    boidUpdate[i][BX] += (cx - boidArray[i][VX]) / 8.0;
    boidUpdate[i][BY] += (cy - boidArray[i][VY]) / 8.0;
    boidUpdate[i][BZ] += (cz - boidArray[i][VZ]) / 8.0;
  }
}

// move the flock towards a point
void moveFlock(int startRow, int endRow) {
  int i;
  static int count = 0;
  static int sign = 1;
  float px, py, pz;

  // pull flock towards two points as the program runs
  // every 200 iterations change point that flock is pulled towards
  if (count % 200 == 0 && endRow == popsize - 1) {
    // printf("flipping directions\n");
    sign = sign * -1;
  }
  if (sign == 1) {
    // move flock towards position (40,40,40)
    px = 40.0;
    py = 40.0;
    pz = 40.0;
  } else {
    // move flock towards position (60,60,60)
    px = 60.0;
    py = 60.0;
    pz = 60.0;
  }
  // add offset (px,py,pz) to each boid in order to pull it
  // towards the current target point
  for (i = startRow; i <= endRow; i++) {
    boidUpdate[i][BX] += (px - boidArray[i][BX]) / 200.0;
    boidUpdate[i][BY] += (py - boidArray[i][BY]) / 200.0;
    boidUpdate[i][BZ] += (pz - boidArray[i][BZ]) / 200.0;
  }
  if (endRow == popsize - 1) {
    // printf("increaseing move flock count %d\n", count);
    count++;
  }
}

void *moveBoids(void *rank) {
  int i;
  long localRank = (long)rank;
  int numRows = popsize / threadCount;
  int startRow = localRank * numRows;
  int endRow;
  if (localRank != threadCount - 1) {
    endRow = (localRank + 1) * numRows - 1;
  } else {
    endRow = popsize - 1;
  }
  // printf("Thread %ld of %d will operate from %d - %d\n", localRank,
  // threadCount, startRow, endRow);

  rule1(startRow, endRow);
  rule2(startRow, endRow);
  rule3(startRow, endRow);
  moveFlock(startRow, endRow);

  return NULL;
}

void allocateArrays() {
  int i;

  boidArray = malloc(sizeof(float *) * popsize);
  for (i = 0; i < popsize; i++)
    boidArray[i] = malloc(sizeof(float) * 6);

  boidUpdate = malloc(sizeof(float *) * popsize);
  for (i = 0; i < popsize; i++)
    boidUpdate[i] = malloc(sizeof(float) * 3);
}

void createThreads() {
  long thread;
  int i;
  pthread_t *thread_handles;

  thread_handles = malloc(threadCount * sizeof(pthread_t));

  for (thread = 0; thread < threadCount; thread++)
    pthread_create(&thread_handles[thread], NULL, moveBoids, (void *)thread);

  for (thread = 0; thread < threadCount; thread++)
    pthread_join(thread_handles[thread], NULL);

  // move boids by calculating updated velocity and new position
  for (i = 0; i < popsize; i++) {
    // update velocity for each boid
    boidArray[i][VX] += boidUpdate[i][BX];
    boidArray[i][VY] += boidUpdate[i][BY];
    boidArray[i][VZ] += boidUpdate[i][BZ];
    // update position for each boid
    boidArray[i][BX] += boidArray[i][VX];
    boidArray[i][BY] += boidArray[i][VY];
    boidArray[i][BZ] += boidArray[i][VZ];
  }

  free(thread_handles);
}

int main(int argc, char *argv[]) {
  int i, count;
  int argPtr;

  // set the default population size
  popsize = POPSIZE;
  // set number of iterations, only used for timing tests in boidspt
  // not used in curses version
  count = ITERATIONS;
  threadCount = THREADCOUNT;

  // read command line arguments for number of iterations and
  // number of boids
  if (argc > 1) {
    argPtr = 1;
    while (argPtr < argc) {
      if (strcmp(argv[argPtr], "-i") == 0) {
        sscanf(argv[argPtr + 1], "%d", &count);
        argPtr += 2;
      } else if (strcmp(argv[argPtr], "-c") == 0) {
        sscanf(argv[argPtr + 1], "%d", &popsize);
        argPtr += 2;
      } else if (strcmp(argv[argPtr], "-t") == 0) {
        sscanf(argv[argPtr + 1], "%d", &threadCount);
        argPtr += 2;
      } else {
        printf("USAGE: %s <-i iterations> <-c pop_size> <-t thread_count>\n",
               argv[0]);
        printf(" iterations -the number of times the population will be "
               "updated\n");
        printf(" pop_size -the number of boids to create\n");
        printf(" thread_count -the number of thread to utalize\n");
        printf(" the number of iterations only affects the non-curses program "
               "boidspt\n");
        printf(" the curses program exits when q is pressed\n");
        exit(1);
      }
    }
  }

  // allocate space for arrays to store boid position and velocity
  allocateArrays();

#ifndef NOGRAPHICS
  // initialize ncurses
  initscr();
  noecho();
  cbreak();
  timeout(0);
  curs_set(FALSE);
  // Global var `stdscr` is created by the call to `initscr()`
  getmaxyx(stdscr, max_y, max_x);
#endif

  // place boids in initial positions
  initBoids();

  // draw and move boids using ncurses
  // do not calculate timing in this loop, ncurses will reduce performance
#ifndef NOGRAPHICS
  while (1) {
    if (drawBoids() == 1)
      break;
    createThreads();
  }
#endif

  // calculate movement of boids but do not use ncurses to draw
#ifdef NOGRAPHICS
  printf("Number of iterations %d\n", count);
  printf("Number of boids %d\n", popsize);
  printf("Number of threads %d\n", threadCount);

  /*** Start timing here ***/
  clock_t time;
  time = clock();

  for (i = 0; i < count; i++) {
    createThreads();
  }

  time = clock() - time;
  double elapsed = ((double)time) / CLOCKS_PER_SEC;

  printf("It took %f seconds to run boids.\n", elapsed);
  /*** End timing here ***/
#endif

#ifndef NOGRAPHICS
  // shut down ncurses
  endwin();
#endif
}

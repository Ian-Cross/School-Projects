/*
 * Author: Ian Cross
 * Date: November 14 2019, 16:40
 * Last modified by: Ian
 * Last modified time:
 * Desc: A file to replicate Conways' game of life in a parallel way using
 * ncurses
 */
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DELAY 250000
#define RANDOM_THREASHOLD 75

#define BOARD_HEIGHT 160
#define BOARD_WIDTH 40

int **boardArray1;
int **boardArray2;

void initBoards() {
  time_t now;
  int i, j, random = 0;

  boardArray1 = malloc(BOARD_WIDTH * sizeof(int *));
  boardArray2 = malloc(BOARD_WIDTH * sizeof(int *));

  if (boardArray1 == NULL || boardArray2 == NULL) {
    printf("Boards' columns could not be allocated!\n");
    exit(1);
  }

  for (i = 0; i < BOARD_WIDTH; i++) {
    boardArray1[i] = malloc(BOARD_HEIGHT * sizeof(int));
    boardArray2[i] = malloc(BOARD_HEIGHT * sizeof(int));

    if (boardArray1[i] == NULL || boardArray2[i] == NULL) {
      printf("Boards' row %d could not be allocated!\n", i);
      exit(1);
    }
  }

  srand((unsigned)time(&now));

  for (i = 0; i < BOARD_WIDTH; i++) {
    for (j = 0; j < BOARD_HEIGHT; j++) {
      random = rand() % 101;
      boardArray1[i][j] = random > RANDOM_THREASHOLD ? 1 : 0;
      boardArray2[i][j] = 0;
    }
  }
}

void destoryBoards() {
  int i;
  for (i = 0; i < BOARD_WIDTH; i++) {
    free(boardArray1[i]);
    free(boardArray2[i]);
  }
  free(boardArray1);
  free(boardArray2);
}

int drawBoard(int **currBoard) {
  int c, i, j;

  clear();

  // display boids
  for (i = 0; i < BOARD_WIDTH; i++) {
    for (j = 0; j < BOARD_HEIGHT; j++) {
      mvaddch(i, j, currBoard[i][j] == 1 ? ' ' | A_REVERSE : ' ');
    }
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

int inBounds(int col, int row) {
  return (col >= 0 && col < BOARD_WIDTH && row >= 0 && row < BOARD_HEIGHT);
}

int checkSurroundings(int col, int row, int **currBoard) {
  int currCol = col - 1;
  int currRow = row - 1;
  int i;
  int neighbourCount = 0;
  int colRotation[8] = {1, 1, 0, 0, -1, -1, 0, 0};
  int rowRotation[8] = {0, 0, 1, 1, 0, 0, -1, -1};

  for (i = 0; i < 8; i++) {
    if (inBounds(currCol, currRow))
      neighbourCount += currBoard[currCol][currRow];
    currCol += colRotation[i];
    currRow += rowRotation[i];
  }

  return neighbourCount;
}

void generateBoard(int **currBoard, int **nextBoard) {
  int i, j, neighbours = 0;

  for (i = 0; i < BOARD_WIDTH; i++) {
    for (j = 0; j < BOARD_HEIGHT; j++) {
      neighbours = checkSurroundings(i, j, currBoard);
      if (currBoard[i][j] == 1 && (neighbours == 2 || neighbours == 3))
        nextBoard[i][j] = 1;
      else if (currBoard[i][j] == 0 && neighbours == 3)
        nextBoard[i][j] = 1;
      else
        nextBoard[i][j] = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  int argPtr;
  int kernelCount = 2;
  int outputFlag = 1;
  long long currGen = 1;

  if (argc > 1) {
    argPtr = 1;
    while (argPtr < argc) {
      if (strcmp(argv[argPtr], "-n") == 0) {
        sscanf(argv[argPtr + 1], "%d", &kernelCount);
        argPtr += 2;
      } else if (strcmp(argv[argPtr], "-o") == 0) {
        outputFlag = 0;
        argPtr += 1;
      } else {
        printf("USAGE: %s <-n kernel_count> <-o>\n", argv[0]);
        printf(" kernel_count -the number of kernals to use during processing "
               "(Default 2)\n");
        printf(" -o -whether or not to produce output using ncurses\n");
        exit(1);
      }
    }
  }

  // initialize arrays
  initBoards();

  if (outputFlag) {
    // good place to define ncurses
    initscr();
    noecho();
    cbreak();
    timeout(0);
    curs_set(FALSE);
  }

  if (outputFlag) {
    while (1) {
      int **currBoard = currGen % 2 ? boardArray1 : boardArray2;
      int **nextBoard = currGen % 2 ? boardArray2 : boardArray1;
      if (drawBoard(currBoard) == 1)
        break;
      generateBoard(currBoard, nextBoard);
      currGen++;
    }
  }

  // int i, j;
  // for (i = 0; i < BOARD_WIDTH; i++) {
  //   for (j = 0; j < BOARD_HEIGHT; j++) {
  //     printf("%d", boardArray1[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("\n");

  // generateBoard(boardArray1, boardArray2);

  if (outputFlag) {
    endwin();
  }

  // for (i = 0; i < BOARD_WIDTH; i++) {
  //   for (j = 0; j < BOARD_HEIGHT; j++) {
  //     printf("%d", boardArray2[i][j]);
  //   }
  //   printf("\n");
  // }

  return 0;
}

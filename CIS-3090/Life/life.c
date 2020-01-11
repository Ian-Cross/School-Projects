/*
 * Author: Ian Cross
 * Date: November 14 2019, 16:40
 * Last modified by: Ian
 * Last modified time: November 26th 2019
 * Desc: A file to replicate Conways' game of life in a parallel way using
 * ncurses and OpenCL
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <ncurses.h>
#include <unistd.h>

// OpenCL Specific Defines
#define PROGRAM_FILE "generateBoard.cl"
#define KERNEL_FUNC "generateBoard"

#define CL_TARGET_OPENCL_VERSION 220

#ifdef MAC
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

// Ncurses Defines
#define DELAY 250000
#define RANDOM_THREASHOLD 75

#define BOARD_HEIGHT 24
#define BOARD_WIDTH 24

int *boardArray1;
int *boardArray2;
int kernelCount = 2;

/* Find a GPU or CPU associated with the first available platform */
cl_device_id create_device() {

  cl_platform_id platform;
  cl_device_id dev;
  int err;

  /* Identify a platform */
  err = clGetPlatformIDs(1, &platform, NULL);
  if (err < 0) {
    perror("Couldn't identify a platform");
    exit(1);
  }

  /* Access a device */
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
  if (err == CL_DEVICE_NOT_FOUND) {
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
  }
  if (err < 0) {
    perror("Couldn't access any devices");
    exit(1);
  }

  return dev;
}

/* Create program from a file and compile it */
cl_program build_program(cl_context ctx, cl_device_id dev,
                         const char *filename) {

  cl_program program;
  FILE *program_handle;
  char *program_buffer, *program_log;
  size_t program_size, log_size;
  int err;

  /* Read program file and place content into buffer */
  program_handle = fopen(filename, "r");
  if (program_handle == NULL) {
    perror("Couldn't find the program file");
    exit(1);
  }
  fseek(program_handle, 0, SEEK_END);
  program_size = ftell(program_handle);
  rewind(program_handle);
  program_buffer = (char *)malloc(program_size + 1);
  program_buffer[program_size] = '\0';
  fread(program_buffer, sizeof(char), program_size, program_handle);
  fclose(program_handle);

  /* Create program from file */
  program = clCreateProgramWithSource(ctx, 1, (const char **)&program_buffer,
                                      &program_size, &err);
  if (err < 0) {
    perror("Couldn't create the program");
    exit(1);
  }
  free(program_buffer);

  /* Build program */
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err < 0) {

    /* Find size of log and print to std output */
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 0, NULL,
                          &log_size);
    program_log = (char *)malloc(log_size + 1);
    program_log[log_size] = '\0';
    clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, log_size + 1,
                          program_log, NULL);
    printf("%s\n", program_log);
    free(program_log);
    exit(1);
  }

  return program;
}

void initBoards() {
  time_t now;
  int i, random = 0; // j

  boardArray1 = malloc(BOARD_WIDTH * BOARD_HEIGHT * sizeof(int *));
  boardArray2 = malloc(BOARD_WIDTH * BOARD_HEIGHT * sizeof(int *));

  if (boardArray1 == NULL || boardArray2 == NULL) {
    printf("Boards' columns could not be allocated!\n");
    exit(1);
  }

  // for (i = 0; i < BOARD_WIDTH; i++) {
  //   boardArray1[i] = malloc(BOARD_HEIGHT * sizeof(int));
  //   boardArray2[i] = malloc(BOARD_HEIGHT * sizeof(int));
  //
  //   if (boardArray1[i] == NULL || boardArray2[i] == NULL) {
  //     printf("Boards' row %d could not be allocated!\n", i);
  //     exit(1);
  //   }
  // }

  srand((unsigned)time(&now));

  for (i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
    // for (j = 0; j < BOARD_HEIGHT; j++) {
    random = rand() % 101;
    boardArray1[i] = random > RANDOM_THREASHOLD ? 1 : 0;
    boardArray2[i] = 0;
    // }
  }
}

void destoryBoards() {
  // int i;
  // for (i = 0; i < BOARD_WIDTH; i++) {
  //   free(boardArray1[i]);
  //   free(boardArray2[i]);
  // }
  free(boardArray1);
  free(boardArray2);
}

int drawBoard(int *currBoard) {
  int c, i, j = 0;

  clear();

  // display boids
  for (i = 1; i <= BOARD_WIDTH * BOARD_HEIGHT; i++) {
    mvaddch(j, (i - 1) % BOARD_WIDTH,
            currBoard[i - 1] == 1 ? ' ' | A_REVERSE : ' ');
    if (i % BOARD_WIDTH == 0)
      j++;
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

void orchestrateKernels(cl_device_id device, cl_program program,
                        cl_context context, int *currBoard, int *nextBoard) {

  cl_command_queue queue;
  cl_kernel kernel;

  cl_int err; // i, j,
  size_t local_size = floor(BOARD_WIDTH / kernelCount),
         global_size = BOARD_WIDTH;

  cl_mem input_board, output_board;

  // Create a command queue
  queue = clCreateCommandQueueWithProperties(context, device, 0, &err);
  if (err < 0) {
    perror("Couldn't create a command queue");
    exit(1);
  };

  /* Create a kernel */
  kernel = clCreateKernel(program, KERNEL_FUNC, &err);
  if (err < 0) {
    perror("Couldn't create a kernel");
    exit(1);
  };

  // Create buffer data
  input_board =
      clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                     BOARD_WIDTH * BOARD_HEIGHT * sizeof(int), currBoard, &err);
  output_board =
      clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                     BOARD_WIDTH * BOARD_HEIGHT * sizeof(int), nextBoard, &err);

  if (!input_board || !output_board) {
    perror("Couldn't create device buffers");
    exit(1);
  }

  int temp_width = BOARD_WIDTH;
  int temp_height = BOARD_HEIGHT;

  /* Create kernel arguments */
  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_board);
  err |= clSetKernelArg(kernel, 1, sizeof(cl_int), &temp_width);
  err |= clSetKernelArg(kernel, 2, sizeof(cl_int), &temp_height);
  err |=
      clSetKernelArg(kernel, 3, BOARD_WIDTH * BOARD_HEIGHT * sizeof(int), NULL);
  err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &output_board);
  if (err < 0) {
    perror("Couldn't create a kernel argument");
    exit(1);
  }
  /* Enqueue kernel */
  err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size,
                               &local_size, 0, NULL, NULL);
  if (err < 0) {
    perror("Couldn't enqueue the kernel");
    exit(1);
  }

  /* Read the kernel's output */
  err = clEnqueueReadBuffer(queue, output_board, CL_TRUE, 0,
                            BOARD_WIDTH * BOARD_HEIGHT * sizeof(int), nextBoard,
                            0, NULL, NULL);
  if (err < 0) {
    perror("Couldn't read the buffer");
    exit(1);
  }

  clReleaseKernel(kernel);
  clReleaseMemObject(input_board);
  // clReleaseMemObject(input_buffer);
  clReleaseCommandQueue(queue);

  // somewhere call generateBoard(currBoard,nextBoard)
}

int main(int argc, char *argv[]) {

  /* OpenCL structures */
  cl_device_id device;
  cl_context context;
  cl_program program;
  cl_int err;

  int argPtr;
  int outputFlag = 1;
  long long currGen = 1;
  int i; // j;
  int *currBoard;
  int *nextBoard;

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

  // Create device and context
  device = create_device();
  context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
  if (err < 0) {
    perror("Couldn't create a context");
    exit(1);
  }

  // Build program
  program = build_program(context, device, PROGRAM_FILE);

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
      currBoard = currGen % 2 ? boardArray1 : boardArray2;
      nextBoard = currGen % 2 ? boardArray2 : boardArray1;
      if (drawBoard(currBoard) == 1)
        break;
      orchestrateKernels(device, program, context, currBoard, nextBoard);
      currGen++;
    }
  } else {
    for (i = 0; i < 1; i++) {
      currBoard = currGen % 2 ? boardArray1 : boardArray2;
      nextBoard = currGen % 2 ? boardArray2 : boardArray1;
      orchestrateKernels(device, program, context, currBoard, nextBoard);
      currGen++;
    }
  }

  // for (i = 1; i <= BOARD_WIDTH * BOARD_HEIGHT; i++) {
  //   printf("%d ", nextBoard[i - 1]);
  //   if (i % BOARD_WIDTH == 0)
  //     printf("\n");
  // }
  // printf("\n");

  clReleaseProgram(program);
  clReleaseContext(context);

  if (outputFlag) {
    endwin();
  }

  return 0;
}

/* Serial Implimentation */
/*int inBounds(int col, int row) {
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
*/

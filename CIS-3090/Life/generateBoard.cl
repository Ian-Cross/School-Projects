__kernel void generateBoard(__global int* currBoard,
                            __global int BOARD_WIDTH,
                            __global int BOARD_HEIGHT) {
    int id = get_global_id(0);
    int i, j, n, neighbours = 0, currRow, currCol;
    int colRotation[8] = {1, 1, 0, 0, -1, -1, 0, 0};
    int rowRotation[8] = {0, 0, 1, 1, 0, 0, -1, -1};

    for (i = 0; i < BOARD_WIDTH; i++) {
      for (j = 0; j < BOARD_HEIGHT; j++) {

        currCol = i - 1;
        currRow = j - 1;

        for (n = 0; n < 8; n++) {
          if (currCol >= 0 && currCol < BOARD_WIDTH && currRow >= 0 && currRow < BOARD_HEIGHT)
            neighbours += currBoard[currCol][currRow];
          currCol += colRotation[n];
          currRow += rowRotation[n];
        }
      }
    }
}

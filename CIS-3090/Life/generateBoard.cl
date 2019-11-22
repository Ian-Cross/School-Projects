__kernel void generateBoard(__global int* currBoard,
                            int width,
                            int height,
                            __global int* nextBoard) {
    int row = get_global_id(0);

    for (int i = 0; i < width; i++) {
      int currCol = i - 1;
      int currRow = row - 1;
      int j;
      int neighbours = 0;
      int colRotation[8] = {1, 1, 0, 0, -1, -1, 0, 0};
      int rowRotation[8] = {0, 0, 1, 1, 0, 0, -1, -1};

      for (j = 0; j < 8; j++) {
        if (currCol >= 0 && currCol < width && currRow >= 0 && currRow < height)
          neighbours += currBoard[currCol + currRow * width];
        currCol += colRotation[j];
        currRow += rowRotation[j];
      }

      if (currBoard[row*width + i] == 1 && (neighbours == 2 || neighbours == 3))
        nextBoard[row*width + i] = 1;
      else if (currBoard[row*width + i] == 0 && neighbours == 3)
        nextBoard[row*width + i] = 1;
      else
        nextBoard[row*width + i] = 0;
    }
}

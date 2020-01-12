__kernel void generateBoard(__global int* currBoard,
                            int width,
                            int height,
                            __local int* local_board,
                            __global int* nextBoard) {
    int row = get_global_id(0);

    // printf("%d,%d\n",get_global_id(0),get_local_id(0));

    for (int i = 0; i < width; i++) {
      int currCol = i - 1;
      int currRow = row - 1;
      int neighbours = 0;
      int colRotation[8] = {1, 1, 0, 0, -1, -1, 0, 0};
      int rowRotation[8] = {0, 0, 1, 1, 0, 0, -1, -1};

      for (int j = 0; j < 8; j++) {
        if (currCol >= 0 && currCol < width && currRow >= 0 && currRow < height)
          neighbours += currBoard[currCol + currRow * width];
        currCol += colRotation[j];
        currRow += rowRotation[j];
      }
      int local_row = get_local_id(0);
      if (currBoard[row*width + i] == 1 && (neighbours == 2 || neighbours == 3))
        local_board[local_row*width + i] = 1;
      else if (currBoard[row*width + i] == 0 && neighbours == 3)
        local_board[local_row*width + i] = 1;
      else
        local_board[local_row*width + i] = 0;
    }

    barrier(CLK_LOCAL_MEM_FENCE);

    if(get_local_id(0) == 0) {
      // printf("For kernel %d\n",);
      for (int i = 0; i < get_local_size(0); i++) {
        for (int j = 0; j < width; j++) {
          nextBoard[get_global_id(0)*width + i*width + j] = local_board[i*width + j];
        }
      }
      // printf("%d:%d\n",get_global_size(0),get_local_size(0));
    }
}

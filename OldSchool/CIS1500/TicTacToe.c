#include <stdio.h>
#include <stdlib.h>

showBoard(int BoardGrid[3][3]);

int main (void)
{
    int BoardGrid[3][3];
    int i,j;

    for(i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
		    BoardGrid[i][j] = 0;
		    // printf("%d",BoardGrid[i][j]);
        }

    while (winner == 0)
    {
        showBoard(int BoardGrid[3][3]);
    }

    return 0;
}

showBoard(int BoardGrid[3][3])
{
    
}
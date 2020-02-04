#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PieceStucture
{
    int name;
}Piece;

void showBoard(Piece board[8][8]);
void assignValues(Piece board[8][8]);
int playerMove(Piece board[8][8]);

enum Pieces {Blank, WhitePawn, BlackPawn, WhiteRook, BlackRook, WhiteKnight, BlackKnight, WhiteBishop, BlackBishop, WhiteQueen, BlackQueen, WhiteKing, BlackKing};

int main(int argc, char * argv[])
{
    Piece board[8][8];

    assignValues(board);
    showBoard(board);

    while (!playerMove(board))
    {
        showBoard(board);
    }
    return 0;
}

void showBoard(Piece board[8][8])
{
    printf("       A.   B.   C.   D.   E.   F.   G.   H.  \n");
    for (int x = 0; x < 8; x++)
    {
        printf("     -----------------------------------------\n");
        printf("  %02d ",x+1);
        for (int y = 0; y < 8; y++)
            printf("| %02d ",board[x][y].name);
        printf("|\n");
    }
    printf("     -----------------------------------------\n");
    return;
}

void assignValues(Piece board[8][8])
{
    int y;
    int x;

    for (x = 0; x < 8; x++)
    {
        for (y = 0; y < 8; y++)
        {
            board[x][y].name = Blank;
        }
    }

    for (y = 0; y < 8; y++)
        board[1][y].name = BlackPawn;

    for (y = 0; y < 8; y++)
        board[6][y].name = WhitePawn;

    for (y = 0; y < 8; y+=7)
        board[0][y].name = BlackRook;

    for (y = 0; y < 8; y+=7)
        board[7][y].name = WhiteRook;

    for (y = 1; y < 8; y+=5)
        board[0][y].name = BlackKnight;

    for (y = 1; y < 8; y+=5)
        board[7][y].name = WhiteKnight;

    for (y = 2; y < 8; y+=3)
        board[0][y].name = BlackBishop;

    for (y = 2; y < 8; y+=3)
        board[7][y].name = WhiteBishop;

    board[0][4].name = BlackQueen;
    board[7][3].name = WhiteQueen;
    board[0][3].name = BlackKing;
    board[7][4].name = WhiteKing;

    return;
}

int playerMove(Piece board[8][8])
{
return -1;
}

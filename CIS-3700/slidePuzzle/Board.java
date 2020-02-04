import java.util.*;

enum Move {
  left,
  right,
  up,
  down
}

public class Board extends ObjectPlus {
  public int board[][];
  int goalBoard[][];
  public int blankLoc[];
  int heuristicValue;

  public Board(int[][] initState, int[][] goalState) {
    board = new int[3][3];
    goalBoard = new int[3][3];
    heuristicValue = -1;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board[i][j] = initState[i][j];
        goalBoard[i][j] = goalState[i][j];
        if (initState[i][j] == 0) {
          blankLoc = new int[]{i,j};
        }
      }
    }
  }

  public void showPart(int part) {

  }

  public int getHeuristicValue(Board goalState) {
    if (this.heuristicValue == -1) {
      int value = 0;
      boolean matched = false;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (this.board[i][j] == 0) continue;
          matched = false;
          //find matching val in goal state
          for (int k = 0; k < 3; k++) {
            for (int p = 0; p < 3; p++) {
              if (this.board[i][j] == goalState.board[k][p]){
                value += Math.abs(i-k) + Math.abs(j-p);
                matched = true;
                break;
              }
            }
            if (matched) break;
          }
        }
      }
      this.heuristicValue = value;
      return value;
    } else
      return this.heuristicValue;
  }
  public void show() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == 0) System.out.print(" ");
        else System.out.print(board[i][j]);
      }
      System.out.println();
    }
  }

  public void show(int depth) {
    int heur = this.heuristicValue;
    for (int i = 0; i < 3; i++) {
      for (int k = 0; k < depth; k++) System.out.print("\t");
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == 0) System.out.print(" ");
        else System.out.print(board[i][j]);
      }
      if (i == 0) System.out.println(" g" + depth);
      if (i == 1) System.out.println(" h" + heur);
      if (i == 2) System.out.println(" f" + depth+heur);
    }
  }

  public Boolean isGoal() {
    for (int i = 0; i< 3; i++) {
      for (int j = 0; j < 3; j++) {
        if ( board[i][j] != goalBoard[i][j]) return false;
      }
    }
    return true;
  }

  public Boolean canMove(Move direction) {
    switch (direction) {
      case left:
        if (blankLoc[1] > 0) return true;
        return false;
      case right:
        if (blankLoc[1] < 2) return true;
        return false;
      case up:
        if (blankLoc[0] > 0) return true;
        return false;
      case down:
        if (blankLoc[0] < 2) return true;
        return false;
    }
    return false;
  }

  public Board makeMove(Move direction) {
      Board newBoard = new Board(board,goalBoard);
      int val;
      switch (direction) {
        case left:
          val = board[blankLoc[0]][blankLoc[1]-1];
          newBoard.board[blankLoc[0]][blankLoc[1]-1] = 0;
          newBoard.board[blankLoc[0]][blankLoc[1]] = val;
          newBoard.blankLoc[1]--;
          break;
        case right:
          val = board[blankLoc[0]][blankLoc[1]+1];
          newBoard.board[blankLoc[0]][blankLoc[1]+1] = 0;
          newBoard.board[blankLoc[0]][blankLoc[1]] = val;
          newBoard.blankLoc[1]++;
          break;
        case up:
          val = board[blankLoc[0]-1][blankLoc[1]];
          newBoard.board[blankLoc[0]-1][blankLoc[1]] = 0;
          newBoard.board[blankLoc[0]][blankLoc[1]] = val;
          newBoard.blankLoc[0]--;
          break;
        case down:
          val = board[blankLoc[0]+1][blankLoc[1]];
          newBoard.board[blankLoc[0]+1][blankLoc[1]] = 0;
          newBoard.board[blankLoc[0]][blankLoc[1]] = val;
          newBoard.blankLoc[0]++;
          break;
      }
      return newBoard;
  }
}

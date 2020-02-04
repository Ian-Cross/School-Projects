import java.util.*;

public class PuzzleProblem extends Problem {
  public LinkedList getSuccessor(ObjectPlus currState) {
    LinkedList<Board> successors = new LinkedList<Board>();
    if (currState instanceof Board) {
      Board currBoard = (Board) currState;
      for (Move move : Move.values()) {
        if (currBoard.canMove(move))
          successors.add(currBoard.makeMove(move));
      }
    }
    return successors;
  }

  public boolean isGoalState(ObjectPlus currState) {
    if (currState instanceof Board) {
      Board currBoard = (Board) currState;
      // System.out.println("Is Goal?");
      // Scanner input = new Scanner(System.in);
      // int number = input.nextInt();
      if (currBoard.isGoal()) return true;
    }
    return false;
  }
}

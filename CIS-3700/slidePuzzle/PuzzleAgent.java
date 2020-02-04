import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class PuzzleAgent extends SearchAgent {
  public int[][][] readStateFile(String filepath) {
    int[][][] states = new int[2][3][3];
    String[] readState = new String[3];
    int stateCount = 0;
    try {
        File file = new File(filepath);
        BufferedReader buffer = new BufferedReader(new FileReader(file));

        String readLine = "";
        while ((readLine = buffer.readLine()) != null) {
            if (readLine.equals("Initial state:") || readLine.equals("Goal state:")) {
              for (int i = 0; i < 3; i++) {
                 readState = buffer.readLine().trim().split(" ");
                 for (int j = 0; j < 3; j++) {
                   try{
                    states[stateCount][i][j] = Integer.parseInt(readState[j]);
                  } catch (NumberFormatException nfe) {
                    System.out.println(nfe.getMessage());
                    System.exit(1);
                  }
                 }
              }
              stateCount++;
            }
        }
    } catch (IOException e) {
        System.out.println(e.toString());
        System.exit(1);
    }
    return states;
  }

  public void showSolution() {

  }

  public void showTree() {
    System.out.println("Search tree size: " + this.tree.size());
    System.out.println("g(), h(), and f() values are shown for each node");
    printTree(this.tree.getFirst());
  }

  private void printTree(Node currNode) {
    Board b = (Board) currNode.getState();
    System.out.println();
    b.show(currNode.depth);
    if (currNode.child != null) {
      for (int i = 0; i < currNode.child.length; i++) {
        printTree(currNode.child[i]);
      }
    }
  }

  public void insertFringe(Node node, LinkedList<Node> fringe) {
    int nodeEval = 0;
    int fringeEval = 0;

    //build the evaluation function
    Board b = (Board) node.getState();
    nodeEval = node.depth + b.getHeuristicValue((Board) this.problem.getGoalState());
    System.out.println(nodeEval);

    //find spot in fringe to insert
    if (fringe.size() == 0) {
      fringe.add(node);
    } else {
      for (int j = 0; j < fringe.size(); j++) {
        Node fNode = (Node) fringe.get(j);
        Board fBoard = (Board) fNode.getState();
        fringeEval = fNode.depth + fBoard.getHeuristicValue((Board) this.problem.getGoalState());
        if (nodeEval < fringeEval) {
          fringe.add(j,node);
          break;
        }
        fringeEval = 0;
      }
    }
  }

  public static void main(String argv[]) {
    PuzzleAgent agent = new PuzzleAgent();
    PuzzleProblem problem = new PuzzleProblem();

    //Read in the initial and goal states
    int states[][][] = agent.readStateFile(argv[0]);
    Board initialState = new Board(states[0],states[1]);
    Board goalState = new Board(states[1],states[1]);

    //set the states to the problem and give the problem to the agent
    problem.setInitialState(initialState);
    problem.setGoalState(goalState);
    agent.setProblem(problem);

    agent.search();

    agent.showTree();

    System.out.println();
    System.out.println("Solution to 8-puzzle:");
    for (int i = 0; i < agent.solution.size(); i++) {
      Node n = (Node) agent.solution.get(i);
      n.show();
    }

    // agent.puzzleTree.add(new Node(agent.puzzle.getInitialState()));
    // insertFringe(agent.puzzleTree.getFirst(), agent.puzzleTree);

    // Object childBoards[] = children.toArray();
    // for (Object childBoard : childBoards) {
    //   Board curBoard = (Board) childBoard;
    //   curBoard.show();
    //   System.out.println();
    // }
    // System.out.println();
    // goalState.show();
    // if (test.isGoalState(goalState)) System.out.println("Goal!!!");
  }
}

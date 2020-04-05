import java.util.ArrayList;

public class Node {
  public String label;
  public Node parent;
  public ArrayList<Node> children;
  public String link;
  public String connector;

  public Node(String label) {
    this.label = label;
    this.parent = null;
    this.children = new ArrayList<>();
    this.link = null;
  }

  public void print() {
    printTree(0);
  }

  public void printTree(int depth) {
    String offset = "";
    for (int i = 0; i < depth-1; i++) {
      offset += "\t";
    }

    if (this.parent == null) {
      System.out.println("\nPrinting Decision Tree:");
      System.out.println(this.label + "");
    } else if (this.children.size() == 0) {
      System.out.println(offset + "| " + this.link);
      System.out.println(offset + "------> [" + this.label + "]");
    } else {
      System.out.println(offset + "| " + this.link);
      System.out.println(offset + "------> " + this.label + "");
    }

    if (this.children != null && this.children.size() > 0) {
      for (Node node : this.children) {
        node.printTree(depth + 1);
      }
    }
  }
}

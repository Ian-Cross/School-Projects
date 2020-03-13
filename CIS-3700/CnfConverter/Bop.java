import java.io.*;

public class Bop {
  public static final String NOT = "~";
  public static final String AND = "^";
  public static final String OR = "v";
  public static final String IMPLY = "=>";
  public static final String IFF = "<->";
  String op;
  public Bop (String bop) {
      this.op = bop;
  }

  public static Boolean isBop(String bop) {
    if (bop.equals(NOT) ||
        bop.equals(AND) ||
        bop.equals(OR) ||
        bop.equals(IMPLY) ||
        bop.equals(IFF)) {
          return true;
    }
    return false;
  }

  public String toString() {
    return this.op;
  }
}

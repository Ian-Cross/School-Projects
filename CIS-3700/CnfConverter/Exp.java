import java.io.*;


public class Exp {
  Bop bop;
  String lhs;
  String rhs;
  public Exp (Bop bop,String lhs, String rhs) {
    this.bop = bop;
    this.lhs = lhs.trim();
    this.rhs = rhs.trim();
  }

  public static Boolean isLiteral(String s) {
    if (s.length() == 1 && !Bop.isBop(s))
      return true;

    if (s.length() == 3 && s.charAt(0) == '(' &&
        s.charAt(s.length()-1) == ')' && !Bop.isBop(s))
          return true;

    return false;
  }

  public String toString() {
    // if (this.bop.op == Bop.NOT) {
    //   return this.bop.toString() + this.lhs;
    // }
    if (this.rhs == "")
      return this.bop.toString() + " " + this.lhs;
    return this.lhs + " " + this.bop.toString() + " " + this.rhs;
    // return "\n\tp: " + this.lhs
    // + "\n\tbop: " + this.bop.toString() + "\n\tq: " + this.rhs;
  }
}

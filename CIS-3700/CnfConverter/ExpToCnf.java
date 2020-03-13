import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.util.regex.Pattern;

public class ExpToCnf {

  public static Boolean isBalanced(Exp exp) {
    int count = 0;
    for (int i = 0, n = exp.lhs.length(); i < n; i++) {
      if (exp.lhs.charAt(i) == ')') count--;
      if (exp.lhs.charAt(i) == '(') count++;
      if (count < 0) return false;
    }

    if (count != 0) return false;

    for (int i = 0, n = exp.rhs.length(); i < n; i++) {
      if (exp.rhs.charAt(i) == ')') count--;
      if (exp.rhs.charAt(i) == '(') count++;
      if (count < 0) return false;
    }

    if (count != 0) return false;
    return true;
  }

  public static String removeOuterParen(String str,String pastStr) {
  	int currDepth = 0;
    int outer = 0;

    if (str.charAt(0) != '(') return str;
    else outer = 1;

  	for(int i = 0, n = str.length(); i < n; i++) {
  		if(str.charAt(i) == '(')
        currDepth += 1;
  		if (str.charAt(i) == ')') {
        if (i == n-1 && outer == 1 && currDepth == 1) {
          str = str.substring(1,n-1);
        } else {
          currDepth -= 1;
        }
      }
      if (currDepth == 0 && outer == 1) outer = 0;
  	}
    if (str.equals(pastStr))
      return str;
    else
      return removeOuterParen(str, str);
  }

  public static Exp getBalencedSplit(String exp) {
    ArrayList<Exp> splits = new ArrayList<Exp>();
    exp = removeOuterParen(exp,"");
    String exps[] = exp.split(" ");
    // for (int i = 0, n = exps.length; i < n ;i++) System.out.println(exps[i]);
    for (int i = 0, n = exps.length; i < n; i++) {
      switch (exps[i]) {
        case Bop.AND:
          splits.add( new Exp (
                        new Bop(Bop.AND),
                        String.join(" ",Arrays.copyOfRange(exps,0,i)),
                        String.join(" ",Arrays.copyOfRange(exps,i+1,n))
                      )
                    );
          break;
        case Bop.OR:
          splits.add( new Exp (
                        new Bop(Bop.OR),
                        String.join(" ",Arrays.copyOfRange(exps,0,i)),
                        String.join(" ",Arrays.copyOfRange(exps,i+1,n))
                      )
                    );
          break;
        case Bop.IMPLY:
          splits.add( new Exp (
                        new Bop(Bop.IMPLY),
                        String.join(" ",Arrays.copyOfRange(exps,0,i)),
                        String.join(" ",Arrays.copyOfRange(exps,i+1,n))
                      )
                    );
          break;
        case Bop.IFF:
          splits.add( new Exp (
                        new Bop(Bop.IFF),
                        String.join(" ",Arrays.copyOfRange(exps,0,i)),
                        String.join(" ",Arrays.copyOfRange(exps,i+1,n))
                      )
                    );
          break;
        case Bop.NOT:
        default:
          continue;
      }
    }
    Exp balencedSplit = null;
    for (int i = 0, n = splits.size(); i < n; i++) {
      Exp currExp = splits.get(i);
      if (isBalanced(currExp)) balencedSplit = currExp;
    }

    if (balencedSplit == null) {
      if (Bop.NOT.equals(exp.substring(0,1)) &&
          exp.charAt(1) == '(' &&
          exp.charAt(exp.length()-1) == ')') {
            return new Exp( new Bop(Bop.NOT),exp.substring(1),"");
      }
    }

    if (balencedSplit == null) {
      System.out.println("A balenced break could not be found");
      System.exit(1);
    }
    return balencedSplit;
  }

  public static String getCNF(String s, int depth) {
    s = removeOuterParen(s,"");

    // Rule 1
    if (Exp.isLiteral(s)) {
      System.out.println("Convert: " + s);

      if (s.charAt(0) == '(' && s.charAt(s.length()-1) == ')')
        s = s.substring(1,s.length()-1);

      System.out.println("\tReturn: " + s);

      return s.trim();
    }
    String content = null;
    //Parse S to (bop,p, and q)
    Exp exp = getBalencedSplit(s.trim());

    System.out.println("Convert: " + exp);

    if (exp.bop.op.equals(Bop.NOT)) {

      if (Exp.isLiteral(exp.lhs)) { // Rule 2.1
        content = Bop.NOT + exp.lhs.substring(1,2);
        System.out.println("\tReturn:" + content);
        return content;
      }

      Exp negExp = getBalencedSplit(exp.lhs);

      if (negExp.bop.op.equals(Bop.NOT)) { // Rule 2.2
        content = getCNF(negExp.lhs,depth+1);

      } else if (negExp.bop.op.equals(Bop.AND)) { //Rule 3
        content =  Bop.NOT + "(" + negExp.lhs + ") " + Bop.OR + " " + Bop.NOT + "("+ negExp.rhs + ")";

      } else if (negExp.bop.op.equals(Bop.OR)) { //Rule 4
        content = Bop.NOT + "(" + negExp.lhs + ") " + Bop.AND + " " + Bop.NOT + "("+ negExp.rhs + ")";

      } else { //Rule 8
        content = Bop.NOT + "("+ getCNF(exp.lhs,depth+1) + ")";
      }

    } else if (exp.bop.op.equals(Bop.AND)) { //Rule 5
      content = getCNF(exp.lhs, depth+1) + " " + Bop.AND + " " + getCNF(exp.rhs, depth+1);

    } else if (exp.bop.op.equals(Bop.OR)) { //Rule 9
      String X[] = getCNF("(" + exp.lhs + ")",depth+1).split(Pattern.quote("^"));
      String Y[] = getCNF("(" + exp.rhs + ")",depth+1).split(Pattern.quote("^"));
      content = "";
      for (int i = 0, x = X.length; i < x; i++) {
        for (int j = 0, y = Y.length; j < y; j++) {
          content += "((" + X[i] + ") " + Bop.OR + " (" + Y[j] + "))";
          content += " " + Bop.AND + " ";
        }
      }
      content = content.substring(0,content.length()-3);

    } else if (exp.bop.op.equals(Bop.IMPLY)) { //Rule 6
      content = getCNF("(" + Bop.NOT + "(" + exp.lhs + ") " + Bop.OR + " " + exp.rhs + ")", depth+1);

    } else if (exp.bop.op.equals(Bop.IFF)) { //Rule 7
      content = getCNF("(("
                          + exp.lhs + " " + Bop.AND + " " + exp.rhs +
                        ") "
                        + Bop.OR +
                        " ("
                          + Bop.NOT + "(" + exp.lhs + ") "
                          + Bop.AND + " "
                          + Bop.NOT + "(" + exp.rhs + ")"
                        +"))", depth+1);
    };

    System.out.println("\tReturn: " + content);
    System.out.println();
    return content;
  }

  public static void main(String[] args) throws IOException{
    FileWriter outfile = null;
    Scanner infile = null;
    File file = null;
    try {
      file = new File(args[0]);
      infile = new Scanner(file);
      outfile = new FileWriter(args[1]);

      String data = "";
      while (infile.hasNextLine()) {
        data = infile.nextLine();

        String CNF = getCNF("(" + data + ")",0);
        System.out.println();
        System.out.println("Exp: " + data);
        System.out.println("CNF: " + CNF);
        System.out.println();
        System.out.println();
      }



    } catch (FileNotFoundException e) {
      System.out.println("File not found exception:");
      e.printStackTrace();
    } catch (IOException e) {
      System.out.println("IO exception:");
      e.printStackTrace();
    } finally {
      infile.close();
      outfile.close();
    }
  }
}

import java.io.InputStreamReader;
import java.util.Arrays;

public class Scanner {
  private Lexer scanner = null;

  public Scanner( Lexer lexer ) {
    scanner = lexer;
  }

  public Token getNextToken() throws java.io.IOException {
    return scanner.yylex();
  }

  public static void separateHyphen (String tok, Boolean space) {
    if(tok.matches("[a-zA-Z0-9]+-[a-zA-Z0-9]+")) {
      System.out.print(tok + (space ? " " : "") );
    } else if(tok.matches("[a-zA-Z0-9]+-[a-zA-Z0-9][a-zA-Z0-9]?-[a-zA-Z0-9]+")) {
      System.out.print(tok + (space ? " " : ""));
    } else if (tok.contains("-")) {
      String[] tokens = tok.split("((?<=-)|(?=-))");
      for (String token : tokens) {
        System.out.print(token + " ");
      }
    } else {
      System.out.print(tok + (space ? " " : ""));
    }
  }

  public static void separateApostrophe (String tok) {
    if(tok.matches("[a-zA-Z0-9-]+\'[a-zA-Z0-9-]+")) {
      String[] tokens = tok.split("((?<=\')|(?=\'))");
      if (tokens[2].toUpperCase().equals("S")) {
        separateHyphen(tokens[0],false);
        System.out.print(tokens[1] + tokens[2] + " ");
      } else if (tokens[0].length() == 1) {
        System.out.print(tokens[0] + tokens[1]);
        separateHyphen(tokens[2],true);
      } else {
        for (String token : tokens) {
          separateHyphen(token,true);
        }
      }
    } else if (tok.matches("[a-zA-Z0-9-]\'[a-zA-Z0-9-]+\'s")) {
      String[] tokens = tok.split("((?<=\')|(?=\'))");
      System.out.print(tokens[0] + tokens[1]);
      separateHyphen(tokens[2],false);
      System.out.print(tokens[3] + tokens[4] +  " ");
    } else {
      String[] tokens = tok.split("((?<=\')|(?=\'))");
      for (String token : tokens) {
        separateHyphen(token,true);
      }
    }
  }

  public static void main(String argv[]) {
    try {
      Scanner scanner = new Scanner(new Lexer(new InputStreamReader(System.in)));
      Token tok = null;
      while( (tok=scanner.getNextToken()) != null )
        if (tok.m_type == Token.APOS) {
          separateApostrophe(tok.m_value);
        } else if (tok.m_type == Token.HYPH) {
          separateHyphen(tok.m_value,true);
        } else if (tok.m_type == Token.NEW) {
          System.out.print(tok);
        } else {
          System.out.print(tok + " ");
        }
    }
    catch (Exception e) {
      System.out.println("Unexpected exception:");
      e.printStackTrace();
    }
  }
}

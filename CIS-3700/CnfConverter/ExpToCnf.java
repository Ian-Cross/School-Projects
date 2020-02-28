import java.io.*;

public class ExpToCnf {
  public static void main(String[] args) throws IOException{
    FileInputStream infile = null;
    FileOutputStream outfile = null;

    try {
      infile = new FileInputStream(args[0]);
      outfile = new FileOutputStream(args[1]);

      int c;
      while (( c = infile.read()) != -1) {
        outfile.write(c);
      }
    } catch (Exception e) {
      System.out.println("Unexpected exception:");
      e.printStackTrace();
    } finally {
      if (infile != null) infile.close();
      if (outfile != null) outfile.close();
    }
  }
}

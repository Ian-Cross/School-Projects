import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class DTLearn {
  public static void updateDocumentCounts() {
  }

  public static void main(String args[]) throws Exception {
    Scheme scheme = new Scheme(args[0]);

    Sample sample = new Sample(args[1],scheme);

    System.out.println(scheme);
    System.out.println(sample);

    
  }
}

import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class UTIL {
  public static ArrayList<String> readFile(String filename) throws Exception {
    ArrayList<String> data = new ArrayList();
    try {
      File myObj = new File(filename);
      Scanner myReader = new Scanner(myObj);
      while (myReader.hasNextLine()) {
        data.add(myReader.nextLine());
      }
      myReader.close();
    } catch (FileNotFoundException e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }
    return data;
  }
}

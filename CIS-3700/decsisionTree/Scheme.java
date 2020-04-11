import java.util.ArrayList;
import java.io.FileNotFoundException;

public class Scheme {
  public Attribute func;
  public ArrayList<Attribute> attributes;

  public Scheme(String schemeFileName) {
    ArrayList <String> data = loadSchemeFile(schemeFileName);
    if (data == null) {
      System.out.println("Scemefile was empty.");
      System.exit(1);
    }
    ArrayList<Attribute> attributes = getAttributes(data);
    this.func = attributes.remove(attributes.size()-1);
    this.attributes = attributes;
  }

  public ArrayList<String> loadSchemeFile(String schemeFileName) {
    try {
      return UTIL.readFile(schemeFileName);
    } catch (Exception e) {
      System.out.println("Scheme file could not be found, please try again");
      System.exit(1);
    }
    return null;
  }

  public ArrayList<Attribute> getAttributes(ArrayList<String> fileData) {
    ArrayList <Attribute> attributes = new ArrayList<>();
    for (int i = 0; i < fileData.size(); i++) {
      if (i == 0) continue;
      if(fileData.get(i).equals("")) continue;

      ArrayList <String> values = new ArrayList();
      for(String j :fileData.get(i+2).split(" "))
        values.add(j);

      Attribute newAtt = new Attribute(fileData.get(i),values);
      attributes.add(newAtt);
      i+=3;
    }

    return attributes;
  }

  public String toString() {
    return "Attributes: " + this.attributes.toString() + "\n" + this.func.toString();
  }
}

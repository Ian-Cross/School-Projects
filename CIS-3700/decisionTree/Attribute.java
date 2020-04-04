import java.util.ArrayList;

public class Attribute {
  public String name;
  public ArrayList<String> values;

  public Attribute(String name, ArrayList<String> values) {
    this.name = name;
    this.values = values;
  }

  public String toString() {
    return this.name + ": " + values.toString();
  }
}

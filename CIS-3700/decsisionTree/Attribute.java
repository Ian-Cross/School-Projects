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

  public Boolean equals(Attribute attribute) {
    if (this.name != attribute.name) return false;
    if (this.values.size() != attribute.values.size()) return false;
    for (int i = 0; i < values.size(); i++) {
      if (!this.values.get(i).equals(attribute.values.get(i))) return false;
    }
    return true;
  }
}

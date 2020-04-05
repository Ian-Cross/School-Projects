import java.util.ArrayList;

public class Example {
  public ArrayList<String> values;

  public Example(ArrayList<String> values) {
    this.values = values;
  }

  public String funcValue() {
    return this.values.get(this.values.size()-1);
  }

  public String toString() {
    return values.toString();
  }

  public Example clone() {
    return new Example(this.values);
  }
}

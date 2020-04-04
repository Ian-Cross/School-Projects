import java.util.ArrayList;

public class Sample {
  ArrayList<Example> examples;

  public Sample(String sampleFileName, Scheme scheme) {
    ArrayList <String> examples = loadSampleFile(sampleFileName);
    if (examples == null) {
      System.out.println("The sample data file is empty, please try again");
      System.exit(1);
    }

    this.examples = getExamples(examples,scheme);
  }

  public void getInfo() {

  }
  public void getRMD() {

  }
  public void getAttribute() {

  }

  public ArrayList<Example> getExamples(ArrayList<String> data, Scheme scheme) {
    ArrayList<Example> examples = new ArrayList<>();
    String attributes[] = data.get(0).split(" ");
    for (int i = 0; i < scheme.attributes.size(); i++) {
      if (!attributes[i].equals(scheme.attributes.get(i).name)) {
        System.out.println("Scheme and Sample file to not match up.");
        System.exit(1);
      }
    }

    data.remove(0);
    for(String i: data) {
      ArrayList<Integer> intValues = new ArrayList();
      String strValues[] = i.split(" ");
      for (int j = 0; j < strValues.length; j++) {
        if (j == strValues.length-1) {
          intValues.add(scheme.func.values.indexOf(strValues[j]));
        } else {
          intValues.add(scheme.attributes.get(j).values.indexOf(strValues[j]));
        }
      }
      examples.add(new Example(intValues));
    }

    return examples;
  }

  public ArrayList<String> loadSampleFile(String sampleFileName) {
    try {
      return UTIL.readFile(sampleFileName);
    } catch (Exception e) {
      System.out.println("Sample data file could not be found, please try again");
      System.exit(1);
    }
    return null;
  }

  public String toString() {
    return examples.toString();
  }
}

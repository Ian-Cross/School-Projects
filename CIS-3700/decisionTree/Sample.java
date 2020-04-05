import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Set;
import java.util.Iterator;

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

  public double getInfo(ArrayList<Example> examples) {
    if (examples.size() == 0) return 0.0;

    Hashtable<String, Integer> values = new Hashtable<String, Integer>();
    for (Example example: examples) {
      if (values.containsKey(example.funcValue())) {
        int currCount = values.get(example.funcValue());
        values.replace(example.funcValue(),currCount,currCount+1);
      } else {
        values.put(example.funcValue(),1);
      }
    }

    double infoGain = 0.0;
    Set<String> keys = values.keySet();
    for(String key: keys) {
        double pi = (double)values.get(key) / (double)examples.size();
        if (pi != 0.0) {
            infoGain += pi * -Math.log(pi)/Math.log(2);
        }
    }

    return infoGain;
  }

  public double getRMD(Attribute attribute, ArrayList<Example> examples, Scheme scheme) {
    int size = examples.size();
    int valuesCount = attribute.values.size();
    int attributeIndex = scheme.attributes.indexOf(attribute);

    Hashtable<String, ArrayList<Example>> subGroups = new Hashtable<String, ArrayList<Example>>();

    for (Example example : examples) {
      String i = example.values.get(attributeIndex);
      if (subGroups.containsKey(i)) {
        ArrayList<Example> currGroup = subGroups.get(i);
        ArrayList<Example> newGroup = new ArrayList<>();
        Iterator<Example> iterator = currGroup.iterator();

        while(iterator.hasNext()) {
            newGroup.add((Example)iterator.next().clone());
        }
        newGroup.add(example);
        subGroups.replace(i,currGroup,newGroup);
      } else {
        ArrayList<Example> group = new ArrayList<>();
        group.add(example);
        subGroups.put(i,group);
      }
    }

    int[] subCounts = new int[valuesCount];
    Set<String> keys = subGroups.keySet();
    int i = 0;
    for (String key: keys) {
        subCounts[i] = subGroups.get(key).size();
        i++;
    }

    double remainder = 0.0;
    i = 0;
    for (String key: keys) {
        double pr = (double)subCounts[i] / (double)size;
        double infoGain = getInfo(subGroups.get(key));
        remainder += pr * infoGain;
        i++;
    }
    return remainder;
  }

  public Attribute getAttribute( ArrayList<Attribute> attributes, ArrayList<Example> examples, Scheme scheme) {
    double info = getInfo(examples);
    double maxGain = -1.0;
    Attribute bestAttribute = null;

    for (Attribute attribute : attributes) {
        double remainder = getRMD(attribute, examples, scheme);
        double gain = info - remainder;
        System.out.println("Test " + attribute.name + ": info=" + Math.round(info * 10000.0)/10000.0 + " rmd=" + Math.round(remainder * 10000.0)/10000.0 + " gain = " + Math.round(gain * 10000.0)/10000.0);
        if (gain > maxGain) {
            maxGain = gain;
            bestAttribute = attribute;
        }
    }
    System.out.println("\tSelect attribute " + bestAttribute.name);
    return bestAttribute;
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
      ArrayList<String> values = new ArrayList();
      String strValues[] = i.split(" ");
      for (int j = 0; j < strValues.length; j++) {
        values.add(strValues[j]);
      }
      examples.add(new Example(values));
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

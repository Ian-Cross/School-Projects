import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Set;

public class DTLearn {
  public static Scheme scheme;
  public static Sample sample;
  public static void main(String args[]) throws Exception {
    scheme = new Scheme(args[0]);
    sample = new Sample(args[1],scheme);

    // System.out.println(scheme);
    // System.out.println(sample);

    Node tree = learnDecisionTree(sample.examples,scheme.attributes,null);
    tree.print();
  }

  public static Node learnDecisionTree(ArrayList<Example> examples, ArrayList<Attribute> attributes , String majorityLabel) {
    // if examples is empty return node labeled with majorityLabel
    if (examples.size() == 0)
      return new Node(majorityLabel);

    // if all examples has the same func value, return node labeled with that value
    String q = examples.get(0).funcValue();
    Boolean flag = false;
    for (Example example : examples) {
      if (!example.funcValue().equals(q)) {
        flag = true;
        break;
      }
    }
    if (!flag)
      return new Node(q);

    // if attributes is empty return node labeled it majorityLabel(examples)
    if (attributes.size() == 0)
      return new Node(majorityLabel(examples));

    // b = getAttribute(attibutes, examples)
    Attribute currAttribute = sample.getAttribute(attributes,examples,scheme);
    Integer attributeIndex = scheme.attributes.indexOf(currAttribute);
    // tr = new tree node with root b only
    Node node = new Node(currAttribute.name);
    // m = majorityLabel(examples)
    String majority = majorityLabel(examples);
    // for each v of b // iterate each value of attribute b
    for (String value: currAttribute.values) {
      // subg = examples in examples with value v
      ArrayList<Example> subExamples = getExamplesByValue(examples, value, attributeIndex);
      // subtr = learnDecisionTree(subg,attibutes - b, m)
      Node subTree = learnDecisionTree(subExamples, getSubAttributes(attributes,currAttribute), majority);
      // link node b to root of subtr and label by the link v
      subTree.link = value;
      subTree.parent = node;
      node.children.add(subTree);
    }
    return node;
  }

  public static ArrayList<Attribute> getSubAttributes(ArrayList<Attribute> attributes, Attribute currAttribute) {
    ArrayList <Attribute> newAttributes = new ArrayList<>();

    for (Attribute attribute : attributes) {
      if (attribute.equals(currAttribute)) continue;
      newAttributes.add(attribute);
    }
    return newAttributes;
  }

  public static ArrayList<Example> getExamplesByValue(ArrayList<Example> examples, String value, Integer attributeIndex) {
    ArrayList <Example> newExamples = new ArrayList<>();

    for (Example example: examples) {
      if (example.values.get(attributeIndex).equals(value)) newExamples.add(example);
    }

    return newExamples;
  }

  public static String majorityLabel(ArrayList<Example> examples) {
    Hashtable<String, Integer> values = new Hashtable<String, Integer>();
    for (Example i: examples) {
      if (values.containsKey(i.funcValue())) {
        int currCount = values.get(i.funcValue());
        values.replace(i.funcValue(),currCount,currCount+1);
      } else {
        values.put(i.funcValue(),1);
      }
    }
    String majority = "";
    Integer majorityCount = 0;
    Set<String> keys = values.keySet();
    for(String key: keys) {
        if (values.get(key) > majorityCount) {
          majority = key;
          majorityCount = values.get(key);
        }
    }
    return majority;
  }
}

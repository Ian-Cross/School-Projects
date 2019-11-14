import java.util.Scanner;
import java.util.TreeMap;
import java.util.Set;
import java.util.Iterator;

public class TermDocument {
  public Integer documentId;
  public Integer termFrequency;

  public TermDocument (Integer id) {
    this.documentId = id;
    this.termFrequency = 0;
  }

  public void setDocumentId(Integer id) {
    this.documentId = id;
  }

  public void addTermFrequency() {
    this.termFrequency++;
  }
}

public class TreeMap {

  public static void main(String args[]) {
    //ArrayList for did and tf
    List<TermDocument> terms = new ArrayList<>();
    //TreeMap for string-term pairs
    TreeMap<String, terms> map = new TreeMap<String, terms>();

    //load an input file into the TreeMap
    Scanner input = new Scanner(args[0]);
    while (input.hasNextLine()) {
      String line = input.nextLine();
      String[] tokens = line.split("[ \t]+");
      for (int i = 0; i < tokens.length; i++) {

        // update relevant tokens on TreeMap
        if (map.containsKey(tokens[i])) {
          ArrayList documentList = map.get(tokens[i]);
          TermDocument lastDoc = documentList.get(documentList.size() - 1);
          if (document.getID == currDoc) {
            document.addTermFrequency();
          } else {

          }
        } else {
          map.put(tokens[i], new TermDocument(currDoc));
        }
      }
    }
    // printMap(map,args[1]);
  }

  public static void printMap(TreeMap map, String outputFolder) {
    // Allow for an output folder to be supplied but ignored if not included
    if (outputFolder == null)
      outputFolder = "";
    // display the TreeMap alphabetically
    // Set<String> keys = map.keySet();
    // Iterator<String> iter = keys.iterator();
    // System.out.println("*** Total entries: " + keys.size());
    // while (iter.hasNext()) {
    //   String key = iter.next();
    //   System.out.println(key + " occurs " + map.get(key));
    // }
  }
}

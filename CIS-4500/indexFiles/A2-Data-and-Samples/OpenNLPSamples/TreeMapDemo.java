import java.util.Scanner;
import java.util.TreeMap;
import java.util.Set;
import java.util.Iterator;

public class TreeMapDemo {

   public static void main(String args[]) {     
      //TreeMap for string-integer pairs 
      TreeMap<String, Integer> map = new TreeMap<String, Integer>();

      //load an input file into the TreeMap
      Scanner input = new Scanner(System.in);
      while (input.hasNextLine()) {
        String line = input.nextLine();
        String[] tokens = line.split("[ \t]+");
        for (int i = 0; i < tokens.length; i++) {
          // filter out irrelevant tokens
          if (tokens[i].matches("\\([0-9]+\\)"))
             continue;
          // update relevant tokens on TreeMap
          if (map.containsKey(tokens[i])) 
             map.put(tokens[i], map.get(tokens[i])+1);
          else
             map.put(tokens[i], 1);
        }
      }

      // display the TreeMap alphabetically
      Set<String> keys = map.keySet();
      Iterator<String> iter = keys.iterator();
      System.out.println("*** Total entries: " + keys.size());
      while (iter.hasNext()) {
        String key = iter.next();
        System.out.println(key + " occurs " + map.get(key));
      } 
   } 
}      


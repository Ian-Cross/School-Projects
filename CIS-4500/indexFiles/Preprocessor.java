import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import opennlp.tools.stemmer.PorterStemmer;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileWriter;

public class Preprocessor {

  public static BufferedReader getReader(String file) throws Exception {
    try {
      BufferedReader reader = new BufferedReader(new FileReader(file));
      return reader;
    } catch (IOException e) {
      e.printStackTrace();
    }
    return null;
  }

  public static FileWriter getWriter(String file) throws Exception {
    try {
      FileWriter writer = new FileWriter(file);
      return writer;
    } catch (Exception e) {
      e.printStackTrace();
    }
    return null;
  }

  public static List<String> buildStopWords(String file) throws Exception {
    List<String> stopwords = new ArrayList<>();
    BufferedReader stopFile = getReader(file);
    String line = stopFile.readLine();
    while (line != null) {
      stopwords.add(line);
      line = stopFile.readLine();
    }
    stopFile.close();
    return stopwords;
  }

  public static void main(String args[]) throws Exception{
    BufferedReader inputFile = getReader(args[0]);
    List<String> stopWords = buildStopWords(args[1]);
    FileWriter outputFile = getWriter(args[2]);
    PorterStemmer stemmer = new PorterStemmer();

    if (inputFile == null || outputFile == null)
      throw new IOException("Please include input and output files as arguments");
    String line = inputFile.readLine();
    while (line != null) {
      String[] tokens = line.split("[ \t]+");
      String token;

      for (int i = 0; i < tokens.length; i++) {
        Boolean notStop = true;
        token = tokens[i].toLowerCase();
        //trim out numbers
        if (!token.matches("[-|+]?[0-9]+ | [-|+]?[0-9]*.[0-9]+")){
            //trim out all punctuation
            if (!token.matches("[\\.\\?\\!:,-;'$\"\\(\\)\\/]+")) {
              //filter out stop words
              for (String stop : stopWords) {
                if (stop.equals(token)){
                  notStop = false;
                  break;
                }
              }
              if (notStop == true) {
                outputFile.write(" " + stemmer.stem(token));
              }
            }
        }
      }
      outputFile.write("\n");
      line = inputFile.readLine();
    }
    inputFile.close();
    outputFile.close();
  }
}

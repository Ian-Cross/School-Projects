import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;

import opennlp.tools.sentdetect.SentenceDetectorME;
import opennlp.tools.sentdetect.SentenceModel;

public class SentenceSplitter {

  public final static String[] LABELS = {"$DOC", "$TITLE", "TEXT"};

  public static String breakLabels(String text) {
    for (String label : LABELS) {
      if (text.contains(label)) {
        return "\n" + text + (label == LABELS[0] ? "" : "\n");
      }
    }
    return text + " ";
  }

  public static String readString() throws Exception {
     BufferedReader buf = new BufferedReader(new InputStreamReader(System.in));
     StringBuilder sb = new StringBuilder();
     String line = buf.readLine();
     while( line != null ) {
       sb.append(breakLabels(line));
       line = buf.readLine();
     }
     buf.close();
     return sb.toString();
  }

  public static void main(String[] args) throws Exception {
    //Load sentence detector model
    InputStream modelData = new FileInputStream("OpenNLP_models/en-sent.bin");
    SentenceModel model = new SentenceModel(modelData);

    //Instantiate SentenceDetectorME
    SentenceDetectorME detector = new SentenceDetectorME(model);

    String fileBody = readString();
    String labels = breakLabels(fileBody);

    //Split input into sentences
    String sentences[] = detector.sentDetect(fileBody);

    //Print the sentences
    for(String sent : sentences)
      System.out.println(sent);
  }
}

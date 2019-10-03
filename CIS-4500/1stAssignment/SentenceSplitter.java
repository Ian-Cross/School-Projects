import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;

import opennlp.tools.sentdetect.SentenceDetectorME;
import opennlp.tools.sentdetect.SentenceModel;

public class ArticleSplitter {
  public static void main(String[] args) {
    //Load sentence detector model
    InputStream modelData = new FileInputStream("OpenNLP_models/en-sent.bin");
    SentenceModel model = new SentenceModel(modelData);

    //Instantiate SentenceDetectorME
    SentenceDetectorME detector = new SentenceDetectorME(model);
  }
}

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;

import opennlp.tools.postag.POSModel;
import opennlp.tools.postag.POSTaggerME;

public class PartOfSpeechTagger {

   public static String readString() throws Exception {
      BufferedReader buf = new BufferedReader(new InputStreamReader(System.in));
      StringBuilder sb = new StringBuilder();
      String line = buf.readLine();
      while( line != null ) {
        sb.append(line + "\n");
        line = buf.readLine();
      }
      buf.close();
      return sb.toString();
   }

   public static void main(String args[]) throws Exception {

      // Load and instantiate the POSTagger
      InputStream posTagStream = new FileInputStream("OpenNLP_models/en-pos-maxent.bin");
      POSModel posModel = new POSModel(posTagStream);
      POSTaggerME posTagger = new POSTaggerME(posModel);

      // Split text into space-separated tokens
      String tokens[] = readString().split("[ ]+");
      //Tagging all tokens
      String tags[] = posTagger.tag(tokens);

      //Printing the token-tag pairs
      for( int i = 0; i < tokens.length; i++ )
         System.out.print(tokens[i] + "/" + tags[i] + " ");
   }
}

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.Arrays;

public class DataAnalysis {

   public static String readString() throws Exception {
      BufferedReader buf = new BufferedReader(new InputStreamReader(System.in));
      StringBuilder sb = new StringBuilder();
      String line = buf.readLine();
      while( line != null ) {
        sb.append(line + "\n ");
        line = buf.readLine();
      }
      buf.close();
      return sb.toString();
   }

   private static Integer docCount = 0;
   private static Integer sentenceCount = 0;
   private static Integer maxSentenceCount = 0;
   private static Integer minSentenceCount = 2147483646;
   private static Integer totalSentenceCount = 0;
   private static Integer tokenCount = 0;
   private static Integer maxTokenCount = 0;
   private static Integer minTokenCount = 2147483646;
   private static Integer totalTokenCount = 0;
   private static Boolean inBody = false;
   private static Boolean wasLabel = false;

   public static void updateDocumentCounts(Integer docIndex) {
     System.out.println("Doc " + docIndex + ":");
     System.out.println("\tTotal number of sentences: " + sentenceCount);
     System.out.println("\tTotal number of tokens: " + tokenCount);
     System.out.println("\tAverage sentence length: " + tokenCount/sentenceCount);
     if (sentenceCount < minSentenceCount) {
       minSentenceCount = sentenceCount;
     }
     if (sentenceCount > maxSentenceCount) {
       maxSentenceCount = sentenceCount;
     }
     totalSentenceCount += sentenceCount;
     if (tokenCount < minTokenCount) {
       minTokenCount = tokenCount;
     }
     if (tokenCount > maxTokenCount) {
       maxTokenCount = tokenCount;
     }
     totalTokenCount += tokenCount;
     sentenceCount = 0;
     tokenCount = 0;
   }

   public static void main(String args[]) throws Exception {

      // Load and instantiate the POSTagger
      InputStream fileStream = new FileInputStream("OpenNLP_models/en-pos-maxent.bin");

      // Split text into space-separated tokens
      String tokens[] = readString().split("[ ]+");

      //
      for( int i = 0; i < tokens.length; i++ ) {
        String deTagged[] = tokens[i].split("/");
        // System.out.print(Arrays.toString(deTagged));
        if (deTagged[0].equals("$DOC")) {
          if (inBody) {
            updateDocumentCounts(docCount);
          }
          inBody=false;
          docCount++;
        }
        if (deTagged[0].equals("$TITLE") || deTagged[0].equals("$TEXT")) {
          inBody = true;
          wasLabel = true;
        } else if (inBody && !wasLabel) {
          if (deTagged[0].equals("\n")) {
            sentenceCount++;
          } else {
            tokenCount++;
          }
        } else {
          wasLabel = false;
        }
      }
      updateDocumentCounts(docCount);
      System.out.println("\nTotal number of docs: " + docCount);


      System.out.println("\tMinimum number of sentences: " + minSentenceCount);
      System.out.println("\tAverage number of sentences: " + totalSentenceCount / docCount);
      System.out.println("\tMaximum number of sentences: " + maxSentenceCount);

      System.out.println("\n\tMinimum number of tokens: " + minTokenCount);
      System.out.println("\tAverage number of tokens: " + totalTokenCount / docCount);
      System.out.println("\tMaximum number of tokens: " + maxTokenCount);

      System.out.println("\n\tAverage sentence length: " + totalTokenCount/totalSentenceCount);

      fileStream.close();
   }
}

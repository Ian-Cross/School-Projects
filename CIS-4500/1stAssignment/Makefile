JAVAC=javac
CLASSPATH=opennlp-tools-1.9.1.jar:.
GENSAMPLEPATH=./TextSamples/GeneralSample/
ARTSAMPLEPATH=./TextSamples/ArticleSample/

all: SentenceSplitter.class PartOfSpeechTagger.class # TokenizerMEProbs.class

%.class: %.java
	$(JAVAC) -cp $(CLASSPATH) $^

clean:
	rm -f *.class *~

splitted:
	java -cp ./$(CLASSPATH) SentenceSplitter articles.txt > articles.splitted

tagged:
	java -cp ./$(CLASSPATH) POSTaggingMEDemo articles.splitted > articles.tagged

stemmed:
	java -cp ./$(CLASSPATH) TokenizerMEProbs articles.splitted > articles.stemmed

JAVAC=javac
CLASSPATH=opennlp-tools-1.9.1.jar:.
GENSAMPLEPATH=./TextSamples/GeneralSample/
ARTSAMPLEPATH=./TextSamples/ArticleSample/

all: SentenceDetectionME.class POSTaggingMEDemo.class TokenizerMEProbs.class

%.class: %.java
	$(JAVAC) -cp $(CLASSPATH) $^

clean:
	rm -f *.class *~

splitted:
	java -cp ./$(CLASSPATH) SentenceDetectionME $(GENSAMPLEPATH)sample.txt > $(GENSAMPLEPATH)sample.splitted

tagged:
	java -cp ./$(CLASSPATH) POSTaggingMEDemo $(GENSAMPLEPATH)sample.splitted > $(GENSAMPLEPATH)sample.tagged

stemmed:
	java -cp ./$(CLASSPATH) TokenizerMEProbs $(GENSAMPLEPATH)sample.splitted > $(GENSAMPLEPATH)sample.stemmed

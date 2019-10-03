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
	java -cp ./$(CLASSPATH) SentenceDetectionME $(ARTSAMPLEPATH)sample.txt > $(ARTSAMPLEPATH)sample.splitted

tagged:
	java -cp ./$(CLASSPATH) POSTaggingMEDemo $(ARTSAMPLEPATH)sample.splitted > $(ARTSAMPLEPATH)sample.tagged

stemmed:
	java -cp ./$(CLASSPATH) TokenizerMEProbs $(ARTSAMPLEPATH)sample.splitted > $(ARTSAMPLEPATH)sample.stemmed

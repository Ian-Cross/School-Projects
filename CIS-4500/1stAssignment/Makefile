JAVAC=javac
JFLEX=jflex
CLASSPATH=opennlp-tools-1.9.1.jar:.
IOFILEPATH=./dataFiles

all: SentenceSplitter.class Token.class Lexer.class Scanner.class PartOfSpeechTagger.class DataAnalysis.class

%.class: %.java
	$(JAVAC) -cp $(CLASSPATH) $^

clean:
	rm -f Lexer.java *.class *~ && cd $(IOFILEPATH) && rm -f *.splitted *.tokenized *.tagged *.analysis

Lexer.java: articles.flex
	$(JFLEX) articles.flex

splitted:
	java -cp ./$(CLASSPATH) SentenceSplitter < $(IOFILEPATH)/articles.txt > $(IOFILEPATH)/articles.splitted

tokenize:
	java Scanner < $(IOFILEPATH)/articles.splitted > $(IOFILEPATH)/articles.tokenized

tagged:
	java -cp ./$(CLASSPATH) PartOfSpeechTagger < $(IOFILEPATH)/articles.tokenized > $(IOFILEPATH)/articles.tagged

analize:
	java DataAnalysis < $(IOFILEPATH)/articles.tagged > $(IOFILEPATH)/articles.analysis

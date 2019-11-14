JAVAC=javac
# JFLEX=jflex
JFLEX=/usr/local/jflex-1.7.0/bin/jflex
CLASSPATH=opennlp-tools-1.9.1.jar:.
IOFILEPATH=./dataFiles

all: a1 a2

a1: SentenceSplitter.class Token.class Lexer.class Scanner.class

a2: Preprocessor.class #TreeMap.class

%.class: %.java
	$(JAVAC) -cp $(CLASSPATH) $^

clean:
	rm -f Lexer.java *.class *~

deepClean:
	rm -f Lexer.java *.class *~ && cd $(IOFILEPATH) && rm -f *.splitted *.tokenized *.tagged *.analysis *.stemmed

Lexer.java: articles.flex
	$(JFLEX) articles.flex

splitted:
	java -cp ./$(CLASSPATH) SentenceSplitter < $(IOFILEPATH)/documents_smaller.txt > $(IOFILEPATH)/documents_smaller.splitted

tokenize:
	java Scanner < $(IOFILEPATH)/documents_smaller.splitted > $(IOFILEPATH)/documents_smaller.tokenized

preprocessor:
	java -cp ./$(CLASSPATH) Preprocessor $(IOFILEPATH)/documents_smaller.tokenized $(IOFILEPATH)/stopwords.txt $(IOFILEPATH)/documents_smaller.stemmed

# treeMap:
# 	java TreeMap $(IOFILEPATH)/documents_smaller.stemmed $(IOFILEPATH)

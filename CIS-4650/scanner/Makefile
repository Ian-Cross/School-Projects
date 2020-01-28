JAVAC=javac
JFLEX=jflex
DATA=datafiles/

all: Token.class Lexer.class Scanner.class

%.class: %.java
	$(JAVAC) $^

Lexer.java: news.flex
	$(JFLEX) news.flex

run: all
	java Scanner < $(DATA)newsdata.txt > $(DATA)output.txt

clean:
	rm -f Lexer.java *.class *~

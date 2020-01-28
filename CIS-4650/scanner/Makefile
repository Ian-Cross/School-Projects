JAVAC=javac
JFLEX=jflex

all: Token.class Lexer.class Scanner.class

%.class: %.java
	$(JAVAC) $^

Lexer.java: news.flex
	$(JFLEX) news.flex

run: all
	java Scanner < newsdata.txt > output.txt

clean:
	rm -f Lexer.java *.class *~

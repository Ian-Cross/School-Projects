JAVAC=javac
CLASSPATH=opennlp-tools-1.9.1.jar:.

all: StemmerDemo.class TreeMapDemo.class

%.class: %.java
	$(JAVAC) -cp $(CLASSPATH) $^

clean:
	rm -f *.class *~

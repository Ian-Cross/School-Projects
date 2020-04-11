JAVAC=javac
IOFILEPATH=./dataFiles

all: DTLearn.class Attribute.class Scheme.class UTIL.class Example.class Sample.class Node.class

%.class: %.java
	$(JAVAC) $^

clean:
	rm -f *.class

learn:
	java DTLearn $(IOFILEPATH)/SchemeFile $(IOFILEPATH)/DataFile

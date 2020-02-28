JAVA=java
JAVAC=javac
INFILE=ExpFile
OUTFILE=CnfFile

All: ExpToCnf.class

%.class: %.java
	$(JAVAC) $^

run:
	java ExpToCnf $(INFILE) $(OUTFILE)

clean:
	rm -f *.class

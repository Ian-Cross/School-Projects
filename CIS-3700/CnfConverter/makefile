JAVA=java
JAVAC=javac
INFILE=ExpFile
OUTFILE=CnfFile

All: Bop.class Exp.class ExpToCnf.class run

%.class: %.java
	$(JAVAC) -Xlint:unchecked $^

run:
	java ExpToCnf $(INFILE) $(OUTFILE)

clean:
	rm -f *.class

# jarPath=.;search.jar
jarPath=search.jar:.
goalFile=goalFiles/initGoal2.txt

all: clean build run

build: Board.java PuzzleProblem.java PuzzleAgent.java
	javac -cp $(jarPath) *.java

run:
	java -cp $(jarPath) PuzzleAgent $(goalFile)

clean:
	rm -f *.class

# Assignment 1 Slide puzzle A\* solution

## Problem

8-puzzle is a game that is played on a 3x3 board. This board has 9 positions and 8 squares that go in those positions.

Given a scrambled version of this puzzle, using an A\* search implemented in Java find the best quickest and cheapest number of moves to find the solution.

## Compilation and Execution

### Windows

To compile run:
`javac -cp .;search.jar \*.java`

To execute: `java -cp .;search.jar PuzzleAgent InitGoalFile`

### Mac & Linux

To compile run: `javac -cp search.jar:. Board.java PuzzleProblem.java PuzzleAgent.java`

To execute: `java -cp search.jar:. PuzzleAgent \$(goalFile)`

A makefile is also provided, running `make` will clean the folder, rebuild, and execute the program with 1 of the included data files.

## Starting Code

### Search.jar

###### ObjectPlus

This abstract class enhances Java Object class with the ability to show itself in a console.

###### Problem

This abstract class specifies components in problem definition. It has an abstract method getSuccessor() that must be implemented by subclasses.

###### Node

This class implements a generic node in search tree. It has an instance variable state that is an object of class ObjectPlus.

###### SearchAgent

This class implements a generic agent that performs treeSearch.

## Author

Ian Cross

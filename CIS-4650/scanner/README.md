# Basic Scanner

## Problem

The problem is described in full in the included specification PDF.

In Brief, the purpose of this program is the create a Lexer, Token, and Scanner file to scan and parse a series of news articles. The output of these programs is a broken down version of the news articles that can be further parse and analyzed more easily.

## Assumptions and Limitations

The major assumption is that the corpus will stick to the general requirements laid out in the specification file. Deviation may not cause breaking but unaccounted for tags will be ignored and unknown characters will be UNKNOWN.

## Building and Execution

To build run the `make` command in the main directory. This will produce a Java binary file.
Alternatively, Build the Lexer file with `jflex news.flex` the classes can then be built with `javac Token.java` and `javac Scanner.java`.

The binary file can be executed by `java Scanner`, it is highly recommended to pipe in the input within a file and catch the output through pipes into an output file. `java Scanner < input.txt > output.txt`

## Testing

A testing file in the datafiles folder has been created to try and account for the different
combinations of text expected to see in the corpus.

To use the testing file build the scanner as normal and execute with
`java Scanner < datafiles/testing.txt`

## Improvements

Potentially to extend the regex to accept a more robust series of acceptable tags. Identification of tag attributes, to store styling for later.

# NLP Data Preprocessing

## Problem

In order to gain more knowledge about Natural language processing this assignment focuses on some data preprocessing steps involved. This include Sentence splitting, sentence tokenization, part of speech tagging and some brief data analysis. Each of these steps provides its own solutions along with its own challenges.

#### Assumptions and Limitations

The largest assumption is the general format of the initial input file will be along the lines of the example files provided. Containing simplified articles with three segments (DOC, TITLE, TEXT). A limitation that comes from this assumption is if the input files differ, parts of the program will not execute properly.

Another assumption is the general rules used for tokenization. If a different set of rules is required to be followed, then a new flex file will need to be created for the scanner to execute properly.

#### Possible Improvements

As deviation from the existing format is very limited the most obvious improvement would be to include all formats. Allowing for all documents to be analyzed would be a drastic improvement on the applicability of these programs.

## Execution

Included is a Makefile:

- running `make` will compile and create all 4 programs needed for execution.

Alternatively, the individual files can be compiled using:

- `javac -cp opennlp-tools-1.9.1.jar:. CLASSFILE`

Each program can be run using these commands:

- Sentence Splitting
  - `java -cp opennlp-tools-1.9.1.jar:. SentenceSplitter`
- Tokenization
  - `java Scanner`
- Part of Speech Tagging
  - `java -cp opennlp-tools-1.9.1.jar:. PartOfSpeechTagger`
- Data analysis
  - `java DataAnalysis`

These programs all take input from stdin and write to stdout, it is recommended to pipe in input to the programs from an input file and capture output in an output file.

#### Testing

Informal testing was used throughout the creation of the 4 programs. The _articlesSmall.txt_ was used as a sample from the larger file to manually validate each step. Each token category was exhaustively tested and should be as robust as needed.

## Author

- **Ian Cross**

## Sample Code

- Sample code was provided for Sentence Splitting, Jflex Scanner creation and Tokenization, and Part of Speech tagging. This code was referenced and altered for this project.

## Acknowledgments

- Instructor: Prof. Fei Song
- NLP Library & Models: OpenNLP
- University of Guelph

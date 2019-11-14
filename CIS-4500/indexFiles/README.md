# Assignment 2

## Notes

Due to outside factors part 2 & 3 were not completed.
This will be addressed moving forward and will be finished swiftly.

## Execution

Running make in the main directly will compile all necessary Java files
Each subsequent program has their own make command to run them properly. They can also be run using the following commands

### Splitter

Utilizing standard in and out to read and write the files
`java -cp opennlp-tools-1.9.1.jar:. SentenceSplitter < input.txt > output.txt`

### Tokenizer

Utilizing standard in and out to read and write the files
`java Scanner < input.txt > output.txt`

### Preprocessor

Utilizing command-line arguments for the input and output files along with a stopwordReference for removal
`java -cp opennlp-tools-1.9.1.jar:. Preprocessor input.txt stopwordsReference.txt output.txt`

### TreeMap

## Author

- **Ian Cross**

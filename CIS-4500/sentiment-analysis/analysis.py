#!/usr/bin/env python3

import os, sys, re
from pathlib import Path

fileCount = 0
maxSentenceCount = 0
minSentenceCount = 2147483647
totalSentenceCount = 0
maxTokenCount = 0
minTokenCount = 2147483647
totalTokenCount = 0
datafiles = None
verbose = False


def updateCounts(tokenCount,sentenceCount):
    global minSentenceCount, maxSentenceCount, totalSentenceCount, minTokenCount, maxTokenCount, totalTokenCount, verbose
    if verbose:
        print("\t%d - Tokens" % tokenCount)
        print("\t%d - Sentences" % (sentenceCount))
        print("\t%d - Average sentence length" % (tokenCount/sentenceCount))

    if (sentenceCount < minSentenceCount):
        minSentenceCount = sentenceCount

    if (sentenceCount > maxSentenceCount):
     maxSentenceCount = sentenceCount

    totalSentenceCount += sentenceCount

    if (tokenCount < minTokenCount):
     minTokenCount = tokenCount

    if (tokenCount > maxTokenCount):
     maxTokenCount = tokenCount

    totalTokenCount += tokenCount;


def readFile(file):
    global fileCount
    fileCount+=1
    sentenceCount = 0
    tokenCount = 0
    if verbose:
        print("\nFile (%s) contains:" % (file))
    for line in file.open():
        sentenceCount+=1
        tokens = line.split(" ")
        tokenCount += len(tokens)
    updateCounts(tokenCount, sentenceCount)


def loadArgs():
    global verbose, datafiles
    while len(sys.argv) != 0:
        arg = sys.argv.pop(0)
        if arg in ["--dataset","-ds"]:
            arg = sys.argv.pop(0)
            datafiles = arg
        if arg in ["--verbose","-v"]:
            verbose = True


def main():
    global fileCount, maxSentenceCount, minSentenceCount, totalSentenceCount, maxTokenCount, minTokenCount, totalTokenCount, verbose, datafiles
    loadArgs()

    if datafiles is None:
        datafiles = "dataset"

    try:
        for filename in Path(datafiles).iterdir():
            file = Path(filename)
            if re.search("pos",str(filename)):
                if file.is_dir():
                    for posFile in file.iterdir():
                        readFile(posFile)
                else:
                    raise AttributeError
            elif re.search("neg",str(filename)):
                if file.is_dir():
                    for negFile in file.iterdir():
                        readFile(negFile)
                else:
                    raise AttributeError
    except AttributeError as e:
        print("\nIncluded datafile '%s' is not a directory, or does not contain a 'pos' & a 'neg' directory \n" % datafiles)
        raise e
        exit(1)
    except Exception as e:
        print("Error occured")
        raise e
        exit(1)

    print("\nTotal number of docs: %d" % fileCount)

    print("\nMinumum number of sentences: %d" % minSentenceCount)
    print("Average number of sentences: %d" % (totalSentenceCount/fileCount))
    print("Maximum number of sentences: %d" % maxSentenceCount)

    print("\nMinumum number of tokens: %d" % minTokenCount)
    print("Average number of tokens: %d" % (totalTokenCount/fileCount))
    print("Maximum number of tokens: %d" % maxTokenCount)

    print("\nAverage sentence length: %d" % (totalTokenCount/totalSentenceCount))


if __name__ == '__main__':
    main()

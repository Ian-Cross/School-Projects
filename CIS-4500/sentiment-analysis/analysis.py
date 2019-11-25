#!/usr/bin/env python3

import os
import sys
from pathlib import Path
import re

fileCount = 0
maxSentenceCount = 0
minSentenceCount = 2147483647
totalSentenceCount = 0
maxTokenCount = 0
minTokenCount = 2147483647
totalTokenCount = 0


def updateCounts(tokenCount,sentenceCount):
    global minSentenceCount, maxSentenceCount, totalSentenceCount, minTokenCount, maxTokenCount, totalTokenCount
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
    print("\nFile (%s) contains:" % (file))
    for line in file.open():
        sentenceCount+=1
        tokens = line.split(" ")
        tokenCount += len(tokens)
    updateCounts(tokenCount, sentenceCount)

def main():
    global fileCount, maxSentenceCount, minSentenceCount, totalSentenceCount, maxTokenCount, minTokenCount, totalTokenCount
    dataFiles = Path(sys.argv[2])

    for filename in dataFiles.iterdir():
        file = Path(filename)
        if (re.search("pos",str(filename)) and file.is_dir()):
            for posFile in file.iterdir():
                readFile(posFile)
        elif (re.search("neg",str(filename)) and file.is_dir()):
            for negFile in file.iterdir():
                readFile(negFile)

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

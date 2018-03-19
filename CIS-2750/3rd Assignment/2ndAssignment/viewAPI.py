#!/usr/bin/python

import view
import sys
import os

def printPost(toPrint):
    if toPrint == "FAIL":
        print "There are no messages in that stream"
    else:
        print toPrint.stream
        print toPrint.username
        print toPrint.date
        for i in range(len(toPrint.data)):
            print toPrint.data[i]


if __name__== "__main__":
    filelist = os.listdir("2ndAssignment/messages/")
    if (sys.argv[1] == "getStreams"):
        streamList = view.streamChoice(sys.argv[2],filelist)
        if (len(streamList) == 1):
            print ("Create Stream")
        else:
            for i in range(len(streamList)):
                print(streamList[i])
    elif (sys.argv[1] == "getPost"):
        printPost(view.getPosts(sys.argv[2],sys.argv[3]))
    elif (sys.argv[1] == "getLastRead"):
        print view.getLastRead(sys.argv[2],sys.argv[3],filelist)
    elif (sys.argv[1] == "updateUserFile"):
        view.updateUser(sys.argv[3],sys.argv[2])
    elif (sys.argv[1] == "markAll"):
        streamList = view.streamChoice(sys.argv[2],filelist)
        view.markAll(sys.argv[2],sys.argv[3],filelist,streamList)
    elif (sys.argv[1] == "loadPosts"):
        streamList = view.streamChoice(sys.argv[2],filelist)
        view.loadPosts(sys.argv[2],sys.argv[3],streamList,sys.argv[4])

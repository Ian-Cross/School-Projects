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
    elif (sys.argv[1] == "getPost"):
        view.getPosts(sys.argv[2],sys.argv[3],sys.argv[4])
    elif (sys.argv[1] == "getLastRead"):
        print view.getLastRead(sys.argv[2],sys.argv[3],filelist)
    elif (sys.argv[1] == "updateUserFile"):
        view.updateUser(sys.argv[3],sys.argv[2])
    elif (sys.argv[1] == "markAll"):
        view.markAll(sys.argv[2],sys.argv[3])
    elif (sys.argv[1] == "loadPosts"):
        print "Uh Oh"
    elif (sys.argv[1] == "getTotalPosts"):
        view.getTotalPosts(sys.argv[2])

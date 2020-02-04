#!/usr/bin/python

import time
import sys
import os

class NewPost:
    stream = ""
    username = ""
    date = ""
    data = []
    def __init__(self,stream,username,date,data):
        self.username = username
        self.date = date
        self.stream = stream
        self.data = self.breakdown(data)

    def breakdown(self,data):
        string = data.split('\n')
        return string

def markAll(username,stream,filelist,streamList):
    viewlist = []

    if stream.lower() == "all":
        for f in streamList:
            viewlist.append(f)
    else:
        viewlist.append(stream)

    for s in viewlist:
        posts = 0
        streamUserFile = ""
        streamDataFile = ""
        for f in filelist:
            if s in f:
                if "Users." in f:
                    streamUserFile = "2ndAssignment/messages/" + f
                elif "Data." in f:
                    streamDataFile = "2ndAssignment/messages/" + f
        if not streamUserFile: continue
        if not streamDataFile: continue
        userFile = open(streamUserFile,"r+")
        dataFile = open(streamDataFile,"r+")

        for line in dataFile:
            posts+=1

        lines = userFile.readlines()
        userFile.seek(0)
        for line in lines:
            if username + ":" in line:
                userFile.write(username + ": " + str(posts) + "\n")
            else:
                userFile.write(line)

        userFile.close()
        dataFile.close()

def updateUser(stream,username):
    streamDataFile = "2ndAssignment/messages/" + stream + "StreamData.txt"
    dataFile = open(streamDataFile,"r+")
    count = 0;
    line = dataFile.readline()
    while line:
        count += 1
        line = dataFile.readline()

    streamUserFile = "2ndAssignment/messages/" + stream + "StreamUsers.txt"
    userFile = open(streamUserFile,"r+")

    lines = userFile.readlines()
    userFile.seek(0)
    for line in lines:
        print line,
        if username + ": " in line:
            print "Found Match"
            string = line.replace(username + ": ","")
            string = string.replace("\n","")
            haveread = int(string) + 1
            if (haveread > count):
                haveread -= 1
            userFile.write(username + ": " + str(haveread) + "\n")
        else:
            userFile.write(line)

    userFile.close()

def stream(streamList):
    while (1):
        for i in streamList:
            print(i),
        stream = raw_input("\n- ")

        if stream.lower() == "all":
            stream = "All"

        if stream not in streamList:
            print ("Sorry that stream does not exist or the user is not subscribed to it")
        else: break

    return stream

def PageUp():
    return 5

def PageDown():
    return 6

def makeUsername(argv):
    username = ""
    for i in range(1,len(argv)):
        if (i > 1):
            username += " "
        username += argv[i]
    return username

def streamChoice(username,filelist):
    l1 = []
    l1.append("All")
    for i in filelist:
        if "Users" in i:
            file = open("2ndAssignment/messages/" + i,"r")
            for line in file:
                if username + ":" in line:
                    i = i.replace("StreamUsers.txt","")
                    l1.append(i)
            file.close()
    return l1

def displayPosts(posts,order):
    grid = [['' for x in range(0,80)] for y in range(0,25)]

    interrupt = 0
    x = 0
    y = 0
    hasread = 0

    for post in posts:
        if post.read == 1 or post.display == 1:
            post.read = 0
            updateUser(post)
            if not interrupt:
                for s in post.stream:
                    grid[x][y] = s
                    y+=1
                    if (y >= 80): break
                x+=1
                y = 0
                if (x >= 23):
                    interrupt = 1
            if not interrupt:
                for s in post.username:
                    grid[x][y] = s
                    y+=1
                    if (y >= 80): break
                x+=1
                y = 0
                if (x >= 23):
                    interrupt = 1
            if not interrupt:
                for s in post.date:
                    grid[x][y] = s
                    y+=1
                    if (y >= 80): break
                x+=1
                y = 0
                if (x >= 23):
                    interrupt = 1
            if not interrupt:
                for line in post.data:
                    if not interrupt:
                        for c in line:
                            grid[x][y] = c
                            y+=1
                            if (y >= 80): break
                        x+=1
                        y = 0
                        if (x >= 23):
                            interrupt = 1

    p = 0
    menu = "Page Up   Page Down   O-order toggle   M-mark all   S-stream  C-check for new"
    for i in menu:
        grid[23][p] = i
        p+=1
    return grid

def getLastRead(username,streamName,filelist):
    if (streamName == "All"):
        FILE = open("2ndAssignment/messages/" + username + "viewData.txt","r")
        lines = FILE.readlines()
        p = 0
        for line in lines:
            if "Stream: " in line:
                p+=1
        return p
    userFileName = ""
    for f in filelist:
        if streamName+"StreamUsers.txt" in f:
            userFileName = f;
            break;
    if userFileName == "": return ""
    userFile = open("2ndAssignment/messages/"+userFileName,"r+")
    line = userFile.readline()
    while line:
        if username+": " in line:
            break;
        line = userFile.readline()
    line = line.replace(username+": ","")
    line = line.replace("\n","")
    return line

def loadPosts(username,streams,streamList,sort):
    viewlist = []
    outfile = open("2ndAssignment/messages/" + username + "viewData.txt","w")
    if streams == "All":
        for f in streamList:
            if f and f != "All": viewlist.append(f)
    else:
        viewlist.append(streams)

    outfile.write(sort + "\n")
    for stream in viewlist:
        dataFile = open("2ndAssignment/messages/" + stream + "Stream.txt","r+")
        lines = dataFile.readlines()
        for line in lines:
            if "Sender: " in line:
                outfile.write("Stream: " + stream + "\n")
            outfile.write(line)

def sortPosts(toggle):
    print ("Sup")

def getPosts(username,currentPost):
    dataFile = open("2ndAssignment/messages/" + username + "viewData.txt","r")
    count = 0
    newPost = "FAIL"

    line = dataFile.readline()
    line = dataFile.readline()
    while ((count != int(currentPost)) and line):
        stream = line.replace('\n','')
        line = dataFile.readline()
        usernamePost = line.replace('\n','')
        line = dataFile.readline()
        date = line.replace('\n','')
        line = dataFile.readline()
        text = ""
        while(("Stream: " not in line) and line):
            text += line
            line = dataFile.readline()

        newPost = NewPost(stream,usernamePost,date,text)
        count+=1

    dataFile.close()
    return newPost

def printGrid(grid):
    for i in range(0,23):
        print "".join(map(str,grid[i]))

    print ("".join(map(str,grid[23]))),

if __name__== "__main__":

    if (len(sys.argv) <= 1):
        print("Please enter a username as an argument")
        sys.exit(1)

    username = makeUsername(sys.argv)
    filelist = os.listdir("messages/")
    streamList = streamChoice(username,filelist)
    order = 1

    if (len(streamList) == 1):
        print ("That user is not subscribed to anything, goodbye")
        sys.exit(1)

    for i in range(len(streamList)):
        print(streamList[i]),
    streams = raw_input("\n- ")

    if streams.lower() == "all":
        streams = "All"

    if streams not in streamList:
        print ("Sorry that stream does not exist or the user is not subscribed to it")
        sys.exit(1)

    posts = getPosts(streams,filelist,streamList,username)

    while True:
        grid = displayPosts(posts,order)
        printGrid(grid)
        c = raw_input()

        if c == 'Q' or c == 'q':
            break
        elif c == 'O' or c == 'o':
            order *= -1
        elif c == 'M' or c == 'm':
            markAll(streams,filelist,streamList,username)
            posts = getPosts(streams,filelist,streamList,username)
        elif c == 'S' or c == 's':
            streams = stream(streamList)
            posts = getPosts(streams,filelist,streamList,username)
        elif c == 'C' or c == 'c':
            posts = getPosts(streams,filelist,streamList,username)
        elif c == '^[[A':
            print("Page Up")
        elif c == '^[[B':
            print("Page Down")
        else:
            print("nothing")

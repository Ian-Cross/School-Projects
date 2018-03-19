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

def markAll(username,stream):
    viewlist = []
    if stream.lower() == "all":
        os.system("./db -select \"SELECT streamName from streams where binary username='" + username + "'\" > temp.txt")
        tp = open("temp.txt","r")
        strealList = tp.readlines()
        tp.close()
        os.remove("temp.txt")
        for f in streamList:
            viewlist.append(f)
    else:
        viewlist.append(stream)

    for s in viewlist:
        os.system("./db -select \"select numPosts from stats where binary streams='" + s + "'\" > temp.txt")
        tp = open("temp.txt","r")
        numPosts = int(tp.readline())
        tp.close()
        os.remove("temp.txt")

        os.system("./db -i \"UPDATE streams SET lastRead=" + str(numPosts) + " where binary id='" + s + username + "'\"")

def updateUser(stream,username):
    os.system("./db -select \"select numPosts from stats where binary streams='" + stream + "'\" > temp.txt")
    tp = open("temp.txt","r")
    numPosts = int(tp.readline())
    tp.close()
    os.remove("temp.txt")

    os.system("./db -select \"select lastRead from streams where binary streamName='" + stream + "'\" > temp.txt")
    tp = open("temp.txt","r")
    haveRead = int(tp.readline())
    tp.close()
    os.remove("temp.txt")

    if haveRead+1 <= numPosts:
        newRead = haveRead+1
    else:
        newRead = haveRead

    os.system("./db -insert \"UPDATE streams SET lastread=" + str(newRead) + " where binary streamName='" + stream + "'\"")

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

def makeUsername(argv):
    username = ""
    for i in range(1,len(argv)):
        if (i > 1):
            username += " "
        username += argv[i]
    return username

def getTotalPosts(stream):
    os.system("./db -select \"select numPosts from stats where binary streams='" + stream + "'\" > temp.txt")
    tp = open("temp.txt","r")
    numPosts = int(tp.readline())
    tp.close()
    os.remove("temp.txt")

    print numPosts

def streamChoice(username,filelist):
    os.system("./db -select \"select streamName from streams where binary username='" + username + "'\" > temp.txt")
    FILE = open("temp.txt","r")
    lines = FILE.readlines()
    FILE.close()
    if (lines):
        print("All")
        for line in lines:
            if line:
                print line,
    else:
        print("Create Stream")

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
    os.system("./db -select \"select lastRead from streams where binary streamName=\'" + streamName + "\'\" > temp.txt")
    FILE = open("temp.txt","r")
    line = FILE.readline()
    os.remove("temp.txt")
    return line
    # if (streamName == "All"):
    #     FILE = open("2ndAssignment/messages/" + username + "viewData.txt","r")
    #     lines = FILE.readlines()
    #     p = 0
    #     for line in lines:
    #         if "Stream: " in line:
    #             p+=1
    #     return p
    # userFileName = ""
    # for f in filelist:
    #     if streamName+"StreamUsers.txt" in f:
    #         userFileName = f;
    #         break;
    # if userFileName == "": return ""
    # userFile = open("2ndAssignment/messages/"+userFileName,"r+")
    # line = userFile.readline()
    # while line:
    #     if username+": " in line:
    #         break;
    #     line = userFile.readline()
    # line = line.replace(username+": ","")
    # line = line.replace("\n","")
    # return line

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

def getPosts(username,currentPost,streamName):
    os.system("./db -select \"select numPosts from stats where binary streams='" + streamName + "'\" > temp.txt")
    tp = open("temp.txt","r")
    numPosts = int(tp.readline())
    tp.close()
    os.remove("temp.txt")

    while int(currentPost)+1 > numPosts:
        currentPost = int(currentPost) - 1

    os.system("./db -select \"Select * from posts where binary id='" + streamName + str(int(currentPost) + 1) + "'\" > temp.txt")
    tempFile = open("temp.txt","r")

    line = tempFile.readline()
    if (line):
        chunk = line.split("\t")
        stream = chunk[1]
        usernamePost = chunk[2]
        date = chunk[3]
        text = chunk[4]

        line = tempFile.readline()
        while line:
            text = text + line
            line = tempFile.readline()

        print ("Stream: " + stream)
        print ("Sender: " + usernamePost)
        print ("Date: " + date)
        print (text)

        newPost = NewPost(stream,usernamePost,date,text)
    else:
        print ("There are no messages in that stream")

    tempFile.close()
    os.remove("temp.txt")

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

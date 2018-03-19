#!/usr/bin/python

import time
import sys
import os

class NewPost:
    stream = ""
    username = ""
    date = ""
    data = []
    read = 0
    display = 0
    def __init__(self,stream,username,date,data,read):
        self.username = username
        self.date = date
        self.stream = "Stream: " + stream
        self.data = self.breakdown(data)
        self.read = read

    def breakdown(self,data):
        string = data.split('\n')
        return string

def markAll(stream,fileList,streamList,username):
    viewlist = []

    if streams.lower() == "all":
        for f in streamList:
            viewlist.append(f)
    else:
        viewlist.append(streams)

    for s in viewlist:
        posts = 0
        streamUserFile = ""
        streamDataFile = ""
        for f in filelist:
            if s in f:
                if "Users." in f:
                    streamUserFile = "messages/" + f
                elif "Data." in f:
                    streamDataFile = "messages/" + f
        if not streamUserFile: continue
        if not streamDataFile: continue
        userFile = open(streamUserFile,"r+")
        dataFile = open(streamDataFile,"r+")

        print(posts)

        for line in dataFile:
            print(line.replace("\n","") + "."),
            posts+=1

        print(posts)
        lines = userFile.readlines()
        userFile.seek(0)
        for line in lines:
            if username + ":" in line:
                userFile.write(username + ": " + str(posts) + "\n")
            else:
                userFile.write(line)

        userFile.close()
        dataFile.close()

def updateUser(post):
    streamUserFile = "messages/" + post.stream.replace("Stream: ","") + "StreamUsers.txt"
    userFile = open(streamUserFile,"r+")

    lines = userFile.readlines()
    userFile.seek(0)
    for line in lines:
        if post.username + ":" in line:
            string = line.replace(post.username + ": ","")
            string = string.replace("\n","")
            haveread = int(string) + 1
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
    for i in filelist:
        if "Users" in i:
            file = open("messages/" + i,"r")
            for line in file:
                if username + ":" in line:
                    i = i.replace("StreamUsers.txt","")
                    l1.append(i)
            file.close()
    l1.append("All")
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

def getPosts(streams,filelist,steamList,username):
    posts = []
    viewlist = []
    if streams == "All":
        for f in streamList:
            if f and f != "All": viewlist.append(f)
    else:
        viewlist.append(streams)

    for s in viewlist:
        print(s)
        if not s: break
        streamUserFile = ""
        streamDataFile = ""
        streamFile = ""
        for f in filelist:
            if not f: break
            if s in f:
                if "Users." in f:
                    streamUserFile = "messages/" + f
                elif "Data." in f:
                    streamDataFile = "messages/" + f
                else:
                    streamFile = "messages/" + f
        if not streamUserFile: continue
        if not streamDataFile: continue
        if not streamFile: continue
        userFile = open(streamUserFile,"r+")
        dataFile = open(streamDataFile,"r+")
        File = open(streamFile,"r+")

        alreadyRead = 0
        postNumber = 0

        for line in userFile:
            if username + ": " in line:
                alreadyRead = line.replace(username + ": ","")

        line = File.readline()
        while (line):
            postNumber += 1;
            usernamePost = line.replace('\n','')
            line = File.readline()
            date = line.replace('\n','')
            line = File.readline()
            text = ""
            while("Sender: " not in line and line):
                text += line
                line = File.readline()
            read = 0
            if (postNumber >= int(alreadyRead)):
                read = 1
            newPost = NewPost(s,usernamePost,date,text,read)
            posts.append(newPost)

        userFile.close()
        dataFile.close()
        File.close()
    return posts

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

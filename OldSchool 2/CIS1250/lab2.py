#!/usr/bin/python

namesList = []

for pos in range(0,3):
    namesList.append(raw_input("Enter a name: "))

namesList.sort()
print namesList

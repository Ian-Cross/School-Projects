#!/usr/bin/python

for pos in range(1,6): 
    for pos2 in range(1,6):
        if pos*pos2 < 10:
	    print pos*pos2,"    ",
	else:
	    print pos*pos2,"   ",
    print


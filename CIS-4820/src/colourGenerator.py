#!/usr/bin/env python3

#A simple python script to generate the proper format of colours based off of RGB values
import sys

def main():
    red = int(sys.argv[1])
    green = int(sys.argv[2])
    blue = int(sys.argv[3])

    aRed = round(red/256,3)
    aGreen = round(green/256,3)
    aBlue = round(blue/256,3)
    dRed = round(red/512,3)
    dGreen = round(green/512,3)
    dBlue = round(blue/512,3)

    print(aRed,",",aGreen,",",aBlue,",",1.0,",",dRed,",",dGreen,",",dBlue,",",1.0)

if __name__ == '__main__':
    main()



# framework information for older version of MACOS
#INCLUDES = -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

# frameworks for newer MACOS, where include files are moved
INCLUDES = -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/ -framework OpenGL -framework GLUT -lm -Wno-deprecated-declarations

INC = include/
SRC = src/

a1: a1.c $(SRC)graphics.c $(SRC)visible.c $(SRC)world.c $(INC)graphics.h $(INC)world.h
	gcc a1.c $(SRC)graphics.c $(SRC)visible.c $(SRC)world.c -o a1 -I$(INC) $(INCLUDES)

clean:
	rm a1

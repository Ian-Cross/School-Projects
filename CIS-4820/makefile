# framework information for older version of MACOS
#INCLUDES = -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

# frameworks for newer MACOS, where include files are moved
CFLAGS = -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/ -Wno-deprecated-declarations
LFLAGS = -framework OpenGL -framework GLUT -lm
CC = gcc
EXE = a1
INC = -Iinclude/ -Iinclude/worldObjects/

SOURCES = a1.c \
					src/graphics.c \
					src/visible.c  \
					src/generation.c \
					src/timing.c \
					src/worldObjects/valley.c \
					src/worldObjects/hill.c \
					src/worldObjects/base.c \
					src/worldObjects/cloud.c


OBJS = $(SOURCES:%.c=%.o)

all: $(EXE)

.c.o: $(OBJS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

test: a1.c src/graphics.c src/visible.c src/generation.c src/timing.c src/worldObjects/valley.c src/worldObjects/hill.c src/worldObjects/base.c src/worldObjects/cloud.c include/graphics.h include/generation.h include/timing.h include/worldObjects/valley.h include/worldObjects/hill.h include/worldObjects/base.h include/worldObjects/cloud.h
	gcc $(INC) $(CFLAGS) $(LFLAGS) a1.c src/graphics.c src/visible.c src/generation.c src/timing.c src/worldObjects/valley.c src/worldObjects/hill.c src/worldObjects/base.c src/worldObjects/cloud.c -o $(EXE)

clean:
	rm $(EXE) *.o src/*.o src/worldObjects/*.o

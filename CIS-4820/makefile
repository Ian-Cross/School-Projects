# framework information for older version of MACOS
#INCLUDES = -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

# frameworks for newer MACOS, where include files are moved
CFLAGS = -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/ -Wno-deprecated-declarations
LFLAGS = -framework OpenGL -framework GLUT -lm
CC = gcc
EXE = a3
INC = -Iinclude/ -Iinclude/worldObjects/ -Iinclude/entities/

SOURCES = main.c \
					src/graphics.c \
					src/visible.c  \
					src/generation.c \
					src/worldObjects/base.c \
					src/worldObjects/valley.c \
					src/worldObjects/hill.c \
					src/worldObjects/cloud.c \
					src/worldObjects/meteor.c \
					src/timing.c \
					src/team.c \
					src/entities/truck.c \
					src/entities/tower.c \
					src/projectile.c

OBJS = $(SOURCES:%.c=%.o)

all: $(EXE) run

new: $(EXE)

.c.o: $(OBJS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

run:
	./$(EXE)
# test: main.c src/graphics.c src/visible.c src/generation.c src/timing.c src/worldObjects/valley.c src/worldObjects/hill.c src/worldObjects/base.c src/worldObjects/cloud.c include/graphics.h include/visible.h include/generation.h include/timing.h include/worldObjects/valley.h include/worldObjects/hill.h include/worldObjects/base.h include/worldObjects/cloud.h
# 	gcc $(INC) $(CFLAGS) $(LFLAGS) main.c src/graphics.c src/visible.c src/generation.c src/timing.c src/worldObjects/valley.c src/worldObjects/hill.c src/worldObjects/base.c src/worldObjects/cloud.c -o $(EXE)

clean:
	rm $(EXE) *.o src/*.o src/worldObjects/*.o src/entities/*.o

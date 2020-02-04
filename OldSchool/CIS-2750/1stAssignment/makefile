all: 1
CC = gcc
FLAGS = -Wall -ansi -g -Iinclude/

1: ass1.o linkedList.o
	$(CC) bin/ass1.o bin/linkedList.o -o a1 && ./a1 assets/program.cc

2: ass1.o linkedList.o
	$(CC) bin/ass1.o bin/linkedList.o -o a1 && ./a1 assets/sample1.cc

3: ass1.o linkedList.o
	$(CC) bin/ass1.o bin/linkedList.o -o a1 && ./a1 assets/sample2.cc

4: ass1.o linkedList.o
	$(CC) bin/ass1.o bin/linkedList.o -o a1 && ./a1 assets/sample3.cc

5: ass1.o linkedList.o
	$(CC) bin/ass1.o bin/linkedList.o -o a1 && ./a1 assets/program2.cc


ass1.o: src/ass1.c
	$(CC) -c src/ass1.c -o bin/ass1.o $(FLAGS)

linkedList.o: src/linkedList.c
	$(CC) -c src/linkedList.c -o bin/linkedList.o $(FLAGS)

clean:
	rm bin/*.o
	rm assets/*.c
	rm a1

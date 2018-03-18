all: main
CC = gcc
FLAGS = -Wall -pedantic -std=c99 -Iinclude/

main: main.o carbon.o ackermann.o newton.o
	$(CC) main.o -o Assignment1

main.o: main.c
	$(CC) -c main.c $(FLAGS)

carbon.o: carbon.c
	$(CC) -c carbon.c $(FLAGS)

ackermann.o: ackermann.c
	$(CC) -c ackermann.c $(FLAGS)

newton.o: newton.c
	$(CC) -c newton.c $(FLAGS)

clean:
	rm *.o
	rm Assignment1

r:
	./Assignment1

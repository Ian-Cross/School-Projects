CC = gcc
FLAGS = -Wall -pedantic -std=c99 -Iinclude/

q1: q1.o
	$(CC) q1.o -o bin/q1

q2: q2.o
	$(CC) q2.o -o bin/q2

q1.o: src/q1.c
	$(CC) -c src/q1.c $(FLAGS)

q2.o: src/q2.c
	$(CC) -c src/q2.c $(FLAGS)

clean:
	rm *.o
	rm bin/q1
	rm bin/q2

rq1:
	./bin/q1 "(((x1+5.12)*(x2-7.68))/x3)"

rq2:
	./bin/q2

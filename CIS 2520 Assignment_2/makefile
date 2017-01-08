CC = gcc
FLAGS = -Wall -pedantic -std=c99 -Iinclude/

q1: q1.o fileOpening.o fileParsing.o linkedList.o menu.o
	$(CC) q1.o fileOpening.o fileParsing.o linkedList.o menu.o -o bin/q1

q2: q2.o
	$(CC) q2.o -o bin/q2

q1.o: src/q1.c
	$(CC) -c src/q1.c $(FLAGS)

q2.o: src/q2.c
	$(CC) -c src/q2.c $(FLAGS)

fileOpening.o: src/fileOpening.c
	$(CC) -c src/fileOpening.c $(FLAGS)

fileParsing.o: src/fileParsing.c
	$(CC) -c src/fileParsing.c $(FLAGS)

linkedList.o: src/linkedList.c
	$(CC) -c src/linkedList.c $(FLAGS)

menu.o: src/menu.c
	$(CC) -c src/menu.c $(FLAGS)

clean:
	rm *.o
	rm bin/q1
	rm bin/q2

rq1:
	./bin/q1 assests/diskFile.txt

rq2:
	./bin/q2 42+0+5*25-*

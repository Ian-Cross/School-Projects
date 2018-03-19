all: lib post addauthor
CC = gcc
FLAGS = -Wall -ansi -g -I.
FLGS = -Wall -g -I.


post: post.o
	$(CC) $(FLGS) post.o -L. -lstream -o $@

post.o: translate poster.c
	$(CC) $(FLAGS) -c poster.c -o $@

poster.c: poster.cc
	./translate poster.cc

addauthor: author.o
	$(CC) $(FLGS) author.o -L. -lstream -o $@

author.o: author.c
	$(CC) $(FLAGS) -c author.c -o $@

lib: stream.o
	ar cr libstream.a stream.o

stream.o: stream.c
	$(CC) -c stream.c -o stream.o $(FLAGS)

translate: translator.o linkedList.o
	$(CC) translator.o linkedList.o -o translate

translator.o: ass1.c
	$(CC) -c ass1.c -o translator.o $(FLAGS)

linkedList.o: linkedList.c
	$(CC) -c linkedList.c -o linkedList.o $(FLAGS)

clean:
	# rm $(LIB)*.o
	rm *.o
	rm libstream.a
	rm translate
	rm poster.c
	rm post
	rm addauthor

merk:
	rm messages/*.txt

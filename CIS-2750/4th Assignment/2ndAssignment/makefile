all: lib post addauthor libAPI
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
	$(CC) $(FLGS) $< -L. -lstream -o $@

author.o: author.c
	$(CC) $(FLAGS) -c author.c -o $@

lib: stream.o
	ar cr libstream.a stream.o

stream.o: stream.c
	$(CC) -c $< -o $@ $(FLGS)

translate: translator.o linkedList.o
	$(CC) $? -o $@

translator.o: ass1.c
	$(CC) -c $< -o $@ $(FLAGS)

linkedList.o: linkedList.c
	$(CC) -c $< -o $@ $(FLAGS)

libAPI: libAPI.o
	$(CC) $< -L. -lstream -o $@

libAPI.o: libAPI.c
	$(CC) -c $< -o $@

clean:
	# rm $(LIB)*.o
	rm *.o
	rm libstream.a
	rm translate
	rm poster.c
	rm post
	rm addauthor
	rm libAPI

cleanlib:
	rm libstream.a
	rm stream.o

merk:
	rm messages/*.txt

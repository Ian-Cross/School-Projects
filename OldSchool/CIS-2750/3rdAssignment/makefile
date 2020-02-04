all: craftA2 a3
CC = gcc
FLAGS = -Wall -ansi -g -I.

craftA2:
	cd 2ndAssignment/ && make && cd ../

a3: a3.o
	$(CC) $(FLGS) $? -o $@

a3.o: a3.c
	$(CC) $(FLAGS) -c $< -o $@

run:
	./a3 home.wpml

clean:
	rm *.o
	rm a3
	cd 2ndAssignment/ && make clean && cd ../

merk:
	rm home.php
	rm login.php
	rm post.php
	rm addauthor.php

cleanlib:
	cd 2ndAssignment/ && make cleanlib && cd ../

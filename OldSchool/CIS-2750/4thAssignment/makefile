all: craftA2 a3 db
CC = gcc
FLAGS = -Wall -ansi -g -I.
FLGS = -Wall -g -I.
DBLNK = `mysql_config --include` `mysql_config --libs`

craftA2:
	cd 2ndAssignment/ && make && cd ../

a3: a3.o
	$(CC) $(FLGS) $? -o $@

a3.o: a3.c
	$(CC) $(FLAGS) -c $< -o $@

db: db.o
	$(CC) $(FLGS) $(DBLNK) $? -o $@
	./db -n

db.o: db.c
	$(CC) $(FLGS) -c $< -o $@

run:
	./db -c -r -p -u -s -h -n

clean:
	rm *.o a3 db
	cd 2ndAssignment/ && make clean && cd ../

merk:
	rm home.php login.php post.php addauthor.php
	cd 2ndAssignment/ && make merk && cd ../

cleanlib:
	cd 2ndAssignment/ && make cleanlib && cd ../

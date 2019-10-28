all: mpicc mpirun

hello: hellocc hellorun

hellocc: mpi_hello.c
	mpicc -g -Wall -std=c99 -o mpi_hello mpi_hello.c

hellorun: mpi_hello
	mpiexec -n 4 ./mpi_hello

phys: phys.c
	gcc phys.c -o phys -lncurses -lm

mpicc: phys.c
	mpicc -lncurses -lm -o phys phys.c

mpirun: phys
	mpiexec -n 4 phys

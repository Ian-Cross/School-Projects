all: mpicc mpirun

phys: phys.c
	gcc phys.c -o phys -lncurses -lm

mpicc: phys.c
	mpicc -o phys phys.c -lncurses -lm

mpirun: phys
	mpirun -n 1 phys

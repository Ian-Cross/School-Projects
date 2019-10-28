all: mpicc mpirun

phys: phys.c
	gcc phys.c -o phys -lncurses -lm

mpicc: phys.c
	mpicc -lncurses -lm -o phys phys.c

mpirun: phys
	mpiexec -n 4 phys

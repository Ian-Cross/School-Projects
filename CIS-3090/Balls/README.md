# Assignment 2: Balls

## Execution

Simply using make will compile the program, then using make run will execute the compiled program.

Can also be compiled using mpicc
`mpicc -lncurses -lm -o phys phys.c`
and executed with, changing X for the desired thread count
`mpiexec -n X phys`

## Problems

Was unable to test on the server due to an account issue (currently being resolved)
code was written and tested with a dodgy local installation of MPI that had some quirks.

## Author

- **Ian Cross**

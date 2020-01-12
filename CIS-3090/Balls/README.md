# Assignment 2: Balls

This assignment attempts to explore the MPI library through simulating bouncing balls in a confined space.

## Execution

Simply using make will compile the program, then using make run will execute the compiled program.

Can also be compiled using mpicc
`mpicc -lncurses -lm -o phys phys.c`
and executed with, changing X for the desired thread count
`mpiexec -n X phys`

_The program will quit execution upon pressing q_

## Base code

Original boids program used from [How to Create a Custom 2D Physics
Engine: The Basics and Impulse Resolution](https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331)

## Problems

Was unable to test on the server due to an account issue (currently being resolved)
code was written and tested with a dodgy local installation of MPI that had some quirks.

## Author

- **Ian Cross**

# Assignment 4: Game of Life
# Assignment 4: Life

In this assignment, the focus is put into OpenCL and how to implement it into a serial version of Conways' Game of Life

## Execution

Simply using `make` will compile the program, then using `oclgrind ./a4` will execute the compiled program.
This will be compiled using gcc and different libraries will be included based on the platform. The makefile should identify this and include the correct ones.

The program can then be executed with:
`oclgrind ./life`

Some parameter to consider:

- `-n X` -> Where X is the desired number of kernels to use in execution, default: 2
- `-o` -> The inclusion of which will hide the ncurses output, default: true

## Author

- **Ian Cross**

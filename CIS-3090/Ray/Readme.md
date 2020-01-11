# Assignment 3: Ray

In this assignment, the focus is put into OpenMP and how to implement it into an existing serial program

## Execution

The machine must have a working version of g++, and access to the openmp library
Simply using make will compile the program, it can also be compiled using
`g++ -fopenmp main.cc -o main -lm`

The program can then be executed with:
`./main`

Some parameters to consider:

- `-output` -> The inclusion of which will create and output file to save the image, default: false
- `-thread X` -> Where X is the desired thread count for execution, default: 1
- `-size H W` -> Where H is the desired hight of the image, and W is the desired width, default: 640 x 480

## Base code

A working version of the ray generator was provided for this assignment written by Peter Shirley <ptrshrl@gmail.com>.

## Results

Average Thread Times
1 => 143
2 => 79.5
4 => 45.8
8 => 29.8
16 => 26.7

Repeated Trials
1 => 147 + 145 + 144 + 143 + 145 + 143 + 139 + 141 + 138 + 145 = 1430 => 1430/10 = 143
2 => 81 + 79 + 80 + 79 + 79 + 79 + 80 + 79 + 79 + 80 = 795 => 795/10 = 79.5
4 => 46 + 45 + 47 + 49 + 46 + 45 + 45 + 45 + 45 + 45 = 458 => 458/10 = 45.8
8 => 29 + 30 + 31 + 30 + 30 + 30 + 30 + 29 + 30 + 29 = 298 => 298/10 = 29.8
16 => 26 + 26 + 27 + 27 + 28 + 26 + 27 + 26 + 27 + 27 = 267 => 267/10 = 26.7

## Author

- **Ian Cross**

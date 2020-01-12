# Parallel Programming

This assignment is to explore the differences in data parallelism and task parallelism. This will be explored by creating two programs, one of each and viewing the execution time for a given amount of iterations.

## Execution

There are three programs included, the makefile can be used to compile all three. Each have a visual and a non visual version to allow for timing tests without IO interference.

Each program can be compiled without the makefile as so: `gcc file.c -o file -lncurses -lm -lpthread` for a visual representation or `gcc file.c -o filept -lm -DNOGRAPHICS -lpthread` for a non visual timing test, switching out file for the other boids, data, and task respectively.

The resulting files can be run with `./file` using the following arguments as needed

- `-i I` => Where I is the number of updates run on the population
- `-c P` => Where P is the size of the population to create
- `-t T` => Where T is the desired number of threads (only applies to data.c)

_The visual version will quit execution upon pressing q_

## Base code

Original boids program used from [Boids Pseudocode](http://www.kfish.org/boids/pseudocode.html)

## Results

###### Serial

_1 Thread_

| Pop.Size | Time (s) |
| -------- | -------- |
| 50       | 0.127    |
| 100      | 0.488    |
| 500      | 11.274   |
| 1000     | 48.817   |

###### Data Parallelism

| Threads  | 1        | 2        | 3        | 4        | 5        | 6        | 7        |
| -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |
| Pop.Size | Time (s) | Time (s) | Time (s) | Time (s) | Time (s) | Time (s) | Time (s) |
| 50       | 0.146    | 0.95     | 0.82     | 0.80     | 0.79     | 0.94     | 0.97     |
| 100      | 0.486    | 0.280    | 0.206    | 0.171    | 0.156    | 0.179    | 0.187    |
| 500      | 11.879   | 5.863    | 4.080    | 3.106    | 2.549    | 2.393    | 2.616    |
| 1000     | 45.189   | 23.134   | 15.790   | 12.035   | 9.915    | 9.298    | 9.844    |

###### Task Parallelism

_4 Threads_

| Pop.Size | Time   |
| -------- | ------ |
| 50       | 0.162  |
| 100      | 0.562  |
| 500      | 11.574 |
| 1000     | 47.177 |

### Interpretation

From the data parallelism results it is shown that as the thread count increases, the lower the total time. As well, as the population increases, so too does the time proportionally. A population so small that the threads are larger than the population wouldn't benefit from the addition of threads. This can be seen in the 6 and 7 thread results, with lower populations the time increases because the overhead of setting up and managing the threads is greater than the benefit of including them. The task parallelism is marginally slower, but would likely get drastically slower on a larger and larger iterations.

## SYSTEM

- processor: Intel Core i7
- cores: 6 cores
- clock speed: 2.6 GHz
- memory: 16gb 2400 DDR4

## Author

- **Ian Cross**

## License

Under no circumstances should this code be duplicated or used in any educational project.

## Acknowledgments

- Instructor: David Calvert
- University of Guelph

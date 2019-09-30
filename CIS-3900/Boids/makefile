
all: boids boidspt data datapt task taskpt

boids: boids.c
	gcc boids.c -o boids -lncurses -lm

boidspt: boids.c
	gcc boids.c -o boidspt -lm -DNOGRAPHICS

data: data.c
	gcc data.c -o data -lncurses -lm

datapt: data.c
	gcc data.c -o datapt -lm -DNOGRAPHICS

task: task.c
	gcc task.c -o task -lncurses -lm

taskpt: task.c
	gcc task.c -o taskpt -lm -DNOGRAPHICS

clean:
	rm data datapt boids boidspt task taskpt

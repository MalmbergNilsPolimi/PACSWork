CC = mpic++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -O3 -fopenmp
LDFLAGS = -lm -lmpi

SRCS = solver.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = jacobi

# Valeurs par défaut
N ?= 100
TOLERANCE ?= 1e-6
MAX_ITER ?= 10000
NUM_PROCS ?= 1

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC) solution_*.vtk

run: $(EXEC)
	mpirun -np $(NUM_PROCS) ./$(EXEC) $(N) $(TOLERANCE) $(MAX_ITER)
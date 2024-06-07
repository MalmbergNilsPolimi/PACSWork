CC = mpic++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -O3 -fopenmp
LDFLAGS = -lm -lmpi
INCLUDES = -I../include

SRCS := $(wildcard ../src/*.cpp) main.cpp
OBJS := $(patsubst ../src/%.cpp,obj/%.o,$(filter-out main.cpp,$(SRCS)))
MAIN_OBJ := obj/main.o
EXEC = bin/jacobi
VTK_DIR = data

# Valeurs par défaut
N ?= 100
TOLERANCE ?= 1e-6
MAX_ITER ?= 10000
NUM_PROCS ?= 1
OMP_NUM_THREADS ?= $(shell ./detect_threads.sh)
PRINT_INFO ?= true
DIMENSION_VTK ?= 2

.PHONY: all clean run

all: $(EXEC) $(VTK_DIR)

$(VTK_DIR):
	@mkdir -p $@

$(EXEC): $(OBJS) $(MAIN_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) $(MAIN_OBJ) $(CFLAGS) $(LDFLAGS) -o $@

obj/%.o: ../src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MAIN_OBJ): main.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf obj bin $(VTK_DIR) plot

run: $(EXEC)
	OMP_NUM_THREADS=$(OMP_NUM_THREADS) mpirun -np $(NUM_PROCS) ./$(EXEC) $(N) $(TOLERANCE) $(MAX_ITER) $(PRINT_INFO) $(DIMENSION_VTK)
	@mv *.vtk $(VTK_DIR)/

valgrind_run: $(EXEC)
	valgrind --leak-check=yes --show-leak-kinds=all --track-origins=yes mpirun -np $(NUM_PROCS) ./$(EXEC) $(N) $(TOLERANCE) $(MAX_ITER) $(PRINT_INFO) $(DIMENSION_VTK)
	@mv *.vtk $(VTK_DIR)/
# Challenge 2: A sparse matrix

## Prerequisites

- A C++ compiler supporting the C++17 standard (e.g., g++).
- make

## Compilation

The project uses a Makefile to facilitate compilation. Here are the available commands:

- `make` or `make all`: Compiles all source files and generates the corresponding executables in the `bin/` directory.
- `make directories`: Creates the necessary directories for compilation (`obj/` and `bin/`).
- `make compress`: Compiles the `test_compress.cpp` file and generates the `compress` executable in the `bin/` directory.
- `make marketReader`: Compiles the `test_marketReader.cpp` file and generates the `marketReader` executable in the `bin/` directory.
- `make multiply`: Compiles the `test_multiply.cpp` file and generates the `multiply` executable in the `bin/` directory.
- `make resize`: Compiles the `test_resize.cpp` file and generates the `resize` executable in the `bin/` directory.

## Execution

After compilation, you can run the programs with the following commands:

- `make run_compress`: Runs the `compress` program.
- `make run_marketReader`: Runs the `marketReader` program.
- `make run_multiply`: Runs the `multiply` program.
- `make run_resize`: Runs the `resize` program.

## Cleaning Up

The `make clean` command removes the object files and executables generated during compilation.

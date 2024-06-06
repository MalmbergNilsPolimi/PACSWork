# Jacobi MPI+OpenMP Project

---

## Introduction

This project implements a Jacobi iteration method to solve the Laplace equation using a parallel approach combining MPI (Message Passing Interface) and OpenMP (Open Multi-Processing). The aim is to demonstrate how to combine these two parallelization paradigms to solve computationally intensive problems.

## Project Structure

The project is structured as follows:

```
.
|-- README.md
|-- doc
|   `-- Challenge23-24_3.pdf
|-- include
|   |-- exportVTK.hpp
|   |-- jacobi.hpp
|   `-- utils.hpp
|-- src
|   |-- exportVTK.cpp
|   |-- jacobi.cpp
|   `-- utils.cpp
`-- test
    |-- Makefile
    |-- detect_threads.sh
    `-- main.cpp
```

### File Descriptions

- **include/**: Contains the header files.
  - `exportVTK.hpp`: Declaration of functions for exporting data in VTK format.
  - `jacobi.hpp`: Declaration of functions for the Jacobi method.
  - `utils.hpp`: Declaration of utility functions.

- **src/**: Contains the source files.
  - `exportVTK.cpp`: Implementation of functions for exporting data in VTK format.
  - `jacobi.cpp`: Implementation of the Jacobi method.
  - `utils.cpp`: Implementation of utility functions.

- **test/**: Contains the test and build files.
  - `Makefile`: Build and execution script.
  - `main.cpp`: Entry point of the program.
  - `detect_threads.sh`: Script to detect the number of threads per core.

## Prerequisites

- An MPI-compatible compiler (e.g., `mpic++`).
- MPI and OpenMP libraries installed.
- `make` for building the project.
- Unix/Linux compatible operating system.

## Compilation

To compile the project, use the provided `Makefile`. You can specify some compilation and execution parameters directly in the `make` command.

### Make Commands

In `test/`

- **Compile the project:**
  ```sh
  make
  ```
- **Clean generated files:**
  ```sh
  make clean
  ```
- **Run the program (by default):**
  ```sh
  make run
  ```
- **Run the program (specifying parameters):**
  ```sh
  make run N=128 TOLERANCE=1e-6 MAX_ITER=10000 NUM_PROCS=2
  ```

By default the we have `N=100 TOLERANCE=1e-6 MAX_ITER=10000 NUM_PROCS=1`

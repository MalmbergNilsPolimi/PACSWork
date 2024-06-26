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
    |-- main.cpp
    `-- performance.sh
```

### File Descriptions

- **include/**: Contains the header files.
  - `exportVTK.hpp`: Declaration of functions for exporting data in VTK format.
  - `jacobi.hpp`: Declaration of functions for the Jacobi method.
  - `utils.hpp`: Declaration of functions for boundary conditions.

- **src/**: Contains the source files.
  - `exportVTK.cpp`: Implementation of functions for exporting data in VTK format.
  - `jacobi.cpp`: Implementation of the Jacobi method.
  - `utils.cpp`: Implementation of utility functions.

- **test/**: Contains the test and build files.
  - `Makefile`: Build and execution script.
  - `main.cpp`: Entry point of the program.
  - `detect_threads.sh`: Script to detect the number of threads per core.
  - `performance.sh`: Script to plot the error in function of the number of points and process.

## Prerequisites

- An MPI-compatible compiler.
- MPI and OpenMP libraries installed.
- `make` for building the project.
- Unix/Linux compatible operating system.

## Compilation

To compile the project, use the provided `Makefile`. You can specify some compilation and execution parameters directly in the `make` command.

### Number of threads per core
If you wan't to use the script detecting the number of threads per core to adapt parallelization you will need to you in `test/` folder the following command:
```chmod +x detect_threads.sh```

If you don't want to use the script and direclty chose the number of threads per core you can modify the line 17 in the Makefile (in `test/` folder).
For example by writting:
```
OMP_NUM_THREADS ?= 2
```

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
  make run N=128 TOLERANCE=1e-6 MAX_ITER=10000 NUM_PROCS=2 PRINT_INFO=false DIMENSION_VTK=3
  ```

By default the we have `N=100 TOLERANCE=1e-6 MAX_ITER=10000 NUM_PROCS=1 PRINT_INFO=true DIMENSION_VTK=2`
- N is the number of points along each coordinate direction;
- TOLERANCE is the criterion of convergence of jacobi iterations;
- MAX_ITER is the maximum number of iterations allowed by processus;
- NUM_PROCS is the number of processus;
- PRINT_INFO is used to allow the user to remove some comments from the shell;
- DIMENSION_VTK is used to specify if the vtk file is written for a 3D plot in paraview or a 2D plot with a color scale.

If the user wants to change the function, it can be done directly in the `main.cpp`. To change the boundary conditions, it can be done in `utils.cpp`.

By using Make Commands the user will be able to test directly the Laplace solver.

The results are stored in `test/data` in a `.vtk` file that can be open using ParaView with the command:
```
paraview data/solution.vtk
```

Then on the ParaView window you can click on `Apply` on `Properties`. If nothing appear, check that you are displaying "solution" using "Surface" and 2D or 3D representation (in function of DIMENSION_VTK).

### Performance plot of the Laplace solver
To compute the error in function of the number of points along each coordinate direction and in function of the number of processus the user can use the following commands:

```
cd test/
chmod +x performance.sh
./performance.sh
```

This part is not optimized, so it will take some time to compute and provide a result. The user can adapt the number of process line 22 and the number of points line 31 by adapting k.

The results will by generated in a new folder called `plot/`. The results will be sum up in `error_plot.png`

## About changing boundary conditions
To change boundary conditions, the user need to modify directly the function `void make_boundaries(std::vector<std::vector<double>>& U, int rank, int size)` in `src/utils.cpp`

## License
This project is licensed under the MIT License - see the LICENSE file for details.
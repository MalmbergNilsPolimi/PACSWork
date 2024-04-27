# Challenge 2: A sparse matrix

This is a C++ library for working with matrices, supporting both row-major and column-major storage orders. The library provides functionalities for creating, manipulating, and performing operations on matrices.


## Features
- Matrix Creation: Create matrices of any size with specified values.
- Matrix Operations: Perform operations such as matrix-vector and matrix-matrix multiplication, resizing and norm (norm-1, norm-inifnite, norm-Frobenius).
- Matrix Compression: Compress matrices to save memory space when dealing with sparse matrices. The uncompress method is also implemented.
- Matrix Loading: Load matrices from files in the Matrix Market format (.mtx).


## Usage

### Creating a Matrix

To create a matrix, simply instantiate the `Matrix` class with the desired dimensions:
```
#include "matrix.hpp"

using namespace algebra;

int main() {
    // Create a 3x3 matrix with row-major storage order
    Matrix<double, StorageOrder::RowMajor> matrix(3, 3);

    // Set values
    matrix(0, 0) = 1.0;
    matrix(0, 1) = 2.0;
    // ...

    // Print the matrix
    matrix.print();

    return 0;
}

```

### Compress and uncompress a matrix

You can compress and uncompress a matrix:

```
#include "matrix.hpp"

using namespace algebra;

int main() {
    // Create a 3x3 matrix with row-major storage order
    Matrix<double, StorageOrder::RowMajor> matrix(3, 3);

    // Set values
    matrix(0, 0) = 1.0;
    matrix(0, 1) = 2.0;
    // ...

    matrix.compress()
    std::cout << "Is matrix compressed? " << (matrix.is_compressed() ? "Yes" : "No") << std::endl;

    matrix.uncompress()
    std::cout << "Is matrix compressed? " << (matrix.is_compressed() ? "Yes" : "No") << std::endl;

    return 0;
}

```


### Resizing a matrix

You can resize a matrix:

```
#include "matrix.hpp"

using namespace algebra;

int main() {
    // Create a 3x3 matrix with row-major storage order
    Matrix<double, StorageOrder::RowMajor> matrix(3, 3);

    // Set values
    matrix(0, 0) = 1.0;
    matrix(0, 1) = 2.0;
    // ...

    matrix.resize(2,2);

    // Print the resized matrix
    matrix.print();

    return 0;
}

```

### Loading a Matrix for MatrixMarket (.mtx) format

You can load a matrix from a file in the Matrix Market format (.mtx) using the `load_from_mtx method`:

```
#include "matrix.hpp"

using namespace algebra;

int main() {
    Matrix<double, StorageOrder::RowMajor> matrix(0,0);
    matrix.load_from_mtx("matrix.mtx", StorageOrder::RowMajor);

    // Print the loaded matrix
    matrix.print();

    return 0;
}

```

### Matrix Operations (*)

Perform matrix operations such as matrix-vector and matrix-matrix multiplication. The matrix and/or the vector can store
arithmetic types or `std::complex<T>` types:

```
#include <complex>
#include "matrix.hpp"

using namespace algebra;

int main() {
    Matrix<std::complex<double>, StorageOrder::RowMajor> complexMatrix(2, 2);
    complexMatrix(0, 0) = std::complex<double>(1.0, 0.0);
    complexMatrix(0, 1) = std::complex<double>(2.0, 1.0);
    complexMatrix(1, 0) = std::complex<double>(3.0, 0.0);
    complexMatrix(1, 1) = std::complex<double>(4.0, 4.0);

    std::vector<std::complex<double>> complexVec = {std::complex<double>(1.0, 0.5), std::complex<double>(2.0, 0.0)};

    auto complexResult = complexMatrix * complexVec;
    std::cout << "Complex result: ";
    for (auto val : complexResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}
```

## Matrix Operations (norm)


You can compute norms of a matrix:

```
#include <complex>
#include "matrix.hpp"

int main() {
    // Create a matrix with complex coefficients
    algebra::Matrix<std::complex<double>, algebra::StorageOrder::RowMajor> matrix(3, 3);

    matrix(0, 1) = {3.0, 4.0};
    matrix(0, 2) = {5.0, 6.0};
    matrix(1, 0) = {7.0, 8.0};
    matrix(1, 2) = {11.0, 12.0};
    matrix(2, 0) = {13.0, 14.0};
    matrix(2, 1) = {15.0, 16.0};


    // Compute and print different norms of the matrix
    std::cout << "1-Norm: " << matrix.norm<double>(algebra::NormType::One) << std::endl;
    std::cout << "Infinity-Norm: " << matrix.norm<double>(algebra::NormType::Infinity) << std::endl;
    std::cout << "Frobenius-Norm: " << matrix.norm<double>(algebra::NormType::Frobenius) << std::endl;

    return 0;
}
```


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
- `make norm`: Compiles the `test_norm.cpp` file and generates the `norm` executable in the `bin/` directory.

## Execution

After compilation, you can run the programs with the following commands:

- `make run_compress`: Runs the `compress` program.
- `make run_marketReader`: Runs the `marketReader` program.
- `make run_multiply`: Runs the `multiply` program.
- `make run_resize`: Runs the `resize` program.
- `make run_norm`: Runs the `norm` program.

## Cleaning Up

The `make clean` command removes the object files and executables generated during compilation.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
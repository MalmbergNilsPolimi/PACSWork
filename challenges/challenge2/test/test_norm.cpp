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
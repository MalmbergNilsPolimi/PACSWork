#include <complex>
#include "matrix.hpp"

int main() {
    algebra::Matrix<int, algebra::StorageOrder::RowMajor> matrix(3,3);
    algebra::Matrix<int, algebra::StorageOrder::ColumnMajor> matrix1(3,3);
    
    matrix(0, 0) = 1;
    matrix(0, 1) = 2;
    matrix(1, 1) = 3;
    matrix(2, 0) = 4;
    matrix(2, 2) = 5;

    matrix1(0, 0) = 1;
    matrix1(0, 1) = 2;
    matrix1(1, 1) = 3;
    matrix1(2, 0) = 4;
    matrix1(2, 2) = 5;

    std::vector<int> vec = {1, 2, 3};

    std::vector<int> result = matrix * vec;
    std::vector<int> result1 = matrix * vec;

    std::cout << "Result of matrix-vector multiplication:" << std::endl;
    for (const auto& element : result) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "Result of matrix1-vector multiplication:" << std::endl;
    for (const auto& element : result1) {
        std::cout << element << " ";
    }
    std::cout << std::endl;


    // std::cout << "\nTest : error when wrong dimensions in matrix-vec multiplication\n" << std::endl;
    // std::vector<int> vec1 = {1, 2, 3, 4};
    // std::vector<int> result2 = matrix * vec1;

    auto result2 = matrix * matrix;

    std::cout << "Result of matrix-matrix multiplication:" << std::endl;
    result2.print();


    auto result3 = matrix1 * matrix1;

    std::cout << "Result of matrix1-matrix1 multiplication:" << std::endl;
    result3.print();


    // std::cout << "\nTest : error when wrong dimensions in matrix-matrix multiplication\n" << std::endl;
    // algebra::Matrix<int, algebra::StorageOrder::ColumnMajor> matrix2(2,2);
    // matrix2(0, 0) = 1;
    // matrix2(0, 1) = 2;
    // matrix2(1, 1) = 3;


    // Test with std::complex<double>
    algebra::Matrix<std::complex<double>, algebra::StorageOrder::RowMajor> complexMatrix(2, 2);
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

    // Test with arithmetic types
    algebra::Matrix<double, algebra::StorageOrder::RowMajor> arithMatrix(2, 2);
    arithMatrix(0, 0) = 1.0;
    arithMatrix(0, 1) = 2.0;
    arithMatrix(1, 0) = 3.0;
    arithMatrix(1, 1) = 4.0;

    std::vector<double> arithVec = {1.0, 2.0};

    auto arithResult = arithMatrix * arithVec;
    std::cout << "Arithmetic result: ";
    for (auto val : arithResult) {
        std::cout << val << " ";
    }
    std::cout << std::endl;


    return 0;
}

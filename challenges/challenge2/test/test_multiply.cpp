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


    std::cout << "\nTest : error when wrong dimensions\n" << std::endl;
    std::vector<int> vec1 = {1, 2, 3, 4};
    std::vector<int> result2 = matrix * vec1;

    return 0;
}

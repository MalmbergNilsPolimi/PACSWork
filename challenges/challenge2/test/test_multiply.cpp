#include "matrix.hpp"

int main() {
    algebra::Matrix<int, algebra::StorageOrder::RowMajor> matrix(3,3);
    
    matrix(0, 0) = 1;
    matrix(0, 1) = 2;
    matrix(1, 1) = 3;
    matrix(2, 0) = 4;
    matrix(2, 2) = 5;


    std::vector<int> vec = {1, 2, 3};

    std::vector<int> result = matrix * vec;

    std::cout << "Result of matrix-vector multiplication:" << std::endl;
    for (const auto& element : result) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}

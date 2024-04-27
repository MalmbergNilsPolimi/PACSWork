#include "matrix.hpp"

int main() {
    using namespace algebra;

    // Creation of dynamic matrices (row abd column major).
    Matrix<int, StorageOrder::RowMajor> matrix(4,6);
    Matrix<int, StorageOrder::ColumnMajor> matrix1(4,6);

    matrix(0, 0) = 10;
    matrix(0, 1) = 20;
    matrix(1, 1) = 30;
    matrix(1, 3) = 40;
    matrix(2, 2) = 50;
    matrix(2, 3) = 60;
    matrix(2, 4) = 70;
    matrix(3, 5) = 80;

    matrix1(0, 0) = 10;
    matrix1(0, 1) = 20;
    matrix1(1, 1) = 30;
    matrix1(1, 3) = 40;
    matrix1(2, 2) = 50;
    matrix1(2, 3) = 60;
    matrix1(2, 4) = 70;
    matrix1(3, 5) = 80;


    // Print Matrix.
    std::cout << "matrix before resizing:" << std::endl;
    matrix.print();
    std::cout << std::endl;

    // Check if compressed.
    std::cout << "Is matrix compressed? " << (matrix.is_compressed() ? "Yes" : "No") << std::endl;

    // Resizing.
    matrix.resize(2,2);
    
    // Print resized matrix.
    std::cout << "Resized matrix dimensions: " << matrix.rows << " rows x " << matrix.cols << " columns" << std::endl;
    std::cout << "Resized matrix:" << std::endl;
    matrix.print();
    std::cout << std::endl;



    // Print Matrix1.
    std::cout << "matrix1 before resizing:" << std::endl;
    matrix1.print();
    std::cout << std::endl;

    // Compressing matrix1.
    matrix1.compress();

    // Check if compressed.
    std::cout << "Is matrix compressed? " << (matrix1.is_compressed() ? "Yes" : "No") << std::endl;

    // Resizing.
    matrix1.resize(3,3);
    
    // Print resized matrix.
    std::cout << "Resized matrix dimensions: " << matrix1.rows << " rows x " << matrix1.cols << " columns" << std::endl;
    std::cout << "Resized matrix1:" << std::endl;
    matrix1.print();
    std::cout << std::endl;

    // Check if compressed.
    std::cout << "Is matrix compressed? " << (matrix1.is_compressed() ? "Yes" : "No") << std::endl;

    return 0;
}
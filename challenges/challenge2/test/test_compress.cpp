#include "matrix.hpp"

int main() {
    using namespace algebra;

    // Creation of a dynamique matrix (row or column major).
    Matrix<int, StorageOrder::RowMajor> matrix;
    //Matrix<int, StorageOrder::ColumnMajor> matrix;

    matrix(0, 0) = 10;
    matrix(0, 1) = 20;
    matrix(1, 1) = 30;
    matrix(1, 3) = 40;
    matrix(2, 2) = 50;
    matrix(2, 3) = 60;
    matrix(2, 4) = 70;
    matrix(3, 5) = 80;

    // Print Matrix.
    std::cout << "Matrix before compression:" << std::endl;
    matrix.print();
    std::cout << std::endl;

    // Compression.
    matrix.compress();

    // Print data compression.
    std::cout << "Compressed data:" << std::endl;
    std::cout << "Row indices: ";
    for (auto idx : matrix.row_indices) {
        std::cout << idx << " ";
    }
    std::cout << std::endl;

    std::cout << "Column indices: ";
    for (auto idx : matrix.col_indices) {
        std::cout << idx << " ";
    }
    std::cout << std::endl;

    std::cout << "Values: ";
    for (auto val : matrix.values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Check if compressed.
    std::cout << "Is matrix compressed? " << (matrix.is_compressed() ? "Yes" : "No") << std::endl;

    std::cout << std::endl;
    
    // Uncompression.
    matrix.uncompress();

    // Print Matrix.
    std::cout << "Matrix after uncompression:" << std::endl;
    matrix.print();
    std::cout << std::endl;

    // Check if uncompressed.
    std::cout << "Is matrix compressed? " << (matrix.is_compressed() ? "Yes" : "No") << std::endl;

    return 0;
}
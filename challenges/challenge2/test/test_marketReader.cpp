#include <chrono>
#include "matrix.hpp"

int main() {

    algebra::Matrix<double, algebra::StorageOrder::RowMajor> row_major_matrix(0,0);
    algebra::Matrix<double, algebra::StorageOrder::ColumnMajor> col_major_matrix(0,0);

    
    try {
        row_major_matrix.load_from_mtx("MatrixMarket/lnsp_131.mtx", algebra::StorageOrder::RowMajor);
        std::cout << "Row major matrix loaded successfully." << std::endl;
        //row_major_matrix.print();

        std::vector<double> vec(row_major_matrix.cols, 1.0);

        auto start = std::chrono::steady_clock::now();
        auto result_uncompressed_row_major = row_major_matrix * vec;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration_uncompressed_row_major = end - start;

        row_major_matrix.compress();

        start = std::chrono::steady_clock::now();
        auto result_compressed_row_major = row_major_matrix * vec;
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration_compressed_row_major = end - start;


        std::cout << "Uncompressed (Row Major) Time: " << duration_uncompressed_row_major.count() << " seconds" << std::endl;
        std::cout << "Compressed (Row Major) Time: " << duration_compressed_row_major.count() << " seconds" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error loading row major matrix: " << e.what() << std::endl;
    }

    std::cout << std::endl;

    try {
        col_major_matrix.load_from_mtx("MatrixMarket/lnsp_131.mtx", algebra::StorageOrder::ColumnMajor);
        std::cout << "Column major matrix loaded successfully." << std::endl;
        //col_major_matrix.print();

        std::vector<double> vec1(col_major_matrix.cols, 1.0);

        auto start1 = std::chrono::steady_clock::now();
        auto result_uncompressed_col_major = col_major_matrix * vec1;
        auto end1 = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration_uncompressed_col_major = end1 - start1;

        col_major_matrix.compress();

        start1 = std::chrono::steady_clock::now();
        auto result_compressed_col_major = col_major_matrix * vec1;
        end1 = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration_compressed_col_major = end1 - start1;
        
        std::cout << "Uncompressed (Column Major) Time: " << duration_uncompressed_col_major.count() << " seconds" << std::endl;
        std::cout << "Compressed (Column Major) Time: " << duration_compressed_col_major.count() << " seconds" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error loading column major matrix: " << e.what() << std::endl;
    }
    

    return 0;
}
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <map>
#include <array>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace algebra {

    enum class StorageOrder { RowMajor, ColumnMajor };

    template<typename T, StorageOrder Order>
    class Matrix {
    private:
        std::map<std::array<std::size_t, 2>, T> data;
        bool compressed = false;


    public:
        // Constructor taking matrix size
        Matrix(std::size_t rows, std::size_t cols) : rows(rows), cols(cols) {}

        std::vector<std::size_t> row_indices;
        std::vector<std::size_t> col_indices;
        std::vector<T> values;
        std::size_t rows = 0;
        std::size_t cols = 0;

        // Non-const call operator for inserting values.
        T& operator()(std::size_t i, std::size_t j) {
            if (compressed) {
                throw std::runtime_error("Cannot modify elements in compressed state. Please uncompress the matrix first.");
            } else {
                return data[{i, j}];
            }
        }

        // Const call operator for accessing values.
        const T& operator()(std::size_t i, std::size_t j) const {
            auto it = data.find({i, j});
            if (it == data.end()) {
                return 0;
            } else {
                return it->second;
            }
        }

        // Print the matrix.
        void print() const {
            for (const auto& pair : data) {
                std::cout << "(" << pair.first[0] << ", " << pair.first[1] << ") -> " << pair.second << std::endl;
            }
        }

        // Method to compress the matrix.
        void compress() {
            if (compressed) return;

            // Clear compressed data vectors.
            row_indices.clear();
            col_indices.clear();
            values.clear();

            // Calculate row count.
            std::size_t rowCount = 0;
            for (const auto& pair : data) {
                rowCount = std::max(rowCount, pair.first[0] + 1);
            }

            //Calculate col count.
            std::size_t colCount = 0;
            for (const auto& pair : data) {
                colCount = std::max(colCount, pair.first[1] + 1);
            }

            if constexpr (Order == StorageOrder::RowMajor) {
                // Compress row-major ordered matrix.
                for (std::size_t i = 0; i < rowCount; ++i) {
                    row_indices.push_back(col_indices.size()); // number of elements above.

                    for (const auto& pair : data) {
                        const auto& indices = pair.first;
                        const auto& value = pair.second;
                        if (indices[0] == i) {
                            col_indices.push_back(indices[1]);
                            values.push_back(value);
                        }
                    }
                }
                row_indices.push_back(col_indices.size());

            } else {
                // Compress column-major ordered matrix.
                for (std::size_t i = 0; i < colCount; ++i) {
                    col_indices.push_back(row_indices.size()); // number of elements above.

                    for (const auto& pair : data) {
                        const auto& indices = pair.first;
                        const auto& value = pair.second;
                        if (indices[1] == i) {
                            row_indices.push_back(indices[0]);
                            values.push_back(value);
                        }
                    }
                }
                col_indices.push_back(row_indices.size());
            }

            // Clear the map after compression.
            data.clear();
            compressed = true;
        }

        // Method to uncompress the matrix.
        void uncompress() {
            if (!compressed) return;

            if constexpr (Order == StorageOrder::RowMajor) {
                // Uncompress row-major ordered matrix.
                for (std::size_t i = 0; i < row_indices.size() - 1; ++i) {
                    const std::size_t start = row_indices[i];
                    const std::size_t end = row_indices[i + 1];
                    for (std::size_t k = start; k < end; ++k) {
                        const std::size_t j = col_indices[k];
                        const T& value = values[k];
                        data[{i, j}] = value;
                    }
                }

            } else {
                // Uncompress column-major ordered matrix.
                for (std::size_t i = 0; i < col_indices.size() - 1; ++i) {
                    const std::size_t start = col_indices[i];
                    const std::size_t end = col_indices[i + 1];
                    for (std::size_t k = start; k < end; ++k) {
                        const std::size_t j = row_indices[k];
                        const T& value = values[k];
                        data[{j, i}] = value;
                    }
                }
            }

            row_indices.clear();
            col_indices.clear();
            values.clear();
            compressed = false;
        }

        // Method to check if the matrix is compressed.
        bool is_compressed() const {
            return compressed;
        }

        // Method to resize the matrix
        void resize(std::size_t new_rows, std::size_t new_cols) {
            if (compressed) {
                uncompress();
            }
            rows = new_rows;
            cols = new_cols;
            
            std::map<std::array<std::size_t, 2>, T> new_data;
            for (const auto& pair : data) {
                if (pair.first[0] < new_rows && pair.first[1] < new_cols) {
                    new_data[pair.first] = pair.second;
                }
            }
            
            data = std::move(new_data);
            compressed = false; 
        }
    
        // Friend operator for matrix-vector multiplication
        friend std::vector<T> operator*(const Matrix<T, Order>& matrix, const std::vector<T>& vec) {
            std::vector<T> result;

            if constexpr (Order == StorageOrder::RowMajor) {
                if (matrix.cols != vec.size()) {
                    throw std::invalid_argument("Matrix and vector dimensions are not compatible for multiplication");
                }
            } else {
                if (matrix.rows != vec.size()) {
                    throw std::invalid_argument("Matrix and vector dimensions are not compatible for multiplication");
                }
            }

            if constexpr (Order == StorageOrder::RowMajor) {
                for (std::size_t i = 0; i < matrix.rows; ++i) {
                    T sum = 0;
                    for (const auto& pair : matrix.data) {
                        if (pair.first[0] == i) {
                            sum += pair.second * vec[pair.first[1]];
                        }
                    }
                    result.push_back(sum);
                }
            } else {
                for (std::size_t j = 0; j < matrix.cols; ++j) {
                    T sum = 0;
                    for (const auto& pair : matrix.data) {
                        if (pair.first[1] == j) {
                            sum += pair.second * vec[pair.first[0]];
                        }
                    }
                    result.push_back(sum);
                }
            }
            return result;
        }

    };
}

#endif // MATRIX_HPP
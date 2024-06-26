#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <map>
#include <array>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <complex>
#include <cmath>

namespace algebra {

    enum class StorageOrder { RowMajor, ColumnMajor };
    enum class NormType { One, Infinity, Frobenius };
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
            static T default_value{0};
            if (it == data.end()) {
                return default_value;
            } else {
                return it->second;
            }
        }

        // Print the matrix.
        void print() const {
            for (const auto& pair : data) {
                std::cout << "(" << pair.first[0] << ", " << pair.first[1] << ") -> " << std::scientific << pair.second << std::endl;
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
          
        // Method to remove zeros from the matrix
        void remove_zeros() {
            if (compressed) {
                uncompress();
            }
            
            std::map<std::array<std::size_t, 2>, T> new_data;
            for (const auto& pair : data) {
                if (pair.second != 0) {
                    new_data[pair.first] = pair.second;
                }
            }
            
            data = std::move(new_data);
        }

        // Friend operator for matrix-vector multiplication
        template<typename U = T>
        friend std::vector<decltype(std::declval<U>() * std::declval<U>())> operator*(const Matrix<T, Order>& matrix, const std::vector<T>& vec) {
            std::vector<decltype(std::declval<U>() * std::declval<U>())> result;

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
                    auto sum = U(0);
                    for (const auto& pair : matrix.data) {
                        if (pair.first[0] == i) {
                            sum += pair.second * vec[pair.first[1]];
                        }
                    }
                    result.push_back(sum);
                }
            } else {
                for (std::size_t j = 0; j < matrix.cols; ++j) {
                    auto sum = U(0);
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

        // Friend operator for matrix-matrix multiplication
        template<typename U = T>
        friend Matrix<decltype(std::declval<U>() * std::declval<U>()), Order> operator*(const Matrix<T, Order>& matrix1, const Matrix<T, Order>& matrix2) {
            // Check if dimensions are compatible for multiplication
            if constexpr (Order == StorageOrder::RowMajor) {
                if (matrix1.cols != matrix2.rows) {
                    throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
                }
            } else {
                if (matrix1.rows != matrix2.cols) {
                    throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
                }
            }

            // Create a result matrix with appropriate dimensions
            Matrix<decltype(std::declval<U>() * std::declval<U>()), Order> result(matrix1.rows, matrix2.cols);

            // Perform matrix multiplication
            if constexpr (Order == StorageOrder::RowMajor)
            {
                for (std::size_t i = 0; i < matrix1.rows; ++i) {
                    for (std::size_t j = 0; j < matrix2.cols; ++j) {
                        auto& element = result(i, j);
                        element = U(0);
                        for (std::size_t k = 0; k < matrix1.cols; ++k) {
                            element += matrix1(i, k) * matrix2(k, j);
                        }
                    }
                }
            } else {
                for (std::size_t i = 0; i < matrix1.cols; ++i) {
                    for (std::size_t j = 0; j < matrix2.cols; ++j) {
                        auto& element = result(j, i);
                        element = U(0);
                        for (std::size_t k = 0; k < matrix1.rows; ++k) {
                            element += matrix1(k, i) * matrix2(j, k);
                        }
                    }
                }
            }           

            result.remove_zeros();
            return result;
        }

        // Method to load a .mtx matrix.
        void load_from_mtx(const std::string& filename, StorageOrder order) {

            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Unable to open file: " + filename);
            }

            std::string line;
            std::size_t rows = 0, cols = 0, nonZeros = 0;
            while (std::getline(file, line)) {
                if (line[0] == '%') continue;
                std::stringstream ss(line);
                ss >> rows >> cols >> nonZeros;
                break;
            }

            resize(rows, cols);

            while (std::getline(file, line)) {
                if (line[0] == '%') continue;
                std::stringstream ss(line);
                std::size_t row, col;
                T value;
                ss >> row >> col >> value;

                if (order == StorageOrder::RowMajor) {
                    (*this)(row - 1, col - 1) = value;
                } else {
                    (*this)(col - 1, row - 1) = value;
                }
            }

            file.close();
        }

        // Method to compute the norm of the matrix
        template<typename U>
            U norm(NormType type) const {
                if (type == NormType::One) {
                    U max_sum = 0;
                    for (std::size_t j = 0; j < cols; ++j) {
                        U column_sum = 0;
                        for (std::size_t i = 0; i < rows; ++i) {
                            column_sum += std::abs((*this)(i, j));
                        }
                        max_sum = std::max(max_sum, column_sum);
                    }
                    return max_sum;
                } else if (type == NormType::Infinity) {
                    U max_sum = 0;
                    for (std::size_t i = 0; i < rows; ++i) {
                        U row_sum = 0;
                        for (std::size_t j = 0; j < cols; ++j) {
                            row_sum += std::abs((*this)(i, j));
                        }
                        max_sum = std::max(max_sum, row_sum);
                    }
                    return max_sum;
                } else if (type == NormType::Frobenius) {
                    U frobenius_sum = 0;
                    for (const auto& pair : data) {
                        frobenius_sum += std::norm(pair.second);
                    }
                    return std::sqrt(frobenius_sum);
                } else {
                    throw std::invalid_argument("Invalid norm type");
                }
            }



    };
}

#endif // MATRIX_HPP
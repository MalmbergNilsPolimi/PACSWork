#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <map>
#include <array>
#include <vector>
#include <iostream>

namespace algebra {

    enum class StorageOrder { RowMajor, ColumnMajor };

    template<typename T, StorageOrder Order>
    class Matrix {
    private:
        std::map<std::array<std::size_t, 2>, T> data;
        bool compressed = false;


    public:
        // Constructors.
        Matrix() = default;
        std::vector<std::size_t> row_indices;
        std::vector<std::size_t> col_indices;
        std::vector<T> values;

        // Non-const call operator for inserting values.
        T& operator()(std::size_t i, std::size_t j) {
            if constexpr(Order == StorageOrder::RowMajor)
                return data[{i, j}];
            else
                return data[{j, i}];
        }

        // Const call operator for accessing values.
        const T& operator()(std::size_t i, std::size_t j) const {
            if constexpr(Order == StorageOrder::RowMajor)
                return data.at({i, j});
            else
                return data.at({j, i});
        }

        // Print the matrix.
        void print() const {
            if constexpr (Order == StorageOrder::RowMajor) {
                for (const auto& pair : data) {
                    std::cout << "(" << pair.first[0] << ", " << pair.first[1] << ") -> " << pair.second << std::endl;
                }
            } else {
            
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

            // Calculate col count.
            // std::size_t colCount = 0;
            // for (const auto& pair : data) {
            //     colCount = std::max(colCount, pair.first[1] + 1);
            // }

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
    };
}

#endif // MATRIX_HPP
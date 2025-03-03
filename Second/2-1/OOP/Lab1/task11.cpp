#include <iostream>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> data;  // 2D vector for dynamic matrix
    int rows;    // Number of rows
    int cols;    // Number of columns

public:
    // Constructor to allocate memory and initialize matrix
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<int>(cols, 0)); // Initialize all elements to 0
    }

    // Method to set value at specific position
    void setValue(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = value;
        }
    }

    // Method to get value at specific position
    int getValue(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        }
        return -1; // Error value for invalid indices
    }

    // Input matrix elements from the keyboard
    void inputMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "Enter element [" << i << "][" << j << "]: ";
                std::cin >> data[i][j];
            }
        }
    }

    // Method to set predefined example matrix
    void setExampleMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = i * cols + j + 1;  // Example: filling with sequential numbers
            }
        }
    }

    // Display the matrix
    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Matrix addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cerr << "Error: Matrices must have the same dimensions for addition" << std::endl;
            return Matrix(0, 0); // Return empty matrix on error
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.setValue(i, j, data[i][j] + other.getValue(i, j));
            }
        }
        return result;
    }

    // Matrix subtraction
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cerr << "Error: Matrices must have the same dimensions for subtraction" << std::endl;
            return Matrix(0, 0); // Return empty matrix on error
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.setValue(i, j, data[i][j] - other.getValue(i, j));
            }
        }
        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            std::cerr << "Error: Number of columns of the first matrix must be equal to the number of rows of the second matrix" << std::endl;
            return Matrix(0, 0); // Return empty matrix on error
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += data[i][k] * other.getValue(k, j);
                }
                result.setValue(i, j, sum);
            }
        }
        return result;
    }

   // Calculate sum of elements of each row
    std::vector<int> rowSums() const {
        std::vector<int> sums(rows, 0);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sums[i] += data[i][j];
            }
        }
        return sums;
    }

    // Calculate sum of elements of each column
    std::vector<int> colSums() const {
        std::vector<int> sums(cols, 0);
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                sums[j] += data[i][j];
            }
        }
        return sums;
    }
};


int main() {
    // Create a 3x3 matrix and input values
    Matrix mat1(3, 3);
    
    // Fill matrix with predefined example values
    mat1.setExampleMatrix();
    std::cout << "Example matrix:" << std::endl;
    mat1.display();
    std::cout << "\n";

    // Now, fill another matrix manually with input from keyboard
    Matrix mat2(3, 3);
    std::cout << "Enter elements for the second matrix:" << std::endl;
    mat2.inputMatrix();
    std::cout << "\n";
    std::cout << "Your matrix:" << std::endl;
    mat2.display();
    std::cout << "\n";

    // Add the two matrices
    Matrix sum = mat1 + mat2;
    std::cout << "Sum of matrices:" << std::endl;
    sum.display();
    std::cout << "\n";

    // Subtract the two matrices
    Matrix diff = mat1 - mat2;
    std::cout << "Difference of matrices:" << std::endl;
    diff.display();
    std::cout << "\n";

    // Multiply the two matrices
    Matrix product = mat1 * mat2;
    std::cout << "Product of matrices:" << std::endl;
    product.display();
    std::cout << "\n";

    // Calculate row and column sums for mat1
    std::vector<int> row_sums = mat1.rowSums();
    std::vector<int> col_sums = mat1.colSums();

    // Display row sums
    std::cout << "Row sums for mat1:" << std::endl;
    for (int i = 0; i < row_sums.size(); i++) {
        std::cout << "Row " << i << ": " << row_sums[i] << std::endl;
    }
    std::cout << "\n";

    // Display column sums
    std::cout << "Column sums for mat1:" << std::endl;
    for (int i = 0; i < col_sums.size(); i++) {
        std::cout << "Column " << i << ": " << col_sums[i] << std::endl;
    }
    std::cout << "\n";

    return 0;
}


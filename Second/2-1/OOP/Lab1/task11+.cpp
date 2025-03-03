#include <iostream>

class Matrix {
private:
    int** data;
    int rows;
    int cols;

public:
    // Constructor by default
    Matrix() : data(nullptr), rows(0), cols(0) {}

    // Constructor to create matrices rows
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        if (rows > 0 && cols > 0) {
            data = new int*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols]();
            }
        } else {
            data = nullptr;
        }
    }

    // Constructor to create matrices columns
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        if (rows > 0 && cols > 0) {
            data = new int*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        } else {
            data = nullptr;
        }
    }

    // Destructor of a matrix
    ~Matrix() {
        if (data) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
    }

    // Method to set a value of matrix
    void setValue(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = value;
        }
    }

    // Method to get a value from a matrix
    int getValue(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        }
        return 0;
    }

    // Method to input a matrices value
    void inputMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "Введи значение элемента [" << i << "][" << j << "]: ";
                std::cin >> data[i][j];
            }
        }
    }

    // Method to create an example matrix
    void setExampleMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = i * cols + j + 1;  
            }
        }
    }

    // Method to display user's matrix
    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    
    // Operator of assignment
    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;

        rows = other.rows;
        cols = other.cols;
        if (rows > 0 && cols > 0) {
            data = new int*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        } else {
            data = nullptr;
        }
        return *this;
    }

    // Operator of sum
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cerr << "Ошибка: матрицы должны быть одинакового размера для сложения" << std::endl;
            return Matrix();
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.setValue(i, j, data[i][j] + other.getValue(i, j));
            }
        }
        return result;
    }

    // Operator of substitution
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cerr << "Ошибка: матрицы должны быть одинакового размера для вычитания" << std::endl;
            return Matrix();
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.setValue(i, j, data[i][j] - other.getValue(i, j));
            }
        }
        return result;
    }

    // Operator of multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            std::cerr << "Ошибка: количество столбцов первой матрицы должно быть равно количеству строк второй матрицы" << std::endl;
            return Matrix();
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += data[i][k] * other.getValue(k, j);  // Правильное накопление произведений
                }
                result.setValue(i, j, sum);
            }
        }
        return result;
    }

    // Method to find rows sum
    int* rowSums() const {
        int* sums = new int[rows]();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sums[i] += data[i][j];
            }
        }
        return sums;
    }

    // Method to find columns sum
    int* colSums() const {
        int* sums = new int[cols]();
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                sums[j] += data[i][j];
            }
        }
        return sums;
    }
};

// Main function (entering point)
int main() {
    Matrix mat1(3, 3);
    mat1.setExampleMatrix();
    std::cout << "Пример матрицы:" << std::endl;
    mat1.display();
    std::cout << "\n";

    Matrix mat2(3, 3);
    std::cout << "Введите элементы для второй матрицы:" << std::endl;
    mat2.inputMatrix();
    std::cout << "\n";
    std::cout << "Ваша матрица:" << std::endl;
    mat2.display();
    std::cout << "\n";

    Matrix sum = mat1 + mat2;
    std::cout << "Сумма матриц:" << std::endl;
    sum.display();
    std::cout << "\n";

    Matrix difference = mat1 - mat2;
    std::cout << "Разность матриц:" << std::endl;
    difference.display();
    std::cout << "\n";

    Matrix product = mat1 * mat2;
    std::cout << "Произведение матриц:" << std::endl;
    product.display();
    std::cout << "\n";

    int* row_sums = mat1.rowSums();
    int* col_sums = mat1.colSums();

    std::cout << "Суммы строк для mat1:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "Строка " << i << ": " << row_sums[i] << std::endl;
    }
    std::cout << "\n";

    std::cout << "Суммы столбцов для mat1:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "Столбец " << i << ": " << col_sums[i] << std::endl;
    }
    std::cout << "\n";

    delete[] row_sums;
    delete[] col_sums;

    return 0;
}

//
// Matrix Class Implementation
//

#include "matrix.h"
#include <iostream>
#include <sstream>

using namespace std;

// Deallocate dynamic memory used by matrix
void Matrix::deallocateMemory() {
    if (mat) {
        for (int i = 0; i < rows; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
    }
}

// Default constructor
Matrix::Matrix() : mat(nullptr), rows(0), cols(0) {}

// Parameterized constructor
Matrix::Matrix(int r, int c) : mat(nullptr), rows(r), cols(c) {
    if (r < 0 || c < 0) {
        throw invalid_argument("the number of rows/columns must be a non-negative number");
    }
    if (r > 0 && c > 0) {
        mat = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            mat[i] = new double[cols];
        }
    }
}

// Destructor
Matrix::~Matrix() {
    deallocateMemory();
}

// Copy constructor
Matrix::Matrix(const Matrix& other) : mat(nullptr), rows(other.rows), cols(other.cols) {
    if (rows > 0 && cols > 0) {
        mat = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            mat[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                mat[i][j] = other.mat[i][j];
            }
        }
    }
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        this->deallocateMemory();

        this->rows = other.rows;
        this->cols = other.cols;

        mat = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            mat[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                mat[i][j] = other.mat[i][j];
            }
        }
    }
    return *this;
}

// Input operator >> to populate matrix from input stream
istream& operator>>(istream& is, Matrix& m) {
    int nRows, nCols;
    is >> nRows >> nCols;

    Matrix temp(nRows, nCols);
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            is >> temp.mat[i][j];
        }
    }
    m = temp;
    return is;
}

// Output operator << to print matrix
ostream& operator<<(ostream& os, Matrix& m) {
    if (m.rows == 0 || m.cols == 0) {
        os << "[]" << endl;
        return os;
    }

    os << "[";
    for (int i = 0; i < m.rows; ++i) {
        if (i != 0) os << " ";
        os << "[";
        for (int j = 0; j < m.cols; j++) {
            os << m.mat[i][j];
            if (j < m.cols - 1) os << ", ";
        }
        os << "]";
        if (i < m.rows - 1) os << ", " << endl;
    }
    os << "]\n";
    return os;
}

// Matrix addition
Matrix Matrix::operator+(const Matrix& other) {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw invalid_argument("matrix sizes must be the same for addition");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
    }
    return result;
}

// In-place matrix subtraction
void Matrix::operator-(const Matrix& other){
    if (this->rows != other.rows || this->cols != other.cols) {
        throw invalid_argument("matrix sizes must be the same for addition");
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] -= other.mat[i][j];
        }
    }
}

// Scalar multiplication
Matrix Matrix::operator*(const double scalar) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.mat[i][j] = mat[i][j] * scalar;
        }
    }
    return result;
}

// Scalar division
Matrix Matrix::operator/(const double scalar) {
    if (scalar == 0) {
        throw invalid_argument("cannot divide by 0");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.mat[i][j] = mat[i][j] / scalar;
        }
    }
    return result;
}

// Matrix dot product
Matrix Matrix::dotProduct(const Matrix& other) {
    if (cols != other.rows) {
        throw invalid_argument("matrix dot product is not possible because invalid dimensions");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            result.mat[i][j] = 0;
            for (int k = 0; k < cols; ++k) {
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }
    return result;
}

// Compute sum of elements in another matrix
double Matrix::getSum(const Matrix& other) {
    double sum = 0;
    for (int i = 0; i < other.rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            sum += other.mat[i][j];
        }
    }
    return sum;
}

// Compute sum of elements in this matrix
double Matrix::getSum() {
    double sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += mat[i][j];
        }
    }
    return sum;
}

// Comparison operators based on sum of elements
bool Matrix::operator<(const Matrix& other)  { return getSum() < getSum(other); }
bool Matrix::operator<=(const Matrix& other) { return getSum() <= getSum(other); }
bool Matrix::operator>(const Matrix& other)  { return getSum() > getSum(other); }
bool Matrix::operator>=(const Matrix& other) { return getSum() >= getSum(other); }
bool Matrix::operator==(const Matrix& other) { return getSum() == getSum(other); }
bool Matrix::operator!=(const Matrix& other) { return getSum() != getSum(other); }

// Increment operator: mat[i][j] += i * j
void Matrix::operator++() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] += i * j;
        }
    }
}

// Decrement operator: reset matrix to zero
void Matrix::operator--() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] = 0;
        }
    }
}

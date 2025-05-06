//
// Matrix Class Declaration
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <sstream>

using namespace std;

class Matrix {
private:
    double** mat;   // 2D array to store matrix values
    int rows;       // Number of rows
    int cols;       // Number of columns

    // Utility to deallocate dynamic memory
    void deallocateMemory();

    // Internal helper to compute sum of all elements (used for comparisons)
    double getSum(const Matrix& other);
    double getSum();

public:
    // Constructors
    Matrix();                 // Default constructor
    Matrix(int r, int c);     // Parameterized constructor

    // Destructor
    ~Matrix();

    // Copy constructor and assignment operator
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    // I/O stream operators
    friend istream& operator>>(istream& is, Matrix& m); // Input operator
    friend ostream& operator<<(ostream& os, Matrix& m); // Output operator

    // Arithmetic operators
    Matrix operator+(const Matrix& other);              // Matrix addition
    void operator-(const Matrix& other);                // In-place matrix subtraction
    Matrix operator*(const double scalar);              // Scalar multiplication
    Matrix operator/(const double scalar);              // Scalar division
    Matrix dotProduct(const Matrix& other);             // Matrix dot product

    // Comparison operators based on matrix element sum
    bool operator<(const Matrix& other);
    bool operator<=(const Matrix& other);
    bool operator>(const Matrix& other);
    bool operator>=(const Matrix& other);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);

    // Unary operators
    void operator++(); // Increment: mat[i][j] += i * j
    void operator--(); // Reset all matrix elements to 0
};

#endif

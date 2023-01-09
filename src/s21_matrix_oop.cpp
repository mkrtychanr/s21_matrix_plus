#include "s21_matrix_oop.h"
#include <iostream>
#include <cmath>

S21Matrix::S21Matrix() {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
}

S21Matrix::S21Matrix(const int rows, const int cols) {
    this->~S21Matrix();
    if (rows < 1 || cols < 1) {
        throw std::logic_error("Invalid matrix size");
    }
    rows_ = rows;
    cols_ = cols;
    matrix_ = (double**)malloc(rows * sizeof(double*));
    if (matrix_ == nullptr) {
        throw "Can't allocate memory";
    }
    for (int i = 0; i < cols; i++) {
        matrix_[i] = (double*)malloc(cols * sizeof(double));
        if (matrix_[i] == nullptr) {
            throw "Can't allocate memory";
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix_[i][j] = 0;
        }
    }
}

S21Matrix::S21Matrix(const S21Matrix& rhs) {
    operator=(rhs);
}

S21Matrix::S21Matrix(S21Matrix&& rhs) {
    this->~S21Matrix();
    this -> rows_ = rhs.rows_;
    this -> cols_ = rhs.cols_;
    this -> matrix_ = rhs.matrix_;
    rhs.rows_ = 0;
    rhs.cols_ = 0;
    rhs.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    if (isValidMatrix()) {
        for(int i = 0; i < rows_; i++) {
            free(matrix_[i]);
        }
        free(matrix_);
    }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& rhs) {
    if (!rhs.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (this != &rhs) {
        this -> ~S21Matrix();
        auto temp = S21Matrix(rhs.rows_, rhs.cols_);
        for (int i = 0; i < temp.rows_; i++) {
            for (int j = 0; j < temp.cols_; j++) {
                temp.matrix_[i][j] = rhs.matrix_[i][j];
            }
        }
        this -> rows_= temp.rows_;
        this -> cols_= temp.cols_;
        this -> matrix_ = temp.matrix_;
        temp.matrix_ = nullptr;
    }
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& rhs) {
    SumMatrix(rhs);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& rhs) {
    SubMatrix(rhs);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const double& rhs) {
    MulNumber(rhs);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& rhs) {
    MulMatrix(rhs);
    return *this;
}

double& S21Matrix::operator()(int i, int j) {
    if (i >= rows_ || j >= cols_) {
        throw std::logic_error("Invalid index");
    }
    return matrix_[i][j];
}

bool S21Matrix::EqMatrix(const S21Matrix& rhs) const {
    if (!isValidMatrix() || !rhs.isValidMatrix()) {
        throw std::logic_error("Invalid Matrix");
    }
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
        return false;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (matrix_[i][j] != rhs.matrix_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void S21Matrix::SumMatrix(const S21Matrix& rhs) {
    if (!isValidMatrix() || !rhs.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
        throw std::logic_error("Invalid operation!");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += rhs.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& rhs) {
    if (!isValidMatrix() || !rhs.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
        throw std::logic_error("Invalid operation!");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= rhs.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double& rhs) {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= rhs;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& rhs) {
    if (!isValidMatrix() || !rhs.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (cols_ != rhs.rows_) {
        throw std::logic_error("Invalid operation");
    }
    S21Matrix result = S21Matrix(rows_, rhs.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < rhs.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                result.matrix_[i][j] += matrix_[i][k] * rhs.matrix_[k][j];
            }
        }
    }
    *this = S21Matrix(std::move(result));
}

S21Matrix S21Matrix::Transpose() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    S21Matrix result = S21Matrix(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != cols_) {
        throw std::logic_error("Invalid operation");
    }
    S21Matrix result = S21Matrix(rows_, rows_);
    if (rows_ == 1) {
        result.matrix_[0][0] = matrix_[0][0];
    } else {
        result.fillMatrixWithMinors(*this);
    }
    return result;
}

double S21Matrix::Determinant() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != cols_) {
        throw std::logic_error("Invalid operation");
    }
    return det(matrix_, rows_);
}

S21Matrix S21Matrix::InverseMatrix() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != cols_) {
        throw std::logic_error("Invalid operation");
    }
    double matrixDeterminant = Determinant();
    if (fabs(matrixDeterminant - 0) <= 1E-7) {
        throw std::logic_error("Invalid operation");
    }
    S21Matrix result = CalcComplements().Transpose();
    result.MulNumber(1/matrixDeterminant);
    return result;
}

int S21Matrix::GetRows() const {
    return rows_;
}

int S21Matrix::GetCols() const {
    return cols_;
}

void S21Matrix::SetRows(const int rows) {
    this -> rows_ = rows;
}

void S21Matrix::SetCols(int cols) {
    this -> cols_ = cols;
}

bool S21Matrix::isValidMatrix() const {
    return matrix_ != nullptr;
}


void S21Matrix::new_pointer(double **a, double *b) const {
    *a = b;
}

double S21Matrix::det(double **a, int n) const {
    if (n == 1) {
        return a[0][0];
    }
    if (n == 2) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    int number = 0;
    double sum = 0;
    double **temp = (double**)malloc((n-1) * sizeof(double*));
    for (int i = 0; i < n; i++) {
        number = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            new_pointer(&temp[number++], a[j]);
        }
        sum +=  pow(-1, i + n - 1) * a[i][n-1] * det(temp, n - 1);
    }
    free(temp);
    return sum;
}

void S21Matrix::fillMatrixWithMinors(const S21Matrix& rhs) const {
    if (rows_ == 1) {
        matrix_[0][0] = rhs.matrix_[0][0];
        return;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = pow(-1, i * rhs.rows_ + j) * rhs.getMatrixForMinor(i, j).Determinant();
        }
    }
}

S21Matrix S21Matrix::getMatrixForMinor(int row, int col) const {
    S21Matrix result = S21Matrix(rows_ - 1, cols_ - 1);
    int new_i = 0;
    for (int i = 0; i < rows_; i++) {
        if (i != row) {
            int new_j = 0;
            for (int j = 0; j < cols_; j++) {
                if (j != col) {
                    result.matrix_[new_i][new_j] = matrix_[i][j];
                    new_j++;
                }
            }
            new_i++;
        }
    }
    return result;
}

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& rhs) {
    S21Matrix result = lhs;
    result += rhs;
    return result;
}

S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& rhs) {
    S21Matrix result = lhs;
    result -= rhs;
    return result;
}

S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& rhs) {
    S21Matrix result = lhs;
    result *= rhs;
    return result;
}

S21Matrix operator*(const S21Matrix& lhs, const double& rhs) {
    S21Matrix result = lhs;
    result *= rhs;
    return result;
}

S21Matrix operator* (const double& lhs, const S21Matrix& rhs) {
    S21Matrix result = rhs;
    result *= lhs;
    return result;
}

bool operator==(const S21Matrix& lhs, const S21Matrix& rhs) {
    return lhs.EqMatrix(rhs);
}

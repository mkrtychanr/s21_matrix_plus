#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

class S21Matrix {
    private:
        int rows_ = 0;
        int cols_ = 0;
        double **matrix_ = nullptr;
        bool isValidMatrix() const;
        void new_pointer(double **a, double *b) const;
        double det(double **a, int n) const;
        S21Matrix getMatrixForMinor(int row, int col) const;
        void fillMatrixWithMinors(const S21Matrix& rhs) const;
    public:
        S21Matrix();
        S21Matrix(const int rows, const int cols);
        S21Matrix(const S21Matrix& rhs);
        S21Matrix(S21Matrix&& rhs);
        ~S21Matrix();

        S21Matrix& operator=(const S21Matrix& rhs);
        S21Matrix& operator+=(const S21Matrix& rhs);
        S21Matrix& operator-=(const S21Matrix& rhs);
        S21Matrix& operator*=(const double& rhs);
        S21Matrix& operator*=(const S21Matrix& rhs);

        double& operator()(int i, int j);

        bool EqMatrix(const S21Matrix& rhs) const;
        void SumMatrix(const S21Matrix& rhs);
        void SubMatrix(const S21Matrix& rhs);
        void MulNumber(const double& rhs);
        void MulMatrix(const S21Matrix& rhs);
        S21Matrix Transpose() const;
        S21Matrix CalcComplements() const;
        double Determinant() const;
        S21Matrix InverseMatrix() const;

        int GetRows() const;
        int GetCols() const;
        void SetRows(const int rows);
        void SetCols(const int cols);

};

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator*(const S21Matrix& lhs, const double& rhs);
S21Matrix operator*(const double& lhs, const S21Matrix& rhs);
bool operator==(const S21Matrix& lhs, const S21Matrix& rhs);

#endif  // SRC_S21_MATRIX_OOP_H_
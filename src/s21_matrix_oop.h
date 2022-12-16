#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

class S21Matrix {
    private:
        int rows_ = 0;
        int cols_ = 0;
        double **matrix_ = nullptr;

    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& rhs);
        S21Matrix(S21Matrix&& other)
        ~S21Matrix();

        S21Matrix& operator=(const S21Matrix& rhs);
        S21Matrix& operator+=(const S21Matrix& rhs);
        S21Matrix& operator-=(const S21Matrix& rhs);
        S21Matrix& operator*=(const S21Matrix& rhs);

        double& operator()(int i, int j) const;

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
        void SetRows();
        void SetCols();

};

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator==(const S21Matrix& lhs, const S21Matrix& rhs);

#endif  // SRC_S21_MATRIX_OOP_H_
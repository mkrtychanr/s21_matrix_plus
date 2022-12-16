#include "s21_matrix.h"
#include "s21_tools.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return sum_and_sub(A, B, result, '+');
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return sum_and_sub(A, B, result, '-');
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int return_code = 0;
    if (is_valid_matrix(A) == SUCCESS && is_valid_pointer(result) == SUCCESS) {
        s21_create_matrix(A -> rows, A -> columns, result);
        for (int i = 0; i < A -> rows; i++) {
            for (int j = 0; j < A -> columns; j++) {
                result -> matrix[i][j] = A -> matrix[i][j] * number;
            }
        }
    } else {
        return_code = 1;
    }
    return return_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int return_code = 0;
    if (is_valid_matrix(A) == SUCCESS && is_valid_matrix(B) == SUCCESS &&
                                    is_valid_pointer(result) == SUCCESS) {
        if (A -> columns == B -> rows) {
            s21_create_matrix(A -> rows, B -> columns, result);
            for (int i = 0; i < A -> rows && return_code == 0; i++) {
                for (int j = 0; j < B -> columns; j++) {
                    for (int k = 0; k < A -> columns; k++) {
                        result -> matrix[i][j] += A -> matrix[i][k] * B -> matrix[k][j];
                    }
                }
            }
        } else {
            return_code = 2;
        }
    } else {
        return_code = 1;
    }
    return return_code;
}

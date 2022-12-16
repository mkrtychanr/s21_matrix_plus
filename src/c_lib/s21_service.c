#include "s21_matrix.h"
#include "s21_tools.h"
#include <stdlib.h>
#include <math.h>

int s21_create_matrix(int rows, int columns, matrix_t* result) {
    int return_code = 0;
    if (rows > 0 && columns > 0 && is_valid_pointer(result) == SUCCESS) {
        result -> rows = rows;
        result -> columns = columns;
        result -> matrix = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < rows; i++) {
            result -> matrix[i] = (double*)malloc(columns * sizeof(double));
        }
        for (int i = 0; i < rows && return_code == 0; i++) {
            for (int j = 0; j < columns; j++) {
                result -> matrix[i][j] = 0;
            }
        }
    } else {
        return_code = 1;
    }
    return return_code;
}

void s21_remove_matrix(matrix_t *A) {
    if (is_valid_pointer(A) == SUCCESS) {
        for (int i = 0; i < A -> rows; i++) {
            free(A -> matrix[i]);
        }
        free(A -> matrix);
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int return_code = SUCCESS;
    if (is_valid_matrix(A) == SUCCESS && is_valid_matrix(B) == SUCCESS) {
        for (int i = 0; i < A -> rows && return_code == SUCCESS; i++) {
            for (int j = 0; j < A -> columns && return_code == SUCCESS; j++) {
                if (fabs(A -> matrix[i][j] - B -> matrix[i][j]) > 1E-6) {
                    return_code = FAILURE;
                }
            }
        }
    } else {
        return_code = FAILURE;
    }
    return return_code;
}

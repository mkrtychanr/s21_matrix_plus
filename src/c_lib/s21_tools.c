#include "s21_tools.h"
#include <stdlib.h>
#include <math.h>

int is_valid_pointer(void *a) {
    return (a != NULL) ? SUCCESS : FAILURE;
}

int is_valid_size(matrix_t *a) {
    return (a -> rows > 0 && a -> columns > 0) ? SUCCESS : FAILURE;
}

int is_valid_matrix(matrix_t *a) {
    return (is_valid_pointer(a) == SUCCESS && is_valid_size(a) == SUCCESS) ? SUCCESS : FAILURE;
}

int sum_and_sub(matrix_t *A, matrix_t *B, matrix_t *result, char operation) {
    int return_code = 0;
    if (is_valid_matrix(A) == SUCCESS && is_valid_matrix(B) == SUCCESS &&
                                    is_valid_pointer(result) == SUCCESS) {
        if (A -> rows == B -> rows && A -> columns == B -> columns) {
            s21_create_matrix(A -> rows, A -> columns, result);
            for (int i = 0; i < A -> rows; i++) {
                for (int j = 0; j < A -> columns; j++) {
                    double temp = 0;
                    switch (operation) {
                    case '+':
                        temp = A -> matrix[i][j] + B -> matrix[i][j];
                        break;
                    case '-':
                        temp = A -> matrix[i][j] - B -> matrix[i][j];
                    default:
                        break;
                    }
                    result -> matrix[i][j] = temp;
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

void new_pointer(double **a, double *b) {
    *a = b;
}

double det(double **a, int n) {
    if (n == 1) {
        return a[0][0];
    }
    if (n == 2) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    int number = 0;
    double sum = 0;
    double **temp = malloc((n-1) * sizeof(double*));
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

void create_matrix_for_minor(matrix_t *A, int row, int column, matrix_t *result) {
    s21_create_matrix(A -> rows - 1, A -> columns - 1, result);
    int new_matrix_i = 0;
    int new_matrix_j = 0;
    for (int i = 0; i < A -> rows; i++) {
        if (i != row) {
            new_matrix_j = 0;
            for (int j = 0; j < A -> columns; j++) {
                if (j != column) {
                    result -> matrix[new_matrix_i][new_matrix_j] = A -> matrix[i][j];
                    new_matrix_j++;
                }
            }
            new_matrix_i++;
        }
    }
}

void fill_matrix_with_minors(matrix_t *A, matrix_t *result) {
    if (A -> rows == 1) {
        s21_determinant(A, &result -> matrix[0][0]);
    } else {
        for (int i = 0; i < A -> rows; i++) {
            for (int j = 0; j < A -> columns; j++) {
                matrix_t temp_matrix_for_minor;
                create_matrix_for_minor(A, i, j, &temp_matrix_for_minor);
                s21_determinant(&temp_matrix_for_minor, &result -> matrix[i][j]);
                result -> matrix[i][j] *= pow(-1, i * A -> rows + j);
                s21_remove_matrix(&temp_matrix_for_minor);
            }
        }
    }
}

#ifndef SRC_S21_TOOLS_H_
#define SRC_S21_TOOLS_H_

#include "s21_matrix.h"

int is_valid_pointer(void *a);

int is_valid_size(matrix_t *a);

int is_valid_matrix(matrix_t *a);

int sum_and_sub(matrix_t *A, matrix_t *B, matrix_t *result, char operation);

void new_pointer(double **a, double *b);

double det(double **a, int n);

void create_matrix_for_minor(matrix_t *A, int row, int column, matrix_t *result);

void fill_matrix_with_minors(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_TOOLS_H_

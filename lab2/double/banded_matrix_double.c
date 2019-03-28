//
// Created by pawel on 21.03.19.
//

#include "banded_matrix_double.h"
#include <stdlib.h>
#include <stdio.h>

BandedMatrix *allocate_banded_matrix(int size) {
    double *diagonal = malloc(size * sizeof(double));
    double *upper_diagonal = malloc((size - 1) * sizeof(double));
    double *lower_diagonal = malloc((size - 1) * sizeof(double));
    double *right_column = malloc(size * sizeof(double));
    BandedMatrix *m = malloc(sizeof(BandedMatrix));
    m->size = size;
    m->upper_diagonal = upper_diagonal;
    m->diagonal = diagonal;
    m->lower_diagonal = lower_diagonal;
    m->right_column = right_column;
    return m;
}
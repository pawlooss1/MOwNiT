//
// Created by pawel on 21.03.19.
//

#include "banded_matrix_float.h"
#include <stdlib.h>
#include <stdio.h>

BandedMatrix_f *allocate_banded_matrix_f(int size) {
    float *diagonal = malloc(size * sizeof(float));
    float *upper_diagonal = malloc((size - 1) * sizeof(float));
    float *lower_diagonal = malloc((size - 1) * sizeof(float));
    float *right_column = malloc(size * sizeof(float));
    BandedMatrix_f *m = malloc(sizeof(BandedMatrix_f));
    m->size = size;
    m->upper_diagonal = upper_diagonal;
    m->diagonal = diagonal;
    m->lower_diagonal = lower_diagonal;
    m->right_column = right_column;
    return m;
}
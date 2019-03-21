//
// Created by pawel on 21.03.19.
//

#include "banded_matrix_double.h"
#include <stdlib.h>
#include <stdio.h>

BandedMatrix allocate_banded_matrix(int size) {
    double *diagonal = malloc(size * sizeof(double));
    double *upper_diagonal = malloc(size * sizeof(double));
    double *lower_diagonal = malloc(size * sizeof(double));
    double *right_column = malloc(size * sizeof(double));
    lower_diagonal[0] = 0.0;
    upper_diagonal[size-1] = 0.0;
    BandedMatrix m = {size, diagonal, upper_diagonal, lower_diagonal, right_column};
    return m;
}
//
// Created by pawel on 21.03.19.
//

#include "banded_matrix_double.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

BandedMatrix allocate_banded_matrix(int size) {
    double *diagonal = malloc(size * sizeof(double));
    double *upper_diagonal = malloc((size - 1) * sizeof(double));
    double *lower_diagonal = malloc((size - 1) * sizeof(double));
    double *right_column = malloc(size * sizeof(double));
    BandedMatrix m = {size, diagonal, upper_diagonal, lower_diagonal, right_column};
    return m;
}
//
// Created by pawel on 21.03.19.
//

#ifndef LAB2_BANDED_MATRIX_DOUBLE_H
#define LAB2_BANDED_MATRIX_DOUBLE_H

typedef struct BandedMatrix {
    int size;
    double *diagonal;
    double *upper_diagonal;
    double *lower_diagonal;
    double *right_column;
} BandedMatrix;

BandedMatrix allocate_banded_matrix(int size);

#endif //LAB2_BANDED_MATRIX_DOUBLE_H

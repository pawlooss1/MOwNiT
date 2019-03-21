//
// Created by pawel on 21.03.19.
//

#ifndef LAB2_BANDED_MATRIX_FLOAT_H
#define LAB2_BANDED_MATRIX_FLOAT_H

typedef struct BandedMatrix_f {
    int size;
    float *diagonal;
    float *upper_diagonal;
    float *lower_diagonal;
    float *right_column;
} BandedMatrix_f;

BandedMatrix_f allocate_banded_matrix_f(int size);

#endif //LAB2_BANDED_MATRIX_FLOAT_H

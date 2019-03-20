//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_VECTOR_DOUBLE_H
#define LAB2_VECTOR_DOUBLE_H

typedef struct Vector {
    int length;
    double *vector;
} Vector;

Vector allocate_vector(int length);
void print_vector(Vector v);
double euclid_norm(Vector x, Vector x_calc);
double max_norm(Vector x, Vector x_calc);

#endif //LAB2_VECTOR_DOUBLE_H

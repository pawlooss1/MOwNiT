//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_VECTOR_FLOAT_H
#define LAB2_VECTOR_FLOAT_H

typedef struct Vector_f {
    int length;
    float *vector;
} Vector_f;

Vector_f *allocate_vector_f(int length);

void free_vector_f(Vector_f *v);

Vector_f *copy_vector_f(Vector_f *v);

void print_vector_f(Vector_f *v);

float euclid_norm_f(Vector_f *x, Vector_f *x_calc);

float max_norm_f(Vector_f *x, Vector_f *x_calc);

#endif //LAB2_VECTOR_FLOAT_H

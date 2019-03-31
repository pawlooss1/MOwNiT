//
// Created by pawel on 20.03.19.
//

#ifndef LAB2_VECTOR_DOUBLE_H
#define LAB2_VECTOR_DOUBLE_H

typedef struct Vector {
    int length;
    double *vector;
} Vector;

Vector *allocate_vector(int length);

void free_vector(Vector *v);

Vector *generate_random_vector(int length);

Vector *copy_vector(Vector *v);

void copy_vector_values(Vector *v_source, Vector *v_dest);

void multiply_vector_by_const(Vector *v, double c);

double dot_product(Vector *v1, Vector *v2);

void print_vector(Vector *v);

double norm(Vector *v);

double euclid_norm(Vector *x, Vector *x_calc);

double max_norm(Vector *x, Vector *x_calc);

#endif //LAB2_VECTOR_DOUBLE_H

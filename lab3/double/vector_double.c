//
// Created by pawel on 20.03.19.
//

#include "vector_double.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Vector *allocate_vector(int length) {
    double *vec = (double *) malloc(length * sizeof(double));
    Vector *v = malloc(sizeof(Vector));
    v->vector = vec;
    v->length = length;
    return v;
}

void free_vector(Vector *v) {
    free(v->vector);
    free(v);
}

Vector *generate_random_vector(int length) {
    Vector *result = allocate_vector(length);
    for (int i = 0; i < result->length; i++)
        result->vector[i] = (double) rand() / ((double) RAND_MAX);
    return result;
}

Vector *copy_vector(Vector *v) {
    Vector *result = allocate_vector(v->length);
    for (int i = 0; i < v->length; i++)
        result->vector[i] = v->vector[i];
    return result;
}

void copy_vector_values(Vector *v_source, Vector *v_dest) {
    if (v_source->length != v_dest->length)
        return;
    for (int i = 0; i < v_source->length; i++)
        v_dest->vector[i] = v_source->vector[i];
}

void multiply_vector_by_const(Vector *v, double c) {
    for (int i = 0; i < v->length; i++)
        v->vector[i] *= c;
}

double dot_product(Vector *v1, Vector *v2) {
    double result = 0;
    for (int i = 0; i < v1->length; i++)
        result += v1->vector[i] * v2->vector[i];
    return result;
}

void print_vector(Vector *v) {
    int length = v->length;
    double *vector = v->vector;
    for (int i = 0; i < length; i++) {
        printf("| %f |\n", vector[i]);
    }
    printf("\n");
}

double norm(Vector *v) {
    double sum = 0;
    for (int i = 0; i < v->length; i++)
        sum += v->vector[i] * v->vector[i];
    return sqrt(sum);
}

double euclid_norm(Vector *x, Vector *x_calc) {
    double sum = 0;
    Vector *v = allocate_vector(x->length);
    for (int i = 0; i < x->length; i++) {
        v->vector[i] = x->vector[i] - x_calc->vector[i];
    }
    for (int i = 0; i < v->length; i++) {
        sum += v->vector[i] * v->vector[i];
    }
    free_vector(v);
    return sqrt(sum);
}

double max_norm(Vector *x, Vector *x_calc) {
    Vector *v = allocate_vector(x->length);
    for (int i = 0; i < x->length; i++) {
        v->vector[i] = (double) (x->vector[i] - x_calc->vector[i]);
    }
    double max = fabs(v->vector[0]);
    for (int i = 1; i < v->length; i++) {
        if (fabs(v->vector[i]) > max)
            max = fabs(v->vector[i]);
    }
    free_vector(v);
    return max;
}
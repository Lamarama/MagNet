/*
 * dmat.h
 *
 */

#ifndef DMAT_H_
#define DMAT_H_

#define MATRIX_MAX_SIZE 16

typedef struct {
    unsigned int rows;
    unsigned int columns;
    double data[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE];
} dmat;

int dmat_add(dmat *dest, dmat *a, dmat *b);

double dmat_dot(const double *a, int a_stride,
                 const double *b, int b_stride,
                 int n);

int dmat_mul(dmat *dest, const dmat *a, const dmat *b);

void dmat_mul_s(dmat *dest, const dmat *a, const double scalar);

#endif /* DMAT_H_ */

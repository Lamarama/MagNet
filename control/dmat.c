/*
 * dmat.c
 *
 *  Created on: Jan 7, 2017
 *      Author: nathaniel
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dmat.h"

int dmat_add(dmat *dest, dmat *a, dmat *b) {
    int invalidDims = 0;

    if(a->rows == b->rows && a->columns == b->columns) {
        dest->rows = a->rows;
        dest->columns = a->columns;

        int i;
        int j;
        for (i = 0; i < a->rows; i++) {
            for (j = 0; j < a->columns; j++) {
                (dest->data)[i][j] = (a->data)[i][j] + (b->data)[i][j];
            }
        }
    } else {
        invalidDims = 1;
    }
    return invalidDims;
}

double dmat_dot(const double *a, int a_stride,
                 const double *b, int b_stride,
                 int n) {
    double sum = 0;

    while (n--) {
        // Compute dest
        if (*a != 0 && *b != 0) {
            double product = (*a) * (*b);
            sum += product;
        }

        // Go to next item
        a += a_stride;
        b += b_stride;
    }

    return sum;
}

int dmat_mul(dmat *dest, const dmat *a, const dmat *b) {
    int invalidDims = 0;
    int row, column;

    if (a->columns == b->rows) {
        dest->rows = a->rows;
        dest->columns = b->columns;

        for (row = 0; row < dest->rows; row++) {
            for (column = 0; column < dest->columns; column++) {
                dest->data[row][column] = dmat_dot(
                    &a->data[row][0], 1,
                    &b->data[0][column], MATRIX_MAX_SIZE,
                    a->columns);
            }
        }
    } else {
        invalidDims = 1;
    }

    return invalidDims;
}

void dmat_mul_s(dmat *dest, const dmat *a, const double scalar) {
    dest->rows = a->rows;
    dest->columns = a->columns;

    int i;
    int j;
    for (i = 0; i < a->rows; i++) {
        for (j = 0; j < a->columns; j++) {
            (dest->data)[i][j] = (a->data)[i][j] * scalar;
        }
    }
}



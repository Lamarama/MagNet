/*
 * control.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "control.h"
#include "dmat.h"

double findPos(double i, double u, double c, double c2) {
    double Bpuck[] = {-0.0977, 0.1215, -0.0011};
    double Bhall = i*c;
    double Bs = u*c2;
    double firstRoot;
    double secondRoot;
    double y = 0;

    int hasImagRoots = solve_quadratic(Bpuck[0], Bpuck[1], Bpuck[2] - Bhall - Bs, &firstRoot, &secondRoot);

    if(!hasImagRoots) {
        if (firstRoot < secondRoot) {
            y = firstRoot;
        } else {
            y = secondRoot;
        }
    }

    return y;
}

double control(double yd, double y, dmat *x, dmat *A, dmat *B, dmat *C, double D, unsigned int size) {
    double e = yd - y;

    dmat cx_prod_matrix;
    dmat ax_prod_matrix;
    dmat be_prod_matrix;

    dmat result_matrix;

    int i;

    dmat_mul(&cx_prod_matrix, C, x);
    double cx_prod_num = cx_prod_matrix.data[0][0];

    dmat_mul(&ax_prod_matrix, A, x);

    dmat_mul_s(&be_prod_matrix, B, e);

    dmat_add(&result_matrix, &be_prod_matrix, &ax_prod_matrix);

    for (i = 0; i < size; i++) {
        (x -> data)[i][0] = result_matrix.data[i][0];
    }

    return cx_prod_num + (D*e);
}

int solve_quadratic(double a, double b, double c, double *firstRoot, double *secondRoot) {
    int hasImagRoots = 0;

    double discrim = (b*b) - (4*a*c);
    if (discrim >= 0) {
        *firstRoot = ((-1 * b) + sqrt(discrim)) / (2*a);
        *secondRoot = ((-1 * b) - sqrt(discrim)) / (2*a);
    } else {
        hasImagRoots = 1;
    }

    return hasImagRoots;
}




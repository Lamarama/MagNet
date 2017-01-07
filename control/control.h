/*
 * control.h
 */

#ifndef CONTROL_H_
#define CONTROL_H_
#include "dmat.h"

int solve_quadratic(double a, double b, double c, double *firstRoot, double *secondRoot);

double findPos(double i, double u, double c, double c2);

double control(double yd, double y, dmat *x, dmat *A, dmat *B, dmat *C, double D, unsigned int size);

#endif /* CONTROL_H_ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
int solve_quadratic(double a, double b, double c, double *firstRoot, double *secondRoot);
double findPos(double i, double u, double c, double c2);
double control(double yd, double y, dmat *x, dmat *A, dmat *B, dmat *C, double D, unsigned int size);

int main(void) {
	double y = findPos(0, -2.7893, 0, 1);

	dmat a = {2, 2,
	    {{0.987716133888642, 0.00348189369389567}, // First row
	     {0.0, 1.0}} // Second row
	};

	dmat b = {2, 1,
		{{0.792563912906443},
		{0.281164954372112}}
	};

	dmat c = {1, 2,
		{{-0.765829954212773,0.271680984494242}}
	};

	double d = 61.841217183204210;

	dmat x = {2, 1,
		{{0.0},
		{0.0}}
	};

	int i;
	int j;
	double u;
	for(i=0; i<5; i++) {
		printf("Iteration %d\n", i+1);
		u = control(-5.0, y, &x, &a, &b, &c, d, 4);
		printf("u = %f\n", u);
		for(j=0; j<3; j++) {
			printf("x%d = %f\n", j+1, x.data[j][0]);
		}
		printf("\n");
	}

	return 0;
}

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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dmat.h"
#include "control.h"

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
        for(j=0; j<2; j++) {
            printf("x%d = %f\n", j+1, x.data[j][0]);
        }
        printf("\n");
    }

    return 0;
}

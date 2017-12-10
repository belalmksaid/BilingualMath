#pragma once

#include <stdlib.h>
#include <time.h>
#include <cblas.h>
#include <lapacke.h>


#ifdef DOUBLE_PREC
#define prec double
#else
#define prec float
#endif

namespace math
{
extern "C" {
    void bl_dcross_(double *A, double *B, double *C);
    void bl_dtranspose_(prec *A, int *M, int *N);
    void bl_scross_(float *A, float *B, float *C);
    void bl_stranspose_(float *A, int *M, int *N);
}
void init()
{
    srand(time(NULL));
}
prec random()
{
    return rand() / ((prec)RAND_MAX);
}
}
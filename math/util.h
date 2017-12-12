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
void bl_init_();
void bl_dcross_(double *A, double *B, double *C);
void bl_scross_(float *A, float *B, float *C);
void bl_dtranspose_(double *A, int *M, int *N, double* B);
void bl_stranspose_(float *A, int *M, int *N, float* B);
void bl_drandom_(double *A, int *M, int *N);
void bl_srandom_(double *A, int *M, int *N);
}
void init()
{
    srand(time(NULL));
    bl_init_();
}
prec random()
{
    return rand() / ((prec)RAND_MAX);
}
}
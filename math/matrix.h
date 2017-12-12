#pragma once

#include "util.h"
#include <iostream>
#include <string.h>
#include <assert.h>

#define tmin(X, Y) (X > Y ? Y : X)

namespace math
{

template <int T, int U>
struct matrix
{
  public:
    int tot = T * U, m = T, n = U;
    prec data[T][U];

    prec &operator()(int i, int j)
    {
        return data[i][j];
    }

    matrix<T, U> &operator=(const matrix<T, U> &);

    matrix<T, U> &operator+=(const matrix<T, U> &M)
    {
        return *this = *this + M;
    }

    matrix<T, U> &operator*=(const matrix<U, T> &M)
    {
        return *this = *this * M;
    }
    matrix<T, U> &operator*=(prec m)
    {
        return *this = *this * m;
    }

    matrix<U, T> &transpose()
    {
        assert(U == T);
        int m = T;
        int n = U;
#ifdef DOUBLE_PREC
        math::bl_dtranspose_(*data, &m, &n, *data);
#else
        math::bl_stranspose_(*data, &m, &n, *data);
#endif
        return (*this);
    }

    matrix<T, U> &inverse()
    {
        if (T != U)
            return *this;
        lapack_int n = T;
        lapack_int ipiv[T];
        lapack_int info = 0;
        prec work[T * T];
        lapack_int wc = T * T;
#ifdef DOUBLE_PREC
        LAPACK_dgetrf(&n, &n, *data, &n, ipiv, &info);
        LAPACK_dgetri(&n, *data, &n, ipiv, work, &wc, &info);
#else
        LAPACK_sgetrf(&n, &n, *data, &n, ipiv, &info);
        LAPACK_sgetri(&n, *data, &n, ipiv, work, &wc, &info);
#endif
        return *this;
    }

    void print()
    {
        for (int i = 0; i < T; i++)
        {
            for (int j = 0; j < U; j++)
            {
                std::cout << data[i][j] << "\t";
            }
            std::cout << "\n"
                      << std::endl;
        }
    }

    static matrix<T, U> random();
    static matrix<T, U> identity();
    static matrix<T, U> zero();
    static matrix<U, T> transpose(matrix<T, U> m);
    static matrix<T, U> inverse(matrix<T, U> m);
};

template <int T, int U>
matrix<T, U> &matrix<T, U>::operator=(const matrix<T, U> &cp)
{
    //cblas_dcopy(cp.tot, *(cp.data), 1, *data, 1);
    memcpy(&data, &(cp.data), cp.tot * sizeof(prec));
    // for(int i = 0; i < cp.tot; i++) {
    //    *(*(data) + i) = *(*(cp.data) + i);
    // }
    return *this;
}

template <int T, int U>
matrix<T, U> operator+(const matrix<T, U> &a, const matrix<T, U> &b)
{
    matrix<T, U> temp;
    for (int i = 0; i < a.tot; i++)
    {
        *(*(temp.data) + i) = *(*(a.data) + i) + *(*(b.data) + i);
    }
    return temp;
}

template <int T, int U, int X>
matrix<T, X> operator*(const matrix<T, U> &a, const matrix<U, X> &m)
{
    matrix<T, X> temp;
#ifdef DOUBLE_PREC
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, T, X, U, 1.0, *(a.data), U, *(m.data), X, 0.0, *(temp.data), X);
#else
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, T, X, U, 1.0, *(a.data), U, *(m.data), X, 0.0, *(temp.data), X);
#endif

    return temp;
}

template <int T, int U>
matrix<T, U> operator*(const matrix<T, U> &a, prec m)
{
    matrix<T, U> temp = a;
#ifdef DOUBLE_PREC
    cblas_dscal(temp.tot, m, *(temp.data), 1);
#else
    cblas_sscal(temp.tot, m, *(temp.data), 1);
#endif
    // matrix<T, U> temp;
    // for(int i = 0; i < a.tot; i++) {
    //    *(*(temp.data) + i) = m * (*(*(a.data) + i));
    // }
    return temp;
}

template <int T, int U>
matrix<T, U> operator*(prec m, const matrix<T, U> &a)
{
    return a * m;
}

template <int T, int U>
matrix<T, U> matrix<T, U>::random()
{
    matrix<T, U> temp;
#ifdef DOUBLE_PREC
    bl_drandom_((*temp.data), &(temp.m), &(temp.n));
#else
    bl_srandom_((*temp.data), &m, &n);
#endif
    // for (int i = 0; i < temp.tot; i++)
    // {
    //     *(*(temp.data) + i) = math::random();
    // }
    return temp;
}

template <int T, int U>
matrix<T, U> matrix<T, U>::identity()
{
    matrix<T, U> temp;
    memset(&(temp.data), 0, sizeof(temp.data));
    int diag = tmin(T, U);
    for (int i = 0; i < diag; i++)
    {
        temp.data[i][i] = 1.0;
    }
    return temp;
}

template <int T, int U>
matrix<T, U> matrix<T, U>::zero()
{
    matrix<T, U> temp;
    memset(&(temp.data), 0, sizeof(temp.data));
    // for (int i = 0; i < temp.tot; i++)
    // {
    //     *(*(temp.data) + i) = 0.0;
    // }
    return temp;
}

template <int T, int U>
matrix<U, T> matrix<T, U>::transpose(matrix<T, U> tr)
{
    if (U == T)
    {
        matrix<U, T> temp = tr;
        return temp.transpose();
    }
    else
    {
        matrix<U, T> temp;
        int m = T;
        int n = U;
#ifdef DOUBLE_PREC
        math::bl_dtranspose_(*(tr.data), &m, &n, *(temp.data));
#else
        math::bl_stranspose_(*(tr.data), &m, &n, *(temp.data));
#endif
        return temp;
    }
}
};
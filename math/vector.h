#pragma once

#include "util.h"
#include <iostream>
#include <string.h>
#include <lapacke.h>
#include "matrix.h"
#include <assert.h>

namespace math
{

template <int T>
struct vector
{
  public:
    prec data[T];
    prec normSt = -1;

    prec &operator()(int i)
    {
        return data[i];
    }

    prec norm() {
        // normSqSt = cblas_ddot(T, data, 1, data, 1);
        // // for(int i = 0; i < T; i++) {
        // //     normSqSt += data[i] * data[i];
        // // }
#ifdef DOUBLE_PREC
        return (normSt = cblas_dnrm2(T, data, 1));
#else
        return (normSt = cblas_snrm2(T, data, 1));
#endif
        
    }

    void print()
    {
        for (int i = 0; i < T; i++)
        {
            std::cout << data[i] << "\t";
        }
        std::cout << "\n" << std::endl;
    }

    vector<T> &operator=(const vector<T> &v);

    static vector<T> random();
    static vector<T> zero();
    static vector<T> cross(vector<T> &a, vector<T> &b);
    static vector<T> cross2(vector<T> &a, vector<T> &b);
};

template <int T>
vector<T> &vector<T>::operator=(const vector<T> &cp)
{
    memcpy(&data, &(cp.data), T * sizeof(prec));
    return *this;
}

template <int T>
vector<T> operator*(const vector<T> &a, prec m)
{
    vector<T> temp = a;
    cblas_dscal(T, m, *(temp.data), 1);
    return temp;
}

template <int T, int X>
vector<X> operator*(const matrix<X, T> &a, const vector<T> &b)
{
    vector<T> temp;
#ifdef DOUBLE_PREC
        cblas_dgemv(CblasColMajor, CblasNoTrans, X, T, 1.0, *(a.data), X, b.data, 1, 0.0, temp.data, 1);
#else
        cblas_sgemv(CblasColMajor, CblasNoTrans, X, T, 1.0, *(a.data), X, b.data, 1, 0.0, temp.data, 1);
#endif
    
    return temp;
}

template <int T>
prec operator*(const vector<T> &a, const vector<T> &b)
{
#ifdef DOUBLE_PREC
        return cblas_ddot(T, a.data, 1, b.data, 1);
#else
        return cblas_sdot(T, a.data, 1, b.data, 1);
#endif
}

template <int T>
vector<T> vector<T>::random()
{
    vector<T> temp;
    for (int i = 0; i < T; i++)
    {
        temp.data[i] = math::random();
    }
    return temp;
}

template <int T>
vector<T> vector<T>::zero()
{
    vector<T> temp;
    memset(&(temp.data), 0, sizeof(temp.data));
    return temp;
}


template <int T>
vector<T> vector<T>::cross(vector<T> &a, vector<T> &b)
{
    assert(T == 3);
    vector<T> axb;
    axb.data[0] = a.data[1]*b.data[2] - a.data[2]*b.data[1];
    axb.data[1] = a.data[2]*b.data[0] - a.data[0]*b.data[2];
    axb.data[2] = a.data[0]*b.data[1] - a.data[1]*b.data[0];
    return axb;
}

template <int T>
vector<T> vector<T>::cross2(vector<T> &a, vector<T> &b)
{
    vector<T> axb;
#ifdef DOUBLE_PREC
        math::bl_dcross_(a.data, b.data, axb.data);
#else
        math::bl_scross_(a.data, b.data, axb.data);
#endif
    return axb;
}

template <int T>
matrix<T, T> scale(vector<T - 1> th) {
    matrix<T, T> temp;
    memset(&(temp.data), 0, sizeof(temp.data));
    for (int i = 0; i < T - 1; i++)
    {
        temp.data[i][i] = th.data[i];
    }
    temp.data[T - 1][T - 1] = 1.0;
    return temp;
}

template <int T>
matrix<T, T> translate(vector<T - 1> th) {
    matrix<T, T> r = math::matrix<T, T>::identity();
    for(int i = 0; i < T - 1; i++) {
        r.data[i][T - 1] = th.data[i];
    }
    return r;
}

};
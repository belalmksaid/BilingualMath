#define DOUBLE_PREC

#include <iostream>
#include <chrono>
#include "math/util.h"
#include "math/math.h"
#include "brt/core/ray.h"

#define K 4
#define S 3

using namespace std;
using namespace math;

int main()
{
    math::init();
    vector<S> v;
    v(0) = 3;
    v(1) = 4;
    v(2) = 5;

    matrix<K,K> m = matrix<K, K>::random();
    
    //math::matrix<K> k;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
    {
        m.inverse();        
    }
    auto elapsed = chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << microseconds << endl;
    return 0;
}
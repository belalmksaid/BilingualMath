#define DOUBLE_PREC

#include <iostream>
#include <chrono>
#include "math/util.h"
#include "math/math.h"

#define LOOP 1000000
#define A 3

using namespace std;
using namespace math;

int main()
{
    cout << "Bilingual Math Library" << endl;
    cout << "Initializing..." << endl;
    math::init();
#ifdef DOUBLE_PREC
    cout << "Double mode in use..." << endl;
#else
    cout << "Float mode in use.." << endl;
#endif
    cout << "Number of iterations: \t\t\t" << LOOP << endl;
    {
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Time to run through "  << LOOP << " loop:\t" << microseconds << " us"<< endl;
    }
    {
        auto start = chrono::high_resolution_clock::now();
        prec holder;
        for(int i = 0; i < LOOP; i++) {
            math::random();
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Generate random numbers:\t\t" << microseconds << " us"<< endl;
    }
    {
        matrix<A, A> m;
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            m = m;
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Assign matrices:\t\t\t" << microseconds << " us"<< endl;
    }
    {
        matrix<A, A> m;
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            m = matrix<A, A>::identity();
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Generate identity matrices:\t\t" << microseconds << " us"<< endl;
    }
    {
        matrix<A, A> m;
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            m = matrix<A, A>::random();
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Generate random matrices:\t\t" << microseconds << " us"<< endl;
    }
    {
        matrix<A, A> m = matrix<A, A>::random();
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            m = matrix<A, A>::random();
            m.transpose();
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Transpose matrices:\t\t\t" << microseconds << " us"<< endl;
    }
    {
        matrix<A, A> m = matrix<A, A>::random(), a;
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            a = m;
            a.inverse();
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Inverse matrices:\t\t\t" << microseconds << " us"<< endl;
    }
    {
        matrix<A, A> m = matrix<A, A>::random();
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            m * m;
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Multiply matrices:\t\t\t" << microseconds << " us"<< endl;
    }
    {
        matrix<A, A> m = matrix<A, A>::random();
        vector<A> v = vector<A>::random();
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            m * v;
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Multiply matrix by vector:\t\t" << microseconds << " us"<< endl;
    }
    {
        vector<A> v = vector<A>::random(), v2 = vector<A>::random();
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            v * v2;
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Vector dot product:\t\t\t" << microseconds << " us"<< endl;
    }
    {
        vector<3> v = vector<3>::random(), v2 = vector<3>::random();
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0; i < LOOP; i++) {
            v * v2;
        }
        auto elapsed = chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << "Vector [3x3] cross product:\t\t" << microseconds << " us"<< endl;
    }
    return 0;
}
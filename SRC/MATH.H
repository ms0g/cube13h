#ifndef MATH_H
#define MATH_H

#include <math.h>

inline int absf(int v) {
    return v < 0 ? 0 - v : v;
}

inline int ceilf(float v) {
    return (int)v + 1;
} 

inline int floorf(float v) {
    return (int)v;
}

inline int signbit(float v) {
    return v < 0.0 ? 1 : 0;
}

inline int round(float v) {
    return signbit(v) ? ceilf(v - 0.5) : floorf(v + 0.5);
}

inline int min(int n0, int n1) {
    return (n0 < n1) ? n0 : n1;
}

inline int max(int n0, int n1) {
    return (n0 > n1) ? n0 : n1;
}

double invSqrt(double n);

int determinant(int x0, int y0, int x1, int y1, int x2, int y2);

#endif
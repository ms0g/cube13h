#include "MATH.H"

double invSqrt(double n) {
    long i;
    float x2, y;

    x2 = n * 0.5F;
    y = n;
    i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (x2 * y * y));   // 1st iteration
    y = y * (1.5f - (x2 * y * y));   // 2nd iteration

    return y;
}

int determinant(int x0, int y0, int x1, int y1, int x2, int y2) {
    int v0v1_x = x1 - x0;
    int v0v1_y = y1 - y0;
    int v0v2_x = x2 - x0;
    int v0v2_y = y2 - y0;

    return (v0v1_x * v0v2_y) - (v0v1_y * v0v2_x);
}
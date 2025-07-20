#ifndef MAT_H
#define MAT_H

#include "VEC.H"

typedef struct {
    double m[3][3];
} Mat3;

Mat3 mtxIdentity(void);

Mat3 mtxRotz(double angle);

Mat3 mtxRoty(double angle);

Mat3 mtxRotx(double angle);

Vec3 mtxMulVec3(const Mat3* m, const Vec3* v);

Mat3 mtxMulMat3(const Mat3* m1, const Mat3* m2);

#endif
#include "MAT.H"
#include <math.h>

Mat3 mtxIdentity(void) {
    Mat3 _m;
    
    _m.m[0][0] = 1;
    _m.m[0][1] = 0;
    _m.m[0][2] = 0;
    _m.m[1][0] = 0;
    _m.m[1][1] = 1;
    _m.m[1][2] = 0;
    _m.m[2][0] = 0;
    _m.m[2][1] = 0;
    _m.m[2][2] = 1;
    
    return _m;
}

Mat3 mtxRotz(double angle) {
    // | c -s  0 |
    // | s  c  0 |
    // | 0  0  1 |
    Mat3 _m = mtxIdentity();
    double c = cos(angle);
    double s = sin(angle);

    _m.m[0][0] = c;
    _m.m[0][1] = -s;
    _m.m[1][0] = s;
    _m.m[1][1] = c;

    return _m;
}

Mat3 mtxRoty(double angle) {
    // |  c  0  s |
    // |  0  1  0 |
    // | -s  0  c |
    Mat3 _m = mtxIdentity();
    double c = cos(angle);
    double s = sin(angle);

    _m.m[0][0] = c;
    _m.m[0][2] = s;
    _m.m[2][0] = -s;
    _m.m[2][2] = c;

    return _m;
}

Mat3 mtxRotx(double angle) {
    // | 1  0  0 |
    // | 0  c -s |
    // | 0  s  c |
    Mat3 _m = mtxIdentity();
    double c = cos(angle);
    double s = sin(angle);

    _m.m[1][1] = c;
    _m.m[1][2] = -s;
    _m.m[2][1] = s;
    _m.m[2][2] = c;

    return _m;
}

Vec3 mtxMulVec3(const Mat3* m, const Vec3* v) {
    Vec3 _v;

    _v.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z;
    _v.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z;
    _v.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z;

    return _v;
}

Mat3 mtxMulMat3(const Mat3* m1, const Mat3* m2) {
    int i, j;
    Mat3 _m;
   
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            _m.m[i][j] = m1->m[i][0] * m2->m[0][j] + m1->m[i][1] * m2->m[1][j] + m1->m[i][2] * m2->m[2][j];
        }
    }

    return _m;
}
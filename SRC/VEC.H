#ifndef VEC_H
#define VEC_H
 
typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

void vecNormalize(Vec3* v);

double vecInvLen(const Vec3* v);

void vecSAdd(Vec3* v, const double scalar);

Vec2 vecProject(const Vec3* v, const int fov);

Vec3 vecRotx(const Vec3* v, const double angle);

Vec3 vecRoty(const Vec3* v, const double angle);

Vec3 vecRotz(const Vec3* v, const double angle);

Vec3 vecAdd(const Vec3* v0, const Vec3* v1);

Vec3 vecSub(const Vec3* v0, const Vec3* v1);

double vecDot(const Vec3* v0, const Vec3* v1);

Vec3 vecCross(const Vec3* v0, const Vec3* v1);

#endif
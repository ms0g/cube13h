#include "VEC.H"
#include "MATH.H"

void vecNormalize(Vec3* v) {
    double length = vecInvLen(v);
    
    v->x *= length;
    v->y *= length;
    v->z *= length;
}

double vecInvLen(const Vec3* v) {
    return invSqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void vecSAdd(Vec3* v, const double scalar) {
    v->x += scalar;
    v->y += scalar;
    v->z += scalar;
}

Vec2 vecProject(const Vec3* v, const int fov) {
    Vec2 result = {0, 0};
    result.x = (fov * v->x) / v->z;
    result.y = (fov * v->y) / v->z;
    
    return result;
}

Vec3 vecRotx(const Vec3* v, const double angle) {
    double cosA = cos(angle);
    double sinA = sin(angle);
    Vec3 result = {0, 0, 0};

    result.x = v->x;
    result.y = v->y * cosA - v->z * sinA;
    result.z = v->y * sinA + v->z * cosA;
   
    return result;
}

Vec3 vecRoty(const Vec3* v, const double angle) {
    double cosA = cos(angle);
    double sinA = sin(angle);
    Vec3 result = {0, 0, 0};

    result.x = v->x * cosA - v->z * sinA;
    result.y = v->y;
    result.z = v->x * sinA + v->z * cosA;
   
    return result;
}

Vec3 vecRotz(const Vec3* v, const double angle) {
    double cosA = cos(angle);
    double sinA = sin(angle);
    Vec3 result = {0, 0, 0};

    result.x = v->x * cosA - v->y * sinA;
    result.y = v->x * sinA + v->y * cosA;
    result.z = v->z;
   
    return result;
}

Vec3 vecAdd(const Vec3* v0, const Vec3* v1) {
    Vec3 result = {0, 0, 0};

    result.x = v0->x + v1->x;
    result.y = v0->y + v1->y;
    result.z = v0->z + v1->z;

    return result;
}

Vec3 vecSub(const Vec3* v0, const Vec3* v1) {
    Vec3 result = {0, 0, 0};

    result.x = v0->x - v1->x;
    result.y = v0->y - v1->y;
    result.z = v0->z - v1->z;

    return result;
}

double vecDot(const Vec3* v0, const Vec3* v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;

}

Vec3 vecCross(const Vec3* v0, const Vec3* v1) {
    Vec3 result = {0, 0, 0};

    result.x = v0->y * v1->z - v0->z * v1->y;
    result.y = v0->z * v1->x - v0->x * v1->z;
    result.z = v0->x * v1->y - v0->y * v1->x;

    return result;
}
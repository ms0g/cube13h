#include "VEC.H"
#include "MATH.H"

void normalize(vec3& v) {
    double length = invLen(v);
    
    v.x *= length;
    v.y *= length;
    v.z *= length;
}

double invLen(const vec3& v) {
    return invSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void sadd(vec3& v, double scalar) {
    v.x += scalar;
    v.y += scalar;
    v.z += scalar;
}

vec2 project(const vec3& v, int fov) {
    vec2 result = {
        (fov * v.x) / v.z,
        (fov * v.y) / v.z
    };

    return result;
}

vec3 rotx(const vec3& v, double angle) {
    vec3 result;

    result.x = v.x;
    result.y = v.y * cos(angle) - v.z * sin(angle);
    result.z = v.y * sin(angle) + v.z * cos(angle);
   
    return result;
}

vec3 roty(const vec3& v,double angle) {
    vec3 result;

    result.x = v.x * cos(angle) - v.z * sin(angle);
    result.y = v.y;
    result.z = v.x * sin(angle) + v.z * cos(angle);
   
    return result;
}

vec3 rotz(const vec3& v, double angle) {
    vec3 result;

    result.x = v.x * cos(angle) - v.y * sin(angle);
    result.y = v.x * sin(angle) + v.y * cos(angle);
    result.z = v.z;
   
    return result;
}

double dot(const vec3& v0, const vec3& v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;

}

vec3 cross(const vec3& v0, const vec3& v1) {
    vec3 result;

    result.x = v0.y * v1.z - v0.z * v1.y;
    result.y = v0.z * v1.x - v0.x * v1.z;
    result.z = v0.x * v1.y - v0.y * v1.x;

    return result;
}
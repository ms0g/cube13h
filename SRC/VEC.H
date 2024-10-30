#ifndef VEC_H
#define VEC_H
 
struct vec2 {
    double x;
    double y;
};

struct vec3 {
    double x;
    double y;
    double z;
    
    vec3(): x(0.0), y(0.0), z(0.0) {}
    vec3(double x, double y, double z): x(x), y(y), z(z) {}
    vec3(double* v) : x(v[0]), y(v[1]), z(v[2]) {}
    
    vec3 operator+(const vec3 &other) const {
        return vec3(x + other.x,  y + other.y, z + other.z);
    }

    vec3 operator-(const vec3 &other) const {
        return vec3(x - other.x,  y - other.y, z - other.z);
    }
};

void normalize(vec3& v);

double invLen(const vec3& v);

void sadd(vec3& v, double scalar);

vec2 project(const vec3& v, int fov);

vec3 rotx(const vec3& v, double angle);

vec3 roty(const vec3& v, double angle);

vec3 rotz(const vec3& v, double angle);

double dot(const vec3& v0, const vec3& v1);

vec3 cross(const vec3& v0, const vec3& v1);

#endif
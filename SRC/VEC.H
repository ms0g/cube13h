#ifndef VEC_H
#define VEC_H
 
struct vec2 {
    float x;
    float y;
};

struct vec3 {
    float x;
    float y;
    float z;
    
    vec3(): x(0), y(0), z(0) {}
    vec3(float x, float y, float z): x(x), y(y), z(z) {}
    vec3(float* v) : x(v[0]), y(v[1]), z(v[2]) {}
    
    vec3 operator+(const vec3 &other) const {
        return vec3(x + other.x,  y + other.y, z + other.z);
    }

    vec3 operator-(const vec3 &other) const {
        return vec3(x - other.x,  y - other.y, z - other.z);
    }
};

void normalize(vec3& v);

float invLen(const vec3& v);

void sadd(vec3& v, float scalar);

vec2 project(const vec3& v, int fov);

vec3 rotx(const vec3& v, float angle);

vec3 roty(const vec3& v, float angle);

vec3 rotz(const vec3& v, float angle);

float dot(const vec3& v0, const vec3& v1);

vec3 cross(const vec3& v0, const vec3& v1);

#endif
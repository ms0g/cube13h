#ifndef VEC_H
#define VEC_H
 
typedef struct {
    double x;
    double y;
} vec2;

typedef struct {
    double x;
    double y;
    double z;
} vec3;

#ifdef __cplusplus
extern "C" {
#endif

void normalize(vec3* v);

double invLen(const vec3* v);

void sadd(vec3* v, const double scalar);

vec2 project(const vec3* v, const int fov);

vec3 rotx(const vec3* v, const double angle);

vec3 roty(const vec3* v, const double angle);

vec3 rotz(const vec3* v, const double angle);

vec3 add(const vec3* v0, const vec3* v1);

vec3 sub(const vec3* v0, const vec3* v1);

double dot(const vec3* v0, const vec3* v1);

vec3 cross(const vec3* v0, const vec3* v1);

#ifdef __cplusplus
}
#endif

#endif
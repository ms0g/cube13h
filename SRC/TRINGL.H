#ifndef TRINGL_H
#define TRINGL_H

#include "VEC.H"

typedef struct {
    int a;
    int b;
    int c;
    char color;
} face;

typedef struct {
    vec2 points[3];
    char color;
} triangle;

#ifdef __cplusplus
extern "C" {
#endif

vec3 computeNormal(vec3* vertices);

#ifdef __cplusplus
}
#endif

#endif
#ifndef TRINGL_H
#define TRINGL_H

#include "VEC.H"

struct face {
    int a;
    int b;
    int c;
    char color;
};

struct triangle {
    vec2 points[3];
    char color;
};

vec3 computeNormal(vec3* vertices);

#endif
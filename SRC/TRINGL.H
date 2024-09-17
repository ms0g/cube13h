#ifndef TRINGL_H
#define TRINGL_H

#include "VEC.H"

class face {
public:
    face() {}
    face(int a, int b, int c, char color): mA(a), mB(b), mC(c), mColor(color) {}

    int mA;
    int mB;
    int mC;
    char mColor;
};

struct triangle {
    vec2 points[3];
    char color;
    float avg_depth;
};

#endif
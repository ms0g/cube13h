#ifndef MATH_H
#define MATH_H

inline int abs(int v) {
    return v < 0 ? 0 - v : v;
}

inline int ceil(float v){
    return (int)v + 1;
} 

inline int floor(float v) {
    return (int)v;
}

inline int signbit(float v) {
    return v < 0.0 ? 1 : 0;
}

inline int round(float v) {
    return signbit(v) ? ceil(v - 0.5) : floor(v + 0.5);
}

#endif
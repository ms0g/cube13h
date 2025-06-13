#ifndef TRINGL_H
#define TRINGL_H

#include "VEC.H"

typedef struct {
    int a;
    int b;
    int c;
    char color;
} Face;

typedef struct {
    Vec2 points[3];
    char color;
} Triangle;

typedef struct {    
    int count;      
    int capacity;   
    Triangle* data;     
} TriArray;   

Vec3 computeNormal(Vec3* vertices);
// Triangle Array functions
void taInit(TriArray* ta, int size);

void taPushback(TriArray* ta, Triangle* tri);

void taRemove(TriArray* ta, int index);

Triangle* taAt(TriArray* ta, int index);

void taClear(TriArray* ta);

void taFree(TriArray* ta);

#endif
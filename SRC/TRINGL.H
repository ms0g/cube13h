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

typedef struct TriArray {    
    int count;      
    int capacity;   
    Triangle* data;
    void (*reserve)(struct TriArray*, int);
    void (*pushback)(struct TriArray*, Triangle*);
    void (*remove)(struct TriArray*, int);
    Triangle* (*at)(struct TriArray*, int);
    void (*clear)(struct TriArray*);
    void (*free)(struct TriArray*);     
} TriArray;   

Vec3 computeNormal(Vec3* vertices);
// Triangle Array functions
void taInit(TriArray* ta);

void taReserve(TriArray* ta, int size);

void taPushback(TriArray* ta, Triangle* tri);

void taRemove(TriArray* ta, int index);

Triangle* taAt(TriArray* ta, int index);

void taClear(TriArray* ta);

void taFree(TriArray* ta);

#endif
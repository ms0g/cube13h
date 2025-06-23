#include "TRINGL.H"
#include <stdlib.h>

Vec3 computeNormal(Vec3* vertices) {
    Vec3 ab, ac, normal;
    Vec3 a = vertices[0];
    Vec3 b = vertices[1];
    Vec3 c = vertices[2];

    ac = vecSub(&c, &a);
    vecNormalize(&ac);

    ab = vecSub(&b, &a);
    vecNormalize(&ab);
        
    normal = vecCross(&ab, &ac);
    vecNormalize(&normal);

    return normal;
}

void taInit(TriArray* ta, int size) {
    ta->count = 0;
    ta->capacity = size;
    ta->data = (Triangle*)malloc(size * sizeof(Triangle));
}

void taPushback(TriArray* ta, Triangle* tri) {
    if (ta->count == ta->capacity) {
        ta->capacity *= 2;
        ta->data = (Triangle*)realloc(ta->data, ta->capacity * sizeof(Triangle));
    }

    ta->data[ta->count++] = *tri;
}

void taRemove(TriArray* ta, int index) {
    int i;

    if (index < 0 || index >= ta->count) {
        return;
    }
    
    for (i = index; i < ta->count - 1; i++) {
        ta->data[i] = ta->data[i + 1];
    }
    
    ta->count--;
}

Triangle* taAt(TriArray* ta, int index) {
    if (index < 0 || index >= ta->count) {
        return NULL;
    }

    return &ta->data[index];
}

void taClear(TriArray* ta) {
    memset(ta->data, 0, ta->count * sizeof(Triangle));
    ta->count = 0;
}

void taFree(TriArray* ta) {
    free(ta->data);
    ta->data = NULL;
}

#ifndef CUBE_H
#define CUBE_H

#include "VEC.H"
#include "TRINGL.H"
#include "VECTOR.H"

#define V_COUNT 8
#define FACE_COUNT (6 * 2)

class Renderer;
class Cube {
public:
    Cube();

    void update(void);

    void draw(Renderer* renderer, unsigned int frames);

private:
    vec3 cubeRot;
    vec3 cameraPos;
    vec2 projectedVertices[V_COUNT];
    vector<triangle> triangles;
};

#endif
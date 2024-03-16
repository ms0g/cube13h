#ifndef CUBE_H
#define CUBE_H

#define N_POINTS (9 * 9 * 9)

class Renderer;
class Cube {
public:
    Cube();

    void update(void);

    void draw(Renderer* renderer, unsigned int frames);

private:
    struct vec3 {
        float x;
        float y;
        float z;
    };

    struct vec2 {
        float x;
        float y;
    };

    vec3 rotx(vec3& v, vec2& angle);

    vec3 roty(vec3& v, vec2& angle);

    vec3 rotz(vec3& v, vec2& angle);

    vec3 vertices[N_POINTS];
    vec2 projectedVertices[N_POINTS];
    vec3 cubeRot;
    vec3 cameraPos;
    
    char color;
};

#endif
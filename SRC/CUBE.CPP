#include "CUBE.H"
#include "RENDERER.H"
#include <MATH.H>

#define WIDTH 320
#define HEIGHT 200

#define FOV_FACTOR 280

Cube::Cube() {
    int pointCount = 0;
    
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3 newPoint = {x, y, z};
                vertices[pointCount++] = newPoint;
            }
        }
    }

    cameraPos.x = 0;
    cameraPos.y = 0;
    cameraPos.z = -5;
    
    cubeRot.x = 0;
    cubeRot.y = 0;
    cubeRot.z = 0;

    color = BLUE;
}

void Cube::update(void) {
    cubeRot.x += 0.01;
    cubeRot.y += 0.01;
    cubeRot.z += 0.01;

    for (int i = 0; i < N_POINTS; i++) {
        vec3 vertex = vertices[i];

        vec2 angleX = {sin(cubeRot.x), cos(cubeRot.x)};
        vec2 angleY = {sin(cubeRot.y), cos(cubeRot.y)};
        vec2 angleZ = {sin(cubeRot.z), cos(cubeRot.z)};
        
        vec3 transformedVertex = rotx(vertex, angleX);
        transformedVertex = roty(transformedVertex, angleY);
        transformedVertex = rotz(transformedVertex, angleZ);

        // Move the points away from the camera
        transformedVertex.z -= cameraPos.z;

        // Project the current point
        vec2 projectedVertex =  {
            (FOV_FACTOR * transformedVertex.x) / transformedVertex.z, 
            (FOV_FACTOR * transformedVertex.y) / transformedVertex.z};

        // Save the projected 2D vector in the array of projected points
        projectedVertices[i] = projectedVertex;
    }
}

void Cube::draw(Renderer* renderer, unsigned int frames) {
    for (int i = 0; i < N_POINTS; i++) {
        vec2 projectedVertex = projectedVertices[i];
        
        if (!(frames % 35)) {
            ++color;

            if (color > YELLOW) {
                color = BLUE;
            }
        }
       
        renderer->putpixel(
            projectedVertex.x + (WIDTH >> 1),
            projectedVertex.y + (HEIGHT >> 1),
            color
        );
    }
}

vec3 Cube::rotx(vec3& v, vec2& angle) {
    vec3 rotated_vector = {
        v.x,
        v.y * angle.y - v.z * angle.x,
        v.y * angle.x + v.z * angle.y
    };

    return rotated_vector;
}

vec3 Cube::roty(vec3& v, vec2& angle) {
    vec3 rotated_vector = {
        v.x * angle.y - v.z * angle.x,
        v.y,
        v.x * angle.x + v.z * angle.y
    };

    return rotated_vector;
}

vec3 Cube::rotz(vec3& v, vec2& angle) {
    vec3 rotated_vector = {
        v.x * angle.y - v.y * angle.x,
        v.x * angle.x + v.y * angle.y,
        v.z
    };
    
    return rotated_vector;
}


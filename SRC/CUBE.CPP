#include "CUBE.H"
#include "RENDERER.H"
#include <MATH.H>

#define WIDTH 320
#define HEIGHT 200

#define FOV_FACTOR 280

Cube::Cube() {
    int point_count = 0;
    
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3 new_point = {x, y, z};
                vertices[point_count++] = new_point;
            }
        }
    }

    camera_position.x = 0;
    camera_position.y = 0;
    camera_position.z = -5;
    
    cube_rotation.x = 0;
    cube_rotation.y = 0;
    cube_rotation.z = 0;

    color = BLUE;
}

void Cube::update(void) {
    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;

    for (int i = 0; i < N_POINTS; i++) {
        vec3 vertex = vertices[i];

        vec2 angleX = {sin(cube_rotation.x), cos(cube_rotation.x)};
        vec2 angleY = {sin(cube_rotation.y), cos(cube_rotation.y)};
        vec2 angleZ = {sin(cube_rotation.z), cos(cube_rotation.z)};
        
        vec3 transformedVertex = rotx(vertex, angleX);
        transformedVertex = roty(transformedVertex, angleY);
        transformedVertex = rotz(transformedVertex, angleZ);

        // Move the points away from the camera
        transformedVertex.z -= camera_position.z;

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

            if (color > 14) {
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


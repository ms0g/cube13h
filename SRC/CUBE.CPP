#include "CUBE.H"
#include "RENDERER.H"
#include <MATH.H>

#define WIDTH 320
#define HEIGHT 200

#define FOV_FACTOR 280

static const face faces[FACE_COUNT] = {
    // front
    {1, 2, 3, GREEN},
    {1, 3, 4, GREEN},
    // right
    {4, 3, 5, GREEN},
    {4, 5, 6, GREEN},
    // back
    {6, 5, 7, GREEN},
    {6, 7, 8, GREEN},
    // left
    {8, 7, 2, GREEN},
    {8, 2, 1, GREEN},
    // top
    {2, 7, 5, GREEN},
    {2, 5, 3, GREEN},
    // bottom
    {6, 8, 1, GREEN},
    {6, 1, 4, GREEN},
};

Cube::Cube() {
    vertices[0] = vec3(-1, -1, -1); // 1
    vertices[1] = vec3(-1,  1, -1); // 2
    vertices[2] = vec3(1,  1, -1);  // 3
    vertices[3] = vec3(1, -1, -1);  // 4
    vertices[4] = vec3(1,  1,  1);  // 5
    vertices[5] = vec3(1, -1,  1);  // 6
    vertices[6] = vec3(-1,  1,  1); // 7
    vertices[7] = vec3(-1, -1,  1); // 8

    cameraPos.z(-5);
}

void Cube::update(void) {
    cubeRot.sadd(0.01);

    for (int i = 0; i < FACE_COUNT; i++) {
        face face = faces[i];
        
        vec3 faceVertices[3];

        faceVertices[0] = vertices[face.a - 1];
        faceVertices[1] = vertices[face.b - 1];
        faceVertices[2] = vertices[face.c - 1];

        vec3 transformedVertices[3];
        
        for (int i = 0; i < 3; i++) {
            vec3 transformedVertex = faceVertices[i];

            transformedVertex = transformedVertex.rotx(cubeRot.x());
            transformedVertex = transformedVertex.roty(cubeRot.y());
            transformedVertex = transformedVertex.rotz(cubeRot.z());

            // Translate the vertex away from the camera
            float z = transformedVertex.z() + cameraPos.z();
            transformedVertex.z(z);

            // Save transformed vertex in the array of transformed vertices
            transformedVertices[i] = transformedVertex;
        }

        //  // Backface culling test to see if the current face should be projected
        // vec3 vector_a = transformedVertices[0]; /*   A   */
        // vec3 vector_b = transformedVertices[1]; /*  / \  */
        // vec3 vector_c = transformedVertices[2]; /* C---B */

        // // Get the vector subtraction of B-A and C-A
        // vec3 vector_ab = vector_b - vector_a;
        // vec3 vector_ac = vector_c - vector_a;
        // vector_ab.normalize();
        // vector_ac.normalize();
      
        // // Compute the face normal (using cross product to find perpendicular)
        // vec3 normal = vector_ab.cross(vector_ac);
        // //cout << " " << normal.x() << " " << normal.y() << " " << normal.z() << "\n";
        // normal.normalize();

        // // Find the vector between vertex A in the triangle and the camera origin
        // vec3 camera_ray = cameraPos - vector_a;

        // // Calculate how aligned the camera ray is with the face normal (using dot product)
        // float dot_normal_camera = normal.dot(camera_ray);

        // // Bypass the triangles that are looking away from the camera
        // if (dot_normal_camera < 0) {
        //     continue;
        // }

        vec2 projectedPoints[3];

        // Loop all three vertices to perform projection
        for (int j = 0; j < 3; j++) {
            // Project the current vertex
            projectedPoints[j] = project(transformedVertices[j]);

            // Scale and translate the projected points to the middle of the screen
            projectedPoints[j].x += (WIDTH / 2);
            projectedPoints[j].y += (HEIGHT / 2);
        }

        // Calculate the average depth for each face based on the vertices after transformation
        float avg_depth = (transformedVertices[0].z() + transformedVertices[1].z() + transformedVertices[2].z()) / 3.0;

        triangle projectedTriangle = {
            {
                { projectedPoints[0].x, projectedPoints[0].y },
                { projectedPoints[1].x, projectedPoints[1].y },
                { projectedPoints[2].x, projectedPoints[2].y },
            },
            face.color,
            avg_depth
        };
        
        triangles_to_render.push_back(projectedTriangle);
    }

}

void Cube::draw(Renderer* renderer, unsigned int frames) {
    for (int i = 0; i < triangles_to_render.size(); i++) {
        triangle triangle = triangles_to_render[i];

        // Draw filled triangle
        renderer->triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                triangle.color
        );  
    }

    triangles_to_render.clear();
}

vec2 Cube::project(vec3& point) {
    vec2 projected_point = {
        (FOV_FACTOR * point.x()) / point.z(),
        (FOV_FACTOR * point.y()) / point.z()
    };
    return projected_point;
}


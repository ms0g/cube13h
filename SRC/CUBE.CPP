#include "CUBE.H"
#include "RENDERER.H"

#define WIDTH 320
#define HEIGHT 200
#define FOV_FACTOR 280

static const face faces[FACE_COUNT] = {
    // front
    {1, 2, 3, GREEN},
    {1, 3, 4, GREEN},
    // right
    {4, 3, 5, CYAN},
    {4, 5, 6, CYAN},
    // back
    {6, 5, 7, BLUE},
    {6, 7, 8, BLUE},
    // left
    {8, 7, 2, RED},
    {8, 2, 1, RED},
    // top
    {2, 7, 5, LIGHTMAGENTA},
    {2, 5, 3, LIGHTMAGENTA},
    // bottom
    {6, 8, 1, LIGHTBLUE},
    {6, 1, 4, LIGHTBLUE},
};

static const vec3 vertices[V_COUNT] = {
    vec3(-1, -1, -1),
    vec3(-1,  1, -1),
    vec3( 1,  1, -1),
    vec3( 1, -1, -1),
    vec3( 1,  1,  1),
    vec3( 1, -1,  1),
    vec3(-1,  1,  1),
    vec3(-1, -1,  1),
};

Cube::Cube() {
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
        int j;
        for (j = 0; j < 3; j++) {
            vec3 transformedVertex = faceVertices[j];

            transformedVertex = transformedVertex.rotx(cubeRot.x());
            transformedVertex = transformedVertex.roty(cubeRot.y());
            transformedVertex = transformedVertex.rotz(cubeRot.z());

            // Translate the vertex away from the camera
            float z = transformedVertex.z() + cameraPos.z();
            transformedVertex.z(z);

            // Save transformed vertex in the array of transformed vertices
            transformedVertices[j] = transformedVertex;
        }

        vec2 projectedPoints[3];

        // Loop all three vertices to perform projection
        for (j = 0; j < 3; j++) {
            // Project the current vertex
            projectedPoints[j] = transformedVertices[j].project(FOV_FACTOR);

            // Scale and translate the projected points to the middle of the screen
            projectedPoints[j].x += (WIDTH >> 1);
            projectedPoints[j].y += (HEIGHT >> 1);
        }

        triangle projectedTriangle = {
            {
                {projectedPoints[0].x, projectedPoints[0].y},
                {projectedPoints[1].x, projectedPoints[1].y},
                {projectedPoints[2].x, projectedPoints[2].y},
            },
            face.color
        };
        
        triangles.push_back(projectedTriangle);
    }
}

void Cube::draw(Renderer* renderer) {
    for (int i = 0; i < triangles.size(); i++) {
        triangle tri = triangles[i];

        // Draw filled triangle
        renderer->drawFilledTri(
                tri.points[0].x, tri.points[0].y, // vertex A
                tri.points[1].x, tri.points[1].y, // vertex B
                tri.points[2].x, tri.points[2].y, // vertex C
                tri.color
        );  
    }

    triangles.clear();
}


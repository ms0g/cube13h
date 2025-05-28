#include "CUBE.H"
#include "RENDERER.H"

#define WIDTH 320
#define HEIGHT 200
#define FOV_FACTOR 280

static const face faces[FACE_COUNT] = {
    // front
    {1, 2, 3, 0x50},
    {1, 3, 4, 0x51},
    // right
    {4, 3, 5, 0x40},
    {4, 5, 6, 0x41},
    // back
    {6, 5, 7, 0x22},
    {6, 7, 8, 0x23},
    // left
    {8, 7, 2, 0x2A},
    {8, 2, 1, 0x2B},
    // top
    {2, 7, 5, 0x28},
    {2, 5, 3, 0x29},
    // bottom
    {6, 8, 1, 0x36},
    {6, 1, 4, 0x37},
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
    cameraPos.z = 5;
}

void Cube::update(void) {
    sadd(cubeRot, 0.02);

    for (int i = 0; i < FACE_COUNT; i++) {
        face face = faces[i];
        
        vec3 faceVertices[3];

        faceVertices[0] = vertices[face.a - 1];
        faceVertices[1] = vertices[face.b - 1];
        faceVertices[2] = vertices[face.c - 1];

        int j;
        vec3 transformedVertices[3];
        for (j = 0; j < 3; j++) {
            vec3 transformedVertex = faceVertices[j];

            transformedVertex = rotx(transformedVertex, cubeRot.x);
            transformedVertex = roty(transformedVertex, cubeRot.y);
            transformedVertex = rotz(transformedVertex, cubeRot.z);

            // Translate the vertex away from the camera
            transformedVertex.z = transformedVertex.z - cameraPos.z;

            // Save transformed vertex in the array of transformed vertices
            transformedVertices[j] = transformedVertex;
        }
        
        // Backface Culling
        vec3 cameraRay = cameraPos - transformedVertices[0];
        vec3 normal = computeNormal(transformedVertices);
        
        double dotNormalCamera = dot(normal, cameraRay);
    
        if (dotNormalCamera < 0) 
            continue;

        vec2 projectedPoints[3];
        // Loop all three vertices to perform projection
        for (j = 0; j < 3; j++) {
            // Project the current vertex
            projectedPoints[j] = project(transformedVertices[j], FOV_FACTOR);

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

void Cube::draw(const Renderer* renderer) {
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


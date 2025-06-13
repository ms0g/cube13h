#include "VEC.H"
#include "TRINGL.H"
#include "TIMER.H"
#include "KEYBRD.H"
#include "RENDERER.H"

#define WIDTH 320
#define HEIGHT 200
#define FOV_FACTOR 280
#define V_COUNT 8
#define FACE_COUNT (6 * 2)

static int isRunning;
vec3 cubeRot;
vec3 cameraPos;
TriArray triangles;

static const Face faces[FACE_COUNT] = {
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
    {-1, -1, -1},
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    { 1,  1,  1},
    { 1, -1,  1},
    {-1,  1,  1},
    {-1, -1,  1},
};

static void processInput(void) {
    char key = kbHit();

    if (key == ESC) {
        isRunning = 0;
    }
}

static void update(void) {
    int i, j;
    Face face;
    vec3 cameraRay;
    vec3 normal;
    vec3 transformedVertex;
    vec3 faceVertices[3];
    vec3 transformedVertices[3];
    vec2 projectedPoints[3];
    Triangle projectedTriangle;

    double dotNormalCamera;
    
    sadd(&cubeRot, 0.02);

    for (i = 0; i < FACE_COUNT; i++) {
        face = faces[i];

        faceVertices[0] = vertices[face.a - 1];
        faceVertices[1] = vertices[face.b - 1];
        faceVertices[2] = vertices[face.c - 1];

        for (j = 0; j < 3; j++) {
            transformedVertex = faceVertices[j];

            transformedVertex = rotx(&transformedVertex, cubeRot.x);
            transformedVertex = roty(&transformedVertex, cubeRot.y);
            transformedVertex = rotz(&transformedVertex, cubeRot.z);

            // Translate the vertex away from the camera
            transformedVertex.z = transformedVertex.z - cameraPos.z;

            // Save transformed vertex in the array of transformed vertices
            transformedVertices[j] = transformedVertex;
        }
        
        // Backface Culling
        cameraRay = sub(&cameraPos, &transformedVertices[0]);
        normal = computeNormal(transformedVertices);
        
        dotNormalCamera = dot(&normal, &cameraRay);
    
        if (dotNormalCamera < 0) 
            continue;

        // Loop all three vertices to perform projection
        for (j = 0; j < 3; j++) {
            // Project the current vertex
            projectedPoints[j] = project(&transformedVertices[j], FOV_FACTOR);

            // Scale and translate the projected points to the middle of the screen
            projectedPoints[j].x += (WIDTH >> 1);
            projectedPoints[j].y += (HEIGHT >> 1);
        }

        projectedTriangle.points[0] = projectedPoints[0];
        projectedTriangle.points[1] = projectedPoints[1];
        projectedTriangle.points[2] = projectedPoints[2];
        projectedTriangle.color = face.color;
        
		taPushback(&triangles, &projectedTriangle);
    }    
}

static void render(void) {
    int i;
    Triangle* tri;

  	rndClear(0x0);

    for (i = 0; i < triangles.count; i++) {
        tri = taAt(&triangles ,i);

        // Draw filled triangle
        rndDrawFilledTri(
                tri->points[0].x, tri->points[0].y, // vertex A
                tri->points[1].x, tri->points[1].y, // vertex B
                tri->points[2].x, tri->points[2].y, // vertex C
                tri->color
        );  
    }

   	taClear(&triangles);

    rndUpdateBuffer();
}



void main(void) {
	isRunning = 1;
	cameraPos.z = 5;

    rndInit();
    kbInit();
	_initTimer();
    
	taInit(&triangles, 12);
    
	while (isRunning) {
        processInput();
        update();
        render();
    }

	taFree(&triangles);

    rndExit();
    kbExit();
	_exitTimer();
}

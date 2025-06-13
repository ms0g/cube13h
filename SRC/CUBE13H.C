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
static Vec3 cubeRot;
static Vec3 cameraPos;
static TriArray triangles;

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

static const Vec3 vertices[V_COUNT] = {
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
    Vec3 cameraRay;
    Vec3 normal;
    Vec3 transformedVertex;
    Vec3 faceVertices[3];
    Vec3 transformedVertices[3];
    Vec2 vecProjectedPoints[3];
    Triangle vecProjectedTriangle;
    double vecDotNormalCamera;
    
    vecSAdd(&cubeRot, 0.02);

    for (i = 0; i < FACE_COUNT; i++) {
        face = faces[i];

        faceVertices[0] = vertices[face.a - 1];
        faceVertices[1] = vertices[face.b - 1];
        faceVertices[2] = vertices[face.c - 1];

        for (j = 0; j < 3; j++) {
            transformedVertex = faceVertices[j];

            transformedVertex = vecRotx(&transformedVertex, cubeRot.x);
            transformedVertex = vecRoty(&transformedVertex, cubeRot.y);
            transformedVertex = vecRotz(&transformedVertex, cubeRot.z);

            // Translate the vertex away from the camera
            transformedVertex.z = transformedVertex.z - cameraPos.z;

            // Save transformed vertex in the array of transformed vertices
            transformedVertices[j] = transformedVertex;
        }
        
        // Backface Culling
        cameraRay = vecSub(&cameraPos, &transformedVertices[0]);
        normal = computeNormal(transformedVertices);
        
        vecDotNormalCamera = vecDot(&normal, &cameraRay);
    
        if (vecDotNormalCamera < 0) 
            continue;

        // Loop all three vertices to perform vecProjection
        for (j = 0; j < 3; j++) {
            // vecProject the current vertex
            vecProjectedPoints[j] = vecProject(&transformedVertices[j], FOV_FACTOR);

            // Scale and translate the vecProjected points to the middle of the screen
            vecProjectedPoints[j].x += (WIDTH >> 1);
            vecProjectedPoints[j].y += (HEIGHT >> 1);
        }

        vecProjectedTriangle.points[0] = vecProjectedPoints[0];
        vecProjectedTriangle.points[1] = vecProjectedPoints[1];
        vecProjectedTriangle.points[2] = vecProjectedPoints[2];
        vecProjectedTriangle.color = face.color;
        
		taPushback(&triangles, &vecProjectedTriangle);
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
	_tmrInit();
    
	taInit(&triangles, 12);
    
	while (isRunning) {
        processInput();
        update();
        render();
    }

	taFree(&triangles);

    rndExit();
    kbExit();
	_tmrExit();
}

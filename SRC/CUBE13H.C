#include "VEC.H"
#include "VGA.H"
#include "UI.H"
#include "TRINGL.H"
#include "TIMER.H"
#include "KEYBRD.H"
#include "RENDERER.H"

#define WIDTH 320
#define HEIGHT 200
#define HALF_WIDTH 160
#define HALF_HEIGHT 100
#define FOV_FACTOR 280
#define VERTEX_COUNT 8
#define FACE_COUNT 12

static Vec3 cubeRot;
static Vec3 cameraPos;
static TriArray triangles;
static int isRunning;
static unsigned int fps, frames, lastTime, currentTime;

static Face faces[FACE_COUNT] = {
    // front
    {1, 2, 3, 0x50, {0, 0, -1}},
    {1, 3, 4, 0x51, {0, 0, -1}},
    // right
    {4, 3, 5, 0x40, {1, 0, 0}},
    {4, 5, 6, 0x41, {1, 0, 0}},
    // back
    {6, 5, 7, 0x22, {0, 0, 1}},
    {6, 7, 8, 0x23, {0, 0, 1}},
    // left
    {8, 7, 2, 0x2A, {-1, 0, 0}},
    {8, 2, 1, 0x2B, {-1, 0, 0}},
    // top
    {2, 7, 5, 0x28, {0, 1, 0}},
    {2, 5, 3, 0x29, {0, 1, 0}},
    // bottom
    {6, 8, 1, 0x36, {0, -1, 0}},
    {6, 1, 4, 0x37, {0, -1, 0}},
};

static const Vec3 vertices[VERTEX_COUNT] = {
    {-1, -1, -1},
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    { 1,  1,  1},
    { 1, -1,  1},
    {-1,  1,  1},
    {-1, -1,  1},
};

static void calculateFPS(void) {
    frames++;
    currentTime = _getTick();
    // runs every second
    if (currentTime - lastTime >= TICKS_PER_SECOND) {
        lastTime = currentTime;
        fps = frames;
        frames = 0;
    }
}

static void processInput(void) {
    if (kbHit(ESC)) {
        isRunning = 0;
    } else if (kbHit(U_ARROW)) {
        cameraPos.z -= 0.1; 
    } else if (kbHit(D_ARROW)) {
        cameraPos.z += 0.1;
    }
}

static void update(void) {
    int i, j;
    Vec2 pv0, pv1, pv2;
    Vec3 transformedVertices[VERTEX_COUNT];
    Triangle projectedTriangle;

    calculateFPS();

    uiUpdate(fps);
    
    vecSAdd(&cubeRot, 0.02);

    for (i = 0; i < VERTEX_COUNT; i++) {
        Vec3 transformedVertex = vertices[i];

        // Rotate the vertex around the cube's center
        transformedVertex = vecRotx(&transformedVertex, cubeRot.x);
        transformedVertex = vecRoty(&transformedVertex, cubeRot.y);
        transformedVertex = vecRotz(&transformedVertex, cubeRot.z);

        // Translate the vertex away from the camera
        transformedVertex.z = transformedVertex.z - cameraPos.z;

        // Save transformed vertex in the array of transformed vertices
        transformedVertices[i] = transformedVertex;
    }

    for (i = 0; i < FACE_COUNT; i++) {
        Face face = faces[i];

        Vec3 fv0 = transformedVertices[face.a - 1];
        Vec3 fv1 = transformedVertices[face.b - 1];
        Vec3 fv2 = transformedVertices[face.c - 1];

        Vec3 cameraRay = vecSub(&cameraPos, &fv0);

        Vec3 normal = face.normal;
        normal = vecRotx(&normal, cubeRot.x);
        normal = vecRoty(&normal, cubeRot.y);
        normal = vecRotz(&normal, cubeRot.z);
        
        // Backface Culling
        if (vecDot(&normal, &cameraRay) < 0) 
            continue;

        pv0 = vecProject(&fv0, FOV_FACTOR);
        pv0.x += HALF_WIDTH;
        pv0.y += HALF_HEIGHT ;
        projectedTriangle.points[0] = pv0;

        pv1 = vecProject(&fv1, FOV_FACTOR);
        pv1.x += HALF_WIDTH;
        pv1.y += HALF_HEIGHT ;
        projectedTriangle.points[1] = pv1;

        pv2 = vecProject(&fv2, FOV_FACTOR);
        pv2.x += HALF_WIDTH;
        pv2.y += HALF_HEIGHT ;
        projectedTriangle.points[2] = pv2;

        projectedTriangle.color = face.color;
        
		taPushback(&triangles, &projectedTriangle);
    }    
}

static void render(void) {
    int i;
    Triangle* tri;

  	vgaClearOffscreen(0x0);

    uiDraw();

    for (i = 0; i < triangles.count; i++) {
        tri = taAt(&triangles, i);

        // Draw filled triangle
        rndDrawFilledTri(
            tri->points[0].x, tri->points[0].y, // vertex A
            tri->points[1].x, tri->points[1].y, // vertex B
            tri->points[2].x, tri->points[2].y, // vertex C
            tri->color
        );  
    }

   	taClear(&triangles);

    vgaUpdateVram();
}

void main(void) {
    cameraPos.x = 0;
    cameraPos.y = 0;
	cameraPos.z = 5;
    
    cubeRot.x = 0.0;
    cubeRot.y = 0.0;
    cubeRot.z = 0.0;
    
    isRunning = 1;
    fps = frames = lastTime = currentTime = 0;

    vgaInit();
    kbInit();
	_tmrInit();
    uiInit();

	taInit(&triangles, 2);
    
	while (isRunning) {
        processInput();
        update();
        render();
    }

	taFree(&triangles);

    vgaExit();
    kbExit();
	_tmrExit();
}

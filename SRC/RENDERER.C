#include "RENDERER.H"
#include "VGA.H"
#include "MATH.H"

static int isTopLeft(int x0, int y0, int x1, int y1);
static int edgeFunction(int x0, int y0, int x1, int y1, int x2, int y2);

void rndPutchar(int x, int y, char color, const int (*font)[5][5]) {
    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if ((*font)[j][i]) {
                vgaPutPixel(x + i, y + j, color);
            }
        }
    }
}

void rndDDA(int x0, int y0, int x1, int y1, char color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step = (absf(dx) >= absf(dy)) ? absf(dx) : absf(dy);

    float xinc = dx / (float)(step);
    float yinc = dy / (float)(step);

    float x = x0;
    float y = y0;

    int i;
    for (i = 0; i < step; ++i) {
        vgaPutPixel(round(x), round(y), color);
        
        x += xinc;
        y += yinc;
    }
}

void rndBresenham(int x0, int y0, int x1, int y1, char color) {
    int dx = absf(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = absf(y1 - y0);
    int sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy)/2;
    int e2;

    while (x0 != x1 || y0 != y1) {
        vgaPutPixel(x0, y0, color);
        
        e2 = err;
        
        if (e2 > -dx) {
            err -= dy; 
            x0 += sx; 
        }

        if (e2 < dy) { 
            err += dx; 
            y0 += sy; 
        }
    }
}

void rndDrawRect(int x, int y, int width, int height, char color) {
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            vgaPutPixel(x + i, y + j, color);
        }
    }
}

void rndDrawTri(int x0, int y0, int x1, int y1, int x2, int y2, char color) {
    rndBresenham(x0, y0, x1, y1, color);
    rndBresenham(x1, y1, x2, y2, color);
    rndBresenham(x2, y2, x0, y0, color);
}

void rndDrawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, char color){
    int xmin = min(min(x0, x1), x2);
    int ymin = min(min(y0, y1), y2);
    int xmax = max(max(x0, x1), x2);
    int ymax = max(max(y0, y1), y2);

    int delta_w0_col = y1 - y2;
    int delta_w1_col = y2 - y0;
    int delta_w2_col = y0 - y1;

    int delta_w0_row = x2 - x1;
    int delta_w1_row = x0 - x2;
    int delta_w2_row = x1 - x0;

    int bias0 = isTopLeft(x1, y1, x2, y2) ? 0 : -1;
    int bias1 = isTopLeft(x2, y2, x0, y0) ? 0 : -1;
    int bias2 = isTopLeft(x0, y0, x1, y1) ? 0 : -1;

    int px = xmin;
    int py = ymin;

    int w0_row = edgeFunction(x1, y1, x2, y2, px, py) + bias0;
    int w1_row = edgeFunction(x2, y2, x0, y0, px, py) + bias1;
    int w2_row = edgeFunction(x0, y0, x1, y1, px, py) + bias2;

    int y, x;
    for (y = ymin; y <= ymax; ++y) {
        int w0 = w0_row;
        int w1 = w1_row;
        int w2 = w2_row;
        
        for (x = xmin; x <= xmax; ++x) {
            if ((w0 >= 0) && (w1 >= 0) && (w2 >= 0)) {
                vgaPutPixel(x, y, color);
            }

            w0 += delta_w0_col;
            w1 += delta_w1_col;
            w2 += delta_w2_col;
        }

        w0_row += delta_w0_row;
        w1_row += delta_w1_row;
        w2_row += delta_w2_row;
    }
 }

static int isTopLeft(int x0, int y0, int x1, int y1) {
    int edx = x1 - x0;
    int edy = y1 - y0;

    int isTopEdge = (edy == 0) && edx > 0;
    int isLeftEdge = edy < 0;
    
    return isTopEdge || isLeftEdge;
}

static int edgeFunction(int x0, int y0, int x1, int y1, int x2, int y2) {
    return (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
}
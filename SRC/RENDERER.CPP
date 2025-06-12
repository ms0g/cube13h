#include "RENDERER.H"
#include "VGA.H"
#include "MATH.H"

 Renderer::Renderer() {
        vgaInit();
    }
Renderer::~Renderer() {
        vgaExit();
    }

void Renderer::putchar(int x, int y, char color, const int (*font)[5][5]) const {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if ((*font)[j][i]) {
                vgaPutPixel(x + i, y + j, color);
            }
        }
    }
}

void Renderer::dda(int x0, int y0, int x1, int y1, char color) const {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step = (absf(dx) >= absf(dy)) ? absf(dx) : absf(dy);

    float xinc = dx / (float)(step);
    float yinc = dy / (float)(step);

    float x = x0;
    float y = y0;

    for (int i = 0; i < step; ++i) {
        vgaPutPixel(round(x), round(y), color);
        
        x += xinc;
        y += yinc;
    }
}

void Renderer::bresenham(int x0, int y0, int x1, int y1, char color) const {
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

void Renderer::drawRect(int x, int y, int width, int height, char color) const {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            vgaPutPixel(x + i, y + j, color);
        }
    }
}

void Renderer::drawTri(int x0, int y0, int x1, int y1, int x2, int y2, char color) const {
    bresenham(x0, y0, x1, y1, color);
    bresenham(x1, y1, x2, y2, color);
    bresenham(x2, y2, x0, y0, color);
}

 void Renderer::drawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, char color) const {
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

    int w0_row = determinant(x1, y1, x2, y2, px, py) + bias0;
    int w1_row = determinant(x2, y2, x0, y0, px, py) + bias1;
    int w2_row = determinant(x0, y0, x1, y1, px, py) + bias2;

    for (int y = ymin; y < ymax; ++y) {
        int w0 = w0_row;
        int w1 = w1_row;
        int w2 = w2_row;
        
        for (int x = xmin; x < xmax; ++x) {
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

void Renderer::clear(char color) const {
    vgaClearOffscreen(color);
}

void Renderer::updateBuffer(void) const {
    vgaUpdateVram();
}

int Renderer::isTopLeft(int x0, int y0, int x1, int y1) const {
    int edx = x1 - x0;
    int edy = y1 - y0;
    
    int isTopEdge = (edy == 0) && edx > 0;
    int isLeftEdge = edy < 0;
    
    return isTopEdge || isLeftEdge;
}
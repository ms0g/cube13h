#include "RENDERER.H"

#define abs(x) (x < 0 ? 0 - x : x)

#define ceil(x) ((int)x + 1)

#define floor(x) (int)x

#define signbit(x) x < 0.0 ? 1 : 0

#define round(x) signbit(x) ? ceil(x - 0.5) : floor(x + 0.5)

#define swap(x, y) { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); }

void Renderer::putpixel(int x, int y, char color) {
    vga.putpixel(x, y, color);
}

void Renderer::putchar(int x, int y, char color, const int (*font)[5][5]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if ((*font)[j][i]) {
                vga.putpixel(x + i, y + j, color);
            }
        }
    }
}

void Renderer::drawLine(int x0, int y0, int x1, int y1, char color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    float xinc = dx / (float)(step);
    float yinc = dy / (float)(step);

    float x = x0;
    float y = y0;

    for (int i = 0; i < step; ++i) {
        vga.putpixel(round(x), round(y), color);
        
        x += xinc;
        y += yinc;
    }
}

void Renderer::rectangle(int x, int y, int width, int height, char color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            vga.putpixel(x + i, y + j, color);
        }
    }
}

void Renderer::drawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color) {
    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y1 > y2) {
        swap(y1, y2);
        swap(x1, x2);
    }

    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y1 == y2) {
        // Draw flat-bottom triangle
        fillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        // Draw flat-top triangle
        fillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // Calculate the new vertex (Mx,My) using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        fillFlatBottomTriangle(x0, y0, x1, y1, Mx, My, color);

        // Draw flat-top triangle
        fillFlatTopTriangle(x1, y1, Mx, My, x2, y2, color);
    }
}

void Renderer::circle(int xc, int yc, int r, char color) {
    int x = 0, y = r; 
    int d = 3 - 2 * r;

    _circle(xc, yc, x, y, color); 
    
    while (y >= x) { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } else {
            d = d + 4 * x + 6;
        }
             
        _circle(xc, yc, x, y, color);
    }
}


void Renderer::fillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color) {
    // Inverse slope because we're calculating the x changes with respect to y
    float invSlope1 = (float)(x1 - x0) / (y1 - y0);
    float invSlope2 = (float)(x2 - x0) / (y2 - y0);

    // Start x_start and x_end from the top vertex (x0,y0)
    float xStart = x0;
    float xEnd = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; ++y) {
        drawLine(xStart, y, xEnd, y, color);
        xStart += invSlope1;
        xEnd += invSlope2;
    }
}

void Renderer::fillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color) {
    float invSlope1 = (float)(x2 - x0) / (y2 - y0);
    float invSlope2 = (float)(x2 - x1) / (y2 - y1);

    // Start x_start and x_end from the top vertex (x0,y0)
    float xStart = x2;
    float xEnd = x2;

    // Loop all the scanlines from top to bottom
    for (int y = y2; y >= y0; --y) {
        drawLine(xStart, y, xEnd, y, color);
        xStart -= invSlope1;
        xEnd -= invSlope2;
    }
}

void Renderer::_circle(int xc, int yc, int x, int y, char color) { 
    vga.putpixel(xc+x, yc+y, color); 
    vga.putpixel(xc-x, yc+y, color); 
    vga.putpixel(xc+x, yc-y, color); 
    vga.putpixel(xc-x, yc-y, color); 
    vga.putpixel(xc+y, yc+x, color); 
    vga.putpixel(xc-y, yc+x, color); 
    vga.putpixel(xc+y, yc-x, color); 
    vga.putpixel(xc-y, yc-x, color); 
}

void Renderer::clear(char color) {
    vga.clroffscreen(color);
}

void Renderer::updateBuffer(void) {
    vga.updateVRAM();
}
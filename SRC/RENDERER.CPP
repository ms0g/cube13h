#include "RENDERER.H"
#include "MATH.H"

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

void Renderer::dda(int x0, int y0, int x1, int y1, char color) {
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

void Renderer::bresenham(int x0, int y0, int x1, int y1, char color) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy)/2;
    int e2;

    while (x0 != x1 || y0 != y1) {
        vga.putpixel(x0, y0, color);
        
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

void Renderer::drawRect(int x, int y, int width, int height, char color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            vga.putpixel(x + i, y + j, color);
        }
    }
}

void Renderer::drawTri(int x0, int y0, int x1, int y1, int x2, int y2, char color) {
    bresenham(x0, y0, x1, y1, color);
    bresenham(x1, y1, x2, y2, color);
    bresenham(x2, y2, x0, y0, color);
}

 void Renderer::drawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, char color) {
    int xmin = min(min(x0, x1), x2);
    int ymin = min(min(y0, y1), y2);
    int xmax = max(max(x0, x1), x2);
    int ymax = max(max(y0, y1), y2);

    for (int y = ymin; y < ymax; ++y) {
        for (int x = xmin; x < xmax; ++x) {
            int w0 = edgeCross(x1, y1, x2, y2, x, y);
            int w1 = edgeCross(x2, y2, x0, y0, x, y);
            int w2 = edgeCross(x0, y0, x1, y1, x, y);
            
            if ((w0 >= 0) && (w1 >= 0) && (w2 >= 0)) {
                vga.putpixel(x, y, color);
            }
        }
    }
 }

void Renderer::drawCircle(int xc, int yc, int r, char color) {
    int x = 0, y = r; 
    int d = 3 - 2 * r;

    circle(xc, yc, x, y, color); 
    
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
             
        circle(xc, yc, x, y, color);
    }
}

void Renderer::circle(int xc, int yc, int x, int y, char color) { 
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
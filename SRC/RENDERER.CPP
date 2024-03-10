#include "RENDERER.H"
#include <MATH.H>

#define signbit(x) x < 0.0 ? 1 : 0

#define round(x) signbit(x) ? ceil(x-0.5) : floor(x+0.5)

void Renderer::putpixel(int x, int y, char color) {
    vga.putpixel_f(x, y, color);
}

void Renderer::putchar(int x, int y, char color, const int (*font)[5][5]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if ((*font)[j][i]) {
                vga.putpixel_f(x + i, y + j, color);
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
        vga.putpixel_f(round(x), round(y), color);
        
        x += xinc;
        y += yinc;
    }
}

void Renderer::rectangle(int x, int y, int width, int height, char color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            vga.putpixel_f(x + i, y + j, color);
        }
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

void Renderer::_circle(int xc, int yc, int x, int y, char color) { 
    vga.putpixel_f(xc+x, yc+y, color); 
    vga.putpixel_f(xc-x, yc+y, color); 
    vga.putpixel_f(xc+x, yc-y, color); 
    vga.putpixel_f(xc-x, yc-y, color); 
    vga.putpixel_f(xc+y, yc+x, color); 
    vga.putpixel_f(xc-y, yc+x, color); 
    vga.putpixel_f(xc+y, yc-x, color); 
    vga.putpixel_f(xc-y, yc-x, color); 
}

void Renderer::clear(char color) {
    vga.clroffscreen(color);
}

void Renderer::updateBuffer(void) {
    vga.updateVRAM();
}
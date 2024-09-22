#include "RENDERER.H"

#define abs(x) (x < 0 ? 0 - x : x)

#define ceil(x) ((int)x + 1)

#define floor(x) (int)x

#define signbit(x) x < 0.0 ? 1 : 0

#define round(x) signbit(x) ? ceil(x - 0.5) : floor(x + 0.5)

#define swap(x, y) { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); }

// vec3 computeBarycentricWeights(vec2 a, vec2 b, vec2 c, vec2 p) {
//     vec2 ac = c - a;
//     vec2 ab = b - a;
//     vec2 ap = p - a;
//     vec2 pc = c - p;
//     vec2 pb = b - p;

//     // Compute the area of the full parallegram/triangle ABC using 2D cross product
//     float areaParallelogramABC = ac.cross(ab);

//     // Alpha is the area of the small parallelogram/triangle PBC divided by the area of the full parallelogram/triangle ABC
//     float alpha = pc.cross(pb) / areaParallelogramABC;

//     // Beta is the area of the small parallelogram/triangle APC divided by the area of the full parallelogram/triangle ABC
//     float beta = ac.cross(ap) / areaParallelogramABC;

//     // Weight gamma is easily found since barycentric coordinates always add up to 1.0
//     float gamma = 1 - alpha - beta;

//     return vec3(alpha, beta, gamma);
// }

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

void Renderer::rectangle(int x, int y, int width, int height, char color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            vga.putpixel(x + i, y + j, color);
        }
    }
}

void Renderer::triangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned char color) {
    dda(x0, y0, x1, y1, color);
    dda(x1, y1, x2, y2, color);
    dda(x2, y2, x0, y0, color);
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
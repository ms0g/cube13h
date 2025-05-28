#ifndef RENDERER_H
#define RENDERER_H

#include "VGA.H"

class Renderer {
public:
    void putchar(int x, int y, char color, const int (*font)[5][5]) const;

    void dda(int x0, int y0, int x1, int y1, char color) const;
    
    void bresenham(int x0, int y0, int x1, int y1, char color) const;

    void drawRect(int x, int y, int width, int height, char color) const;
    
    void drawTri(int x0, int y0, int x1, int y1, int x2, int y2, char color) const;

    void drawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, char color) const;
    
    void clear(char color) const;

    void updateBuffer(void) const;

private:
    int isTopLeft(int x0, int y0, int x1, int y1) const;
   
    VGA vga;
};

#endif
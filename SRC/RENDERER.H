#ifndef RENDERER_H
#define RENDERER_H

#include "VGA.H"

enum COLORS {
    BLACK,		    /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,		/* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

class Renderer {
public:
    void putchar(int x, int y, char color, const int (*font)[5][5]);

    void dda(int x0, int y0, int x1, int y1, char color);
    
    void bresenham(int x0, int y0, int x1, int y1, char color);

    void drawRect(int x, int y, int width, int height, char color);
    
    void drawTri(int x0, int y0, int x1, int y1, int x2, int y2, char color);

    void drawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, char color);
    
    void clear(char color);

    void updateBuffer(void);

private:
    int isTopLeft(int x0, int y0, int x1, int y1);
   
   VGA vga;
};

#endif
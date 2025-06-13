#ifndef VGA_H
#define VGA_H

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

void vgaInit(void);

void vgaExit(void);
  
void vgaPutPixel(int x, int y, char color);

void vgaClearOffscreen(char color);

void vgaUpdateVram(void);

#endif
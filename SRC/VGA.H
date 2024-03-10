#ifndef VGA_H
#define VGA_H

class VGA {
public:
    VGA();

    ~VGA();
    
    void clrscr(char color);

    void clroffscreen(char color);
  
    void putpixel_s(int x, int y, char color);

    void putpixel_f(int x, int y, char color);

    void waitVRetrace(void);

    void updateVRAM(void);

private:
    unsigned char far* VRAM;
    unsigned char far* offscreen;
};

#endif
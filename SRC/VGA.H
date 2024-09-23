#ifndef VGA_H
#define VGA_H

#include <_defs.h>
#include <string.h>
// VGA GFX Mode
#define MODE_VGA_13H 0x13
// VGA Text Mode
#define MODE_VGA_3H  0x3

#define VRAM_SIZE 64000u

#ifdef __cplusplus
extern "C" {
#endif
void _Cdecl _waitvretrace(void);
void _Cdecl _putpixel(int x, int y, char color);
void _Cdecl _initMode(int mode);
#ifdef __cplusplus
}
#endif

class VGA {
public:
    VGA();

    ~VGA();

    void clroffscreen(char color);
  
    void putpixel(int x, int y, char color);

    void updateVRAM(void);

private:
    unsigned char far* VRAM;
    unsigned char far* offscreen;
};

inline void VGA::clroffscreen(char color) {
    _fmemset(offscreen, color, VRAM_SIZE);
}

inline void VGA::putpixel(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

inline void VGA::updateVRAM(void) {
    _waitvretrace();

    _fmemcpy(VRAM, offscreen, VRAM_SIZE);
}

#endif
#include "VGA.H"
#include <MALLOC.H>
#include <STRING.H>

#define VRAM_SIZE 64000u

VGA::VGA() {
    VRAM = (unsigned char far*)0xA0000000L;
    offscreen = (unsigned char far*)farmalloc(VRAM_SIZE);

    if (offscreen) {
        _fmemset(offscreen, 0, VRAM_SIZE);
        
        _initMode(MODE_VGA_13H);
    } 
}

VGA::~VGA() {
    farfree(offscreen);
    // Return to the text mode
   _initMode(MODE_VGA_3H);
}

void VGA::clroffscreen(char color) {
    _fmemset(offscreen, color, VRAM_SIZE);
}

void VGA::putpixel(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

void VGA::updateVRAM(void) {
    _waitvretrace();

    _fmemcpy(VRAM, offscreen, VRAM_SIZE);
}
   

#include "VGA.H"
#include <MALLOC.H>
#include <STRING.H>

VGA::VGA() {
    VRAM = (unsigned char far*)0xA0000000L;
    offscreen = (unsigned char far*)farmalloc(64000u);

    if (offscreen) {
        _fmemset(offscreen, 0, 64000u);
        
        _initMode(MODE_VGA_13H);
    } 
}

VGA::~VGA() {
    farfree(offscreen);
    // Return to the text mode
   _initMode(MODE_VGA_3H);
}

void VGA::clroffscreen(char color) {
    _fmemset(offscreen, color, 64000u);
}

void VGA::putpixel(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

void VGA::updateVRAM(void) {
    _waitvretrace();

    _fmemcpy(VRAM, offscreen, 64000u);
}
   

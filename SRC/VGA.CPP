#include "VGA.H"
#include <malloc.h>

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
   

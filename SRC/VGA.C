#include "VGA.H"
#include <string.h>
#include <malloc.h>
// VGA Graphics Mode
#define VGA_MODE_13H 0x13
// VGA Text Mode
#define VGA_MODE_3H  0x3

#define VRAM_SIZE 64000u

static unsigned char far* vram;
static unsigned char far* offscreen;

static void _waitvretrace(void);
static void _initMode(int mode);

void vgaInit(void) {
    vram = (unsigned char far*)0xA0000000L;
    offscreen = (unsigned char far*)farmalloc(VRAM_SIZE);

    if (offscreen) {
        _fmemset(offscreen, 0, VRAM_SIZE);
        _initMode(VGA_MODE_13H);
    } 
}

void vgaExit(void) {
     farfree(offscreen);
    _initMode(VGA_MODE_3H);
}

void vgaClearOffscreen(char color) {
    _fmemset(offscreen, color, VRAM_SIZE);
}

void vgaPutPixel(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

void vgaUpdateVram(void) {
    _waitvretrace();
    _fmemcpy(vram, offscreen, VRAM_SIZE);
}

static void _waitvretrace(void) {
    asm { cli }
v1: 
    asm {
        mov dx, 03dah  
        in al, dx      
        test al, 08h   
        jnz v1
    }
v2:
    asm { 
        mov dx, 03dah
        in al, dx
        test al, 08h
        jz v2          
        sti
    }
}

static void _initMode(int mode) {
    asm {
        xor ah, ah    
        mov ax, mode
        int 10h
    }
}

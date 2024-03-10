#include "VGA.H"
#include <MALLOC.H>
#include <STRING.H>

VGA::VGA() {
    VRAM = (unsigned char far*)0xA0000000L;
    offscreen = (unsigned char far*)farmalloc(64000u);

    if (offscreen) {
        _fmemset(offscreen, 0, 64000u);
        
        asm {
            xor ah, ah      // change video mode
            mov al, 0x13    // 320x200x256
            int 0x10        //interrupt
        }
    } 
}

VGA::~VGA() {
    farfree(offscreen);
    // Return to the text mode
    asm {
        xor ah, ah
        mov al, 0x3
        int 0x10
    }
}

void VGA::clrscr(char color) {
    asm {
        xor al, al
        mov ah, 0x6
        xor bl, bl
        mov bh, color
        mov cx, 0x0
        mov dx, 0x182a 
        int 0x10 
    }
}

void VGA::clroffscreen(char color) {
    _fmemset(offscreen, color, 64000u);
}

void VGA::putpixel_s(int x, int y, char color) {
    asm {
        mov ah, 0x0C
        mov al, color
        xor bh, bh             
        mov cx, x           
        mov dx, y    
        int 0x10          
    }
}

void VGA::putpixel_f(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

void VGA::waitVRetrace(void) {
    asm cli
    //If vert. retrace bit is set, wait for it to clear
v1: 
    asm {
        mov dx, 0x03da  //dx <- VGA status register
        in al, dx       //al <- status byte
        test al, 0x08   //is bit 3 (vertical retrace bit) set
        jnz v1          //If so, wait for it to clear
    }
    //When it's cleared, wait for it to be set
v2: 
    asm {
        mov dx, 0x03da
        in al, dx
        test al, 0x08
        jz v2           //loop back till vert. retrace bit is newly set

        sti
    }
}

void VGA::updateVRAM(void) {
    waitVRetrace();

    _fmemcpy(VRAM, offscreen, 64000u);
}
   

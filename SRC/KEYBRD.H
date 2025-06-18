#ifndef KEYBOARD_H
#define KEYBOARD_H

#define R_ARROW     0x4D
#define L_ARROW     0x4B
#define U_ARROW     0x48
#define D_ARROW     0x50
#define ESC         0x01

void kbInit(void);

void kbExit(void);

unsigned char kbHit(void);

#endif


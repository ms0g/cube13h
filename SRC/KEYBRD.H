#ifndef KEYBOARD_H
#define KEYBOARD_H

#define R_ARROW     0x4D
#define L_ARROW     0x4B
#define ESC         0x01

void kbInit(void);

void kbExit(void);

unsigned char kbHit(void);

#endif


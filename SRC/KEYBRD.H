#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef enum {
    R_ARROW = 0x4D,
    L_ARROW = 0x4B,
    U_ARROW = 0x48,
    D_ARROW = 0x50,
    ESC = 0x01
} KeyCode;

void kbInit(void);

void kbExit(void);

int kbHit(KeyCode key);

#endif


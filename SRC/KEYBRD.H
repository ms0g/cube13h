#ifndef KEYBOARD_H
#define KEYBOARD_H

#define R_ARROW     0x4D
#define L_ARROW     0x4B
#define ESC         0x01

#ifdef __cplusplus
extern "C" {
#endif
void kbInit(void);

void kbExit(void);

unsigned char kbHit(void);
#ifdef __cplusplus
}
#endif

#endif


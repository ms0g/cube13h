#ifndef TIMER_H
#define TIMER_H

#include <_defs.h>

#define TICKS_PER_SECOND 18.2

void _Cdecl _tmrInit(void);

void _Cdecl _tmrExit(void);

unsigned int _Cdecl _getTick(void);

#endif
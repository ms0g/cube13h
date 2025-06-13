#ifndef TIMER_H
#define TIMER_H

#include <_defs.h>

#define TICKS_PER_SECOND 18.2

void _Cdecl _initTimer(void);

void _Cdecl _exitTimer(void);

unsigned int _Cdecl _getTick(void);

#endif
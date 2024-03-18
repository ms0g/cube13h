#ifndef TIMER_H
#define TIMER_H

#define TICKS_PER_SECOND 18.2

void initTimer(void);

void exitTimer(void);

unsigned int getTick(void);

#endif
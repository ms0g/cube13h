#include "TIMER.H"

#define TMR_IRQ 0x1c

static void interrupt (*old_timer)(...);

static unsigned int tick = 0;

static void interrupt tmr_irq_handler(...) {
    tick += 1;
}

void initTimer(void) {
    asm {
        push bx
        push es
        mov  bx, TMR_IRQ * 4                             //calculates the offset within the interrupt vector table for IRQ 1c (timer interrupt)
        xor  ax, ax
        mov  es, ax                                      //set up the segment register es to point to the beginning of the interrupt vector table.
        cli
        mov  ax, es:[bx]                                 //loads the old interrupt handler address for IRQ 1c
        mov  word ptr old_timer, ax                      //stores the low word (offset) of the old interrupt handler in the variable old_timer.
        mov  ax, es:[bx + 2]                             //loads the segment of the old interrupt handler into the ax register.
        mov  word ptr old_timer[2], ax                   //stores the high word (segment) of the old interrupt handler in the variable old_timer.
        mov  word ptr es:[bx], offset tmr_irq_handler    //replaces the old interrupt handler address with the address of tmr_irq_handler.
        mov  es:[bx + 2], cs                             //replaces the old segment of the interrupt handler with the code segment (cs) of the current code.
        sti
        pop  es
        pop  bx
    }
}

void exitTimer(void) {
    asm { 
        push bx
        push es
        mov  bx, TMR_IRQ * 4
        xor  ax, ax
        mov  es, ax
        cli
        mov  ax, word ptr old_timer
        mov  es:[bx], ax
        mov  ax, word ptr old_timer[2]
        mov  es:[bx + 2], ax
        sti
        pop  es
        pop  bx
    }
}

unsigned int getTick(void) {
    return tick;
}



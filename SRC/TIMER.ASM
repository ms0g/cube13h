.model small
TMR_IRQ equ 1ch
.data
tick dw 0
oldseg dw 0 ;Old Interrupt Vector Segment
oldoff dw 0 ;Old Interrupt Vector Offset
.code
public __initTimer
public __exitTimer
public __getTick
; -------------------------------------------------------------
; void interrupt __tmr_irq_handler (...);                     ;
; -------------------------------------------------------------
__tmr_irq_handler proc far
    cli
    inc tick
    sti
    iret
__tmr_irq_handler endp
; -------------------------------------------------------------
; void _initTimer(void)                                       ;
; -------------------------------------------------------------
__initTimer proc
    ; https://wiki.osdev.org/Interrupt_Vector_Table
    ;   +-----------+-----------+
    ;   |  Segment  |  Offset   |
    ;   +-----------+-----------+
    ;   4           2           0 
    push bx
    push es
    mov bx, TMR_IRQ * 4                                 ;calculates the offset within the interrupt vector table for IRQ 1ch (timer interrupt)
    xor ax, ax
    mov es, ax                                          ;set up the segment register es to point to the beginning of the interrupt vector table.
    cli
    mov ax, es:[bx]                                     ;loads the old interrupt handler address for IRQ 1ch
    mov word ptr [oldoff], ax                           ;stores the low word (offset) of the old interrupt handler in the variable old_irq.
    mov ax, es:[bx + 2]                                 ;loads the segment of the old interrupt handler into the ax register.
    mov word ptr [oldseg], ax                           ;stores the high word (segment) of the old interrupt handler in the variable old_irq.
    mov word ptr es:[bx], offset [__tmr_irq_handler]    ;replaces the old interrupt handler address with the address of kbc_irq_handler.
    mov es:[bx + 2], cs                                 ;replaces the old segment of the interrupt handler with the code segment (cs) of the current code.
    sti
    pop es
    pop bx
    ret
__initTimer endp
; -------------------------------------------------------------
; void _exitTimer(void)                                       ;
; -------------------------------------------------------------
__exitTimer proc
    push bx
    push es
    mov bx, TMR_IRQ * 4
    xor ax, ax
    mov es, ax
    cli
    mov ax, word ptr [oldoff]
    mov es:[bx], ax
    mov ax, word ptr [oldseg]
    mov es:[bx + 2], ax
    sti
    pop es
    pop bx
    ret
__exitTimer endp
; -------------------------------------------------------------
; unsigned int _getTick(void)                                 ;
; -------------------------------------------------------------
__getTick proc
    mov ax, tick
    ret
__getTick endp
end

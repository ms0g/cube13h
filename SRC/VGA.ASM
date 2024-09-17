.model small
.data
.code
public __waitvretrace
public __initMode
public __putpixel
; -------------------------------------------------------------
; void _Cdecl _waitvretrace(void)                             ;
; -------------------------------------------------------------
__waitvretrace proc
    cli
    ;If vert. retrace bit is set, wait for it to clear
v1: 
    mov dx, 03dah  ;dx <- VGA status register
    in al, dx      ;al <- status byte
    test al, 08h   ;is bit 3 (vertical retrace bit) set
    jnz v1         ;If so, wait for it to clear
    
    ;When it's cleared, wait for it to be set
v2: 
    mov dx, 03dah
    in al, dx
    test al, 08h
    jz v2           ;loop back till vert. retrace bit is newly set
    sti
    ret
__waitvretrace endp
; -------------------------------------------------------------
; void _Cdecl _initMode(int mode)                        ;
; -------------------------------------------------------------
__initMode proc
    push bp       
    mov bp, sp
    mov al, byte ptr [bp+4]
    xor ah, ah         
    int 10h
    mov sp, bp
    pop bp
    ret      
__initMode endp
; -------------------------------------------------------------
; void _Cdecl _putpixel(int x, int y, char color)             ;
; -------------------------------------------------------------
__putpixel proc
    push bp      
    mov bp, sp
    push 0A000h
    pop es
    push di
    xor di, di
    mov di, word ptr [bp+4] ;x
    mov cx, word ptr [bp+6] ;y
    mov ax, cx
    shl ax, 08h             ;y<<8
    add di, ax              ;x+(y<<8)
    mov ax, cx
    shl ax, 06h             ;y<<6
    add di, ax              ;x+(y<<8)+(y<<6)
    xor ax, ax
    mov al, byte ptr [bp+8] ;color
    stosb
    pop di
    mov sp, bp
    pop bp
    ret     
__putpixel endp
end
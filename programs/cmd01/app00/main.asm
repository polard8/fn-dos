

;app00.com
; 0x3000:0
[BITS 16]
[ORG 0000h]

OUR_SEGMENT  EQU  0x3000 

STACK_SEGMENT  EQU  0x3000 
STACK_OFFSET   EQU  0xFFF0

AppMain:
    jmp real_start

real_start:

    cli
    mov  	ax, OUR_SEGMENT  
    mov  	ds, ax
    mov  	ax, 0xB800
    mov  	es, ax
    mov  	ax, STACK_SEGMENT
    mov  	ss, ax
    mov  	sp, STACK_OFFSET
    sti

    mov si, msg_hello
    call DisplayMessage

    mov bx, 0
    mov al, 'X'
    mov ah, 0x17
    mov byte [es:bx], al 
    inc bx
    mov byte [es:bx], ah

    mov bx, 2
    mov al, 'X'
    mov ah, 0x87
    mov byte [es:bx], al 
    inc bx
    mov byte [es:bx], ah


    mov bx, 4
    mov al, 'X'
    mov ah, 0x67
    mov byte [es:bx], al 
    inc bx
    mov byte [es:bx], ah


    ;int 0x18

    ;retf

    jmp $

msg_hello db 'Hello from app', 0x0D, 0x0A, 0x00

; -----------------------------------------
; DisplayMessage:
; Display ASCIIZ string at "ds:si" via BIOS.
; Standadr print string routine.
DisplayMessage:
    lodsb                  ; Load next character.
    or al, al              ; Test for NUL character.
    jz .DONE
    mov ah, 0x0E           ; BIOS teletype. 
    mov bx, 0x0007         ; Página e atributo.  
    int 0x10               ; Invoke BIOS.
    jmp  DisplayMessage
.DONE:
    RET


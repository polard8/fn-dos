
; 0x2000:0
; Loads a program in 0x2000:0x8000 using the kernel
; It has an array of jmps and act as an intarface with the kernel.
; The program calls the cmd and the command calls the kernel.

bits 16
[ORG 0x0000]

all:
    db "Signature", 0
    times (512*4) db 0
    ret 

    


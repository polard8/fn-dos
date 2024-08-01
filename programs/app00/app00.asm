
bits 16
[ORG 0x8000]

all:
    db "Signature", 0
    times (512*4) db 0
    ret 

    


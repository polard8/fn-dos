; s1lib.inc
; Functions for stage1.asm

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


; -----------------------------------------
; ClusterLBA:
; Convert FAT cluster into LBA addressing scheme
; LBA = (cluster - 2) * sectors per cluster
ClusterLBA:
    sub ax, 0x0002                      ; zero base cluster number
    xor cx, cx
    mov cl, BYTE [SectorsPerCluster]    ; convert byte to word
    mul cx
    add ax, WORD [datasector]           ; base data sector
    RET

; -----------------------------------------
; ReadSectors:
; Reads "cx" sectors from disk starting at "ax" 
; into memory location "es:bx"

ReadSectors:

    mov WORD [DAPBuffer]   ,bx
    mov WORD [DAPBuffer+2] ,es
    mov WORD [DAPStart]    ,ax
; Tentativas.
.MAIN:
    mov di, 0x0005  
.SECTORLOOP:

    push  ax
    push  bx
    push  cx

    push si
    mov ah, 0x42
    mov dl, 0x80
    mov si, DAPSizeOfPacket
    int 0x13
    pop si
 
    jnc  .__SUCCESS    ; Test for read error.
    xor  ax, ax        ; BIOS reset disk.
    int  0x13          ; Invoke BIOS.
    
    dec  di            ; Decrement error counter.
    
    pop  cx
    pop  bx
    pop  ax

; Attempt to read again
    jnz  .SECTORLOOP    
;.fail:
    int  0x18
.__SUCCESS:

    ; Importante: 
    ; Mensagem de progresso.    
    ;mov  si, msgProgress
    ;call  DisplayMessage
    
    pop  cx
    pop  bx
    pop  ax

    ; Queue next buffer.
    add bx, WORD [BytesPerSector] 
    cmp bx, 0x0000
    jne .NextSector

    ; Switching the segment.
    push ax
    mov  ax, es
    add  ax, 0x1000
    mov  es, ax
    pop  ax

.NextSector:

    inc  ax                     ; Queue next sector.
    mov WORD [DAPBuffer], bx
    mov WORD [DAPStart], ax
    loop  .MAIN                 ; Read next sector.
    RET

; -----------------------------------------
; XXX
FAILURE:
    ; int 0x18  
    mov si, msgFailure
    call DisplayMessage
    mov ah, 0x00
    int 0x16        ; Await keypress
    int 0x19        ; Warm boot computer



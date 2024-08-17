// ps2.h
// Created by Fred Nora.

#ifndef ____PS2_H
#define ____PS2_H  1

/*
 Wikipedia
 O conector PS/2 � um conector mini-DIN de 6 pinos usado para conectar alguns 
 teclados e mouses a um sistema de computador compat�vel com PC. 
 Seu nome vem da s�rie de computadores pessoais IBM Personal System/2, 
 com o qual ele foi introduzido em 1987. O conector de mouse PS/2 geralmente 
 substitui antigos conectores de "mouses seriais" DE-9 RS-232, 
 enquanto o conector de teclado PS/2 substituiu o conector DIN mais largo de 5 pinos/180� 
 usado no desenho do IBM PC/AT. Os desenhos PS/2 nas interfaces de teclados e 
 mouses s�o eletricamente similares e empregam o mesmo protocolo de comunica��o. 
 Entretanto, a porta de teclado ou mouse de um determinado sistema pode n�o ser 
 intercambi�vel uma vez que os dois dispositivos usam um conjunto de comandos diferentes.
 
A comunica��o � serial, s�ncrona e bidirecional.[1] 
O dispositivo conectado gera o sinal de rel�gio. O hospedeiro controla a comunica��o usando a 
linha de rel�gio. Quando o hospedeiro puxa o rel�gio para baixo, a comunica��o do dispositivo � inibida.
*/

//
// Defini��es.
//

#define  PS2_PORT    0x60
#define  PS2_CTRL    0x64
#define  PS2_ACK     0xFA 
//...

// ================================

struct ps2_d
{
    int used;
    int magic;
    
    // #hackhack
    // Use pooling or not.
    // TRUE, FALSE
    // :: 
    // Maybe something is wrong with the 
    // USB/PS2 emulation microcode in my real machine.
    // Maybe the 'interrupts' is not working in the 
    // 32 bit protected mode. 
    // Maybe we can use 'pooling' to aboid this issue. 
    // Just like in Temple OS.
    // ps: Some other OSs are facing the same problem.
    int pooling;

    //flags: TRUE or FALSE,
    int keyboard_initialized;
    int mouse_initialized;
    
    // #todo
    // We can create these two structures.
    // See: ps2kbd.h and ps2mouse.h
    // struct ps2_keyboard_d *ps2_keyboard;
    // struct ps2_mouse_d    *ps2_mouse;
    
    // ...
};
// see: i8042.c
// #important:
// use ps2_ioctl to setup this structure.
// The app needs to open the file /PS2, something like that.
extern struct ps2_d  PS2;
// ================================


//
// == prototypes ===========================================
//

 
void ps2 (void);
void early_ps2_init (void);

int PS2_initialize(void);
int PS2_early_initialization(void);

// See:
// i8042.c
int ps2_ioctl ( int fd, unsigned long request, unsigned long arg );

#endif  

//
// End
//


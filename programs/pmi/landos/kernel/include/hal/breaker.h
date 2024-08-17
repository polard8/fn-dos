// breaker.h
// hw interrupt breaker.

#ifndef ____BREAKER_H
#define ____BREAKER_H    1

// See:
// x86 - entry/head/hw.asm
// ...

// timer interrupt
// kdrivers/timer.c
extern int __breaker_timer_initialized;

// ps2 keyboard
// x/i8042/ps2kbd.c
extern int __breaker_ps2keyboard_initialized;

// Serial ports.
// See: kdrivers/serial.c
extern int __breaker_com1_initialized;
extern int __breaker_com2_initialized;
extern int __breaker_com3_initialized;
extern int __breaker_com4_initialized;

// real time clock
// kdrivers/rtc.c
extern int __breaker_rtc_initialized;

// ps2 mouse
// x/i8042/ps2mouse.c
extern int __breaker_ps2mouse_initialized;

// ata
// kdrivers/ide/ata.c
extern int __breaker_ata1_initialized;
extern int __breaker_ata2_initialized;

//...

#endif    



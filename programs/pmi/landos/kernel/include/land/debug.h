// debug.h
// Kernel debug
// Created by Fred Nora.

#ifndef __DEBUG_H
#define __DEBUG_H   1

int debug (void);
int debug_check_inicialization (void);
int debug_check_drivers (void);
void debug_breakpoint (void);

//retorna um checksum dado um buffer e um tamanho.
unsigned long debug_compute_checksum( unsigned char *Buffer, unsigned long Lenght);

//escreve na porta seria.
void debug_print (char *data);
void PROGRESS (char *string);

#endif  

//
// End
//


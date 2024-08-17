/*
 * File: pic.c
 *
 *    Controlador PIC.
 *    Arquivo principal do m�dulo interno do kernel de 32bit. 
 *    PIC - Programmable Interrupt Controller
 *
 * Vers�o 1.0, 2016.
 */
 

#include <kernel.h>
  

//
//  PIC - Programmable Interrupt Controller register addresses.
//
 
//Ningu�m al�m do driver precisa dessas constantes. 
// master PIC.
#define PIC1_PORT0 0x20  
#define PIC1_PORT1 0x21
// slave PIC.
#define PIC2_PORT0 0x0A0 
#define PIC2_PORT1 0x0A1
 
 
//
// Vari�veis internas.
// 

int picStatus=0;
int picError=0;
//... 

struct pic_d  *Pic;

 
/* 
int picInit();
int picInit()
{
    picStatus;
    picError;

    return (int) 0;	
} 
*/
 
//
// End.
//


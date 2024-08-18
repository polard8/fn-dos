/*
 * File: bli.h
 * Boot Loader Internal. Para rotinas globais come�adas com BlXXXX.
 * Acessiveis � todos os m�dulos do boot loader.
 */


#ifndef __BLI_H
#define __BLI_H    1

//
// Procedure =============================
//

unsigned long 
bl_procedure ( 
    unsigned long window,
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

// Finalizations support.
void BlAbort();

#endif   

//
// End.
//


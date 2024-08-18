/*
 * File: heap.h
 *
 * Descri��o:
 *     O prop�sito desse header � dar suporte ao gerenciamento de
 * do heap que ser� usado para a aloca��o de mem�ria para um programa
 * em user mode. 
 *     Um suporte oferecido pela biblioteca libC99.
 *     Obs: O kernel poder� usar tanto o heap do processo quanto o heap 
 * do desktop ao qual o processo pertence.
 * 
 * History:
 *     2016 - Created by Fred Nora.
 */

#ifndef __HEAP_H
#define __HEAP_H  1



//Contagem de heap.
#define HEAP_COUNT_MAX  256 

// see: stdlib.c
extern unsigned long HEAP_START; 
extern unsigned long HEAP_END;
extern unsigned long HEAP_SIZE;
//@todo: padronizar 
extern unsigned long heapCount;            //Conta os heaps da stdlib.
extern unsigned long heap_start;    //Start.
extern unsigned long heap_end;      //End.
extern unsigned long g_heap_pointer;       //Pointer.
extern unsigned long g_available_heap;     //Available. 


// see: stdlib.c
// Heap pointer:
//     Isso deve apontar para o heap buffer atual. Quando acabar o heap atual
// deve-se chamar o kernel para criar mais heap dentro da working set do processo.  
extern void *Heap;


//
// *** HEAP ***
//

#define HEAP_BUFFER_SIZE  (32*1024)  // 32KB, provis�rio.

static unsigned char HeapBuffer[HEAP_BUFFER_SIZE]; 

/*
 * heap_d:
 *     Estrutura para heap.
 *     Cada processo tem seu heap.
 *     Cada heap tem uma lista encadeada de blocos.  
 */

struct heap_d 
{
    int Id;
    
    int Used;
    int Magic;

    unsigned long HeapStart;
    unsigned long HeapEnd;

    unsigned long HeapPointer;
    unsigned long AvailableHeap; 

    //lista linkada de blocos. 
    //struct mmblock_d *nextblock; 
};
// stdlib.c
extern struct heap_d *libcHeap;
//...

// stdlib.c
//Heap list.
extern unsigned long heapList[HEAP_COUNT_MAX];


//
// == prototypes ===============================================
//


// Alloc and Free.
unsigned long heapAllocateMemory ( unsigned long size );
unsigned long FreeHeap( unsigned long size );

void heapSetLibcHeap( unsigned long HeapStart, unsigned long HeapSize);

int heapInit(void);

#endif    

//
// End
//


// heap.h
// 2016 - Created by Fred Nora.

/*
 *    Its used to manage the heap support.
 *    The heap is used to allocate memory for malloc.
 *    + Manage the pointer of the current heap.
 */

#ifndef __MM_HEAP_H
#define __MM_HEAP_H    1

/*
 * Kernel Heap support.
 */

extern unsigned long heapCount;            // Conta os heaps do sistema.

extern unsigned long kernel_heap_start;    // Start.
extern unsigned long kernel_heap_end;      // End.

extern unsigned long g_heap_pointer;       // Pointer.
extern unsigned long g_available_heap;     // Available.

/*
 * heap_d:
 *     Estrutura para heap.
 *     Cada processo tem seu heap.
 *     Cada heap tem uma lista encadeada de blocos.  
 */  

struct heap_d 
{
    object_type_t objectType;
    object_class_t objectClass;

    int id;

    int used;
    int magic;


    unsigned long HeapStart;  
    unsigned long HeapEnd;
    unsigned long HeapPointer; 
    unsigned long AvailableHeap; 



    // Ponteiro para a lista de blocos de um heap.
    // Lista encadeada de blocos que formam o heap.
    // A estrutura para um bloco �: mmblock_d e est� definida em mm.h
    //
    // Obs: 
	// Foram alocados v�rios blocos de mem�ria dentro de um heap. Portanto 
	// podemos colocar os ponteiros para as estruturas desses blocos dentro 
	// de uma lista encadeada e o ponteiro para a lista colocaremos aqui.
	//
	// Cada bloco desse come�a com um 'header', definido na estrutura de bloco.
	struct mmblock_d *mmblockListHead;  
	
	//se esses arrays ocuparem muito espa�o, ent�o faremos com listas encadeads.
	//struct mmblock_d *mmblockUsedBlocks;  
	//struct mmblock_d *mmblockFreeBlocks;  	
	//struct mmblock_d *mmblockAllBlocks;  
	
	
	//Test:
	// Endere�os para os blocos de um heap.
	// Uma lista de blocos que est�o sendo usados
	// Uma lista de blocos livres e j� alocados.
	// Uma lista com todos os blocos.
	//unsigned long usedBlocks[32];
	//unsigned long freeBlocks[32];
	//unsigned long Blocks[64];		
	
	
	//Um heap pertence � um desktop.
    struct desktop_d *desktop;
	
	//Um heap pertence � um processo.
    struct process_d *process;
	
	//Um heap pode pertencer � um thread.
    struct thread_d *thread;
	
	//
	// Compartilhamento de heap:
	// ========================
	//   + As threads de um mesmo processo podem compartilhar o mesmo heap
	//     pois est�o na mesma �rea de mem�ria.
	//   + @todo: O desafio � fazer os processes que est�o no mesmo desktop
	//            compartilharem o mesmo heap, porque eles deveriam estar
	//            na mesma �rea de mem�ria para isso. 
	//
	
	
    //
	// Podemos criar aqui flags de porte��o.
	//
	//int read;  //Apenas leitura.
	//int write;
	
	
	//...

	//Sequenciando heaps sei l� pra qu�. 
	//#bugbug: N�o queremos sequenciar os heaps.
	//cada processo tem seu heap.
	//struct heap_d *next;
};


#define HEAP_COUNT_MAX  8

// see: memory.c
extern unsigned long heapList[HEAP_COUNT_MAX];  

//
// Prototypes =======================================================
//

struct heap_d *memory_create_new_head ( 
    unsigned long start_va, 
    unsigned long size );

// Destr�i um heap se as flags permitirem.
void memory_destroy_heap (struct heap_d *heap );

// Pega o endere�o do in�cio do header da pr�xima aloca��o.
unsigned long get_process_heap_pointer (int pid);

//
// Alloc and Free.
//

unsigned long heapAllocateMemory (unsigned long size);
void FreeHeap (void *ptr);

int init_heap (void);

#endif  


//
// End
//


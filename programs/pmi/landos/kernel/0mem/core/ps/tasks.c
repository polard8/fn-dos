// File: ps/tasks.c
// #todo
// Devemos reaproveitar esse arquivo,
// mas com outro nome e outro proposito.


#include <kernel.h>



//Status do mecanismo de task switch. 
unsigned long task_switch_status=0;
 
//Status do scheduler.	
unsigned long g_scheduler_status=0;
 
//usada no salvamento de contexto de tarefa.
unsigned long old=0; //importante!  

//new task variables.
unsigned long start_new_task_status=0;
int start_new_task_id=0;
unsigned long start_new_task_address=0;


/*
 * quantum - quanto tempo fica rodando uma tarefa ate ser interrompida.
 */
unsigned long quantum=0;
unsigned long current_quantum=0;
unsigned long next_quantum=0;


/*
 *  O que segue s�o as vari�veis usadas com menor frequ�ncia.
 */
int task_color=0;
unsigned long forkid=0;
unsigned long newtask_EIP=0;    
unsigned long next_address=0;

//
//outras
//
	
unsigned long task_waiting=0;   //?espera
unsigned long preempted_task=0;
unsigned long running_tasks=0;   //numero de tarefas rodando. //esta em estrutura agora.
unsigned long task_count=0;      //contador de tarefas criadas.




// =======================

void task0 (void)
{
    //printf ("Thread started\n"); 
    while(1){ asm("hlt"); }
}

void task1 (void)
{
    //printf("Thread started\n"); 
    while(1){ asm("hlt"); }
}


//
// End.
//


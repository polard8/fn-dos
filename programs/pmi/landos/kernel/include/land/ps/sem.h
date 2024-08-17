/*
 * File: semaphore.h
 *
 * Descri��o:
 *     Header do m�dulo semaphore do microkernel.
 *     M0.
 *     Rotinas de Down e Up.
 *     Os processos entram e saem da sua regi�o cr�tica
 *     utilizando as rotinas de Down e Up. 
 *
 * 2015 - Created by Fred Nora.
 */


#ifndef __SEM_H
#define __SEM_H    1


#define SEMAPHORE_MAX 256    //N�mero m�ximo de sem�foros por enquanto.
#define VERMELHO 0
#define VERDE    1
#define BASE_COUNT 0
#define MAX_COUNT  8


/*
 * estruturas.
 */
 

/*
 * semaphore_d:
 *     Estrutura para cria��o de um sem�foro.        
 *
 *     Pode-se criar v�rios sem�foros. Cada sem�foro � usado para
 * controlar o fluxo em um determinado recurso.
 * 
 */ 
typedef struct semaphore_d semaphore_descriptor_t;
struct semaphore_d 
{
	object_type_t objectType;
	object_class_t objectClass;
    
    //call back. @todo: Create.
	//unsigned long callback; //d
	
	//Identificadores do sem�foro.   	
	int id;         //c
	int used;       //b
	int magic;      //a
	int taskId;    	//g, A tarefa que esta usando o dispositivo. 
	
	//Estado do sem�foro. (verde, vermelho)
	int color;          //G
	int status;         //F Flag.
	unsigned int count; //>=0   //E
   
    //...
	
    //@todo: corrigir o nome dessa estrututras.
	//struct d_wait_queue *sema_wait;   //ext1
    //struct wait_queue_d *sema_wait;   //ext1 	
	//...	
};

//semaphore_descriptor_t *current_semaphore; 
//unsigned long semaphoreList[32+1];

// ===========================================

/*
 * Semaphore support.
 */

/*
 * Down:
 *     Quando um processo vai entrar na sua regi�o cr�tica
 *     ele executa um Down.
 *     Se o sem�foro estiver com zero, significa que
 *     o recurso j� est� bloqueado por outro processo 
 *     ent�o o processo que est� tentando utilizar o recurso
 *     deve esperar, mudando o estado para waiting.
 */  

int Down (struct semaphore_d *s);

/*
 * Up:
 *     Quando um processo sai da sua regi�o cr�tica
 *     ele d� um Up no sem�foro, mudando seu valor pra 1.
 *     Isso libera o recurso pra outro processo.
 */ 

int Up (struct semaphore_d *s);


/*
 * Semaphore support.
 */

int init_semaphore(struct semaphore_d *s, unsigned int count); 

void semaphore_down(struct semaphore_d *s);
void semaphore_up(struct semaphore_d *s); 

void *create_semaphore (void); 
void delete_semaphore(struct semaphore_d *s);

void open_semaphore(struct semaphore_d *s);
void close_semaphore(struct semaphore_d *s);


#endif    


//
// End.
//




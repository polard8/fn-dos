/*
 * File: queue.h
 *
 * Descri��o:
 *     Header para queue.
 *     No fim da fila a prioridade � maior.
 *    
 * History:
 *     2015 - Created by Fred Nora.
 *     2018 - Revision.
 */


#ifndef __QUEUE_H
#define __QUEUE_H    1


// Ordena��o das listas de filas.

#define QUEUE_NULL     0
#define QUEUE_STANDBY  1
#define QUEUE_RUNNING  2
#define QUEUE_READY    3
#define QUEUE_WAITING  4  //Fila das threads que est�o esperando.
#define QUEUE_BLOCKED  5
#define QUEUE_ZOMBIE   6
#define QUEUE_DEAD     7
#define QUEUE_INITIALIZED   8
#define QUEUE_SYSCOOP       9  // Sistema, coopera��o.   
#define QUEUE_USERCOOP     10  // Usu�rio, coopera��o.   
#define QUEUE_SYSCONC      11  // Sistema, concorr�ncia. 
#define QUEUE_USERCONC     12  // Usu�rio, concorrencia.  
#define QUEUE_REALTIME     13 
#define QUEUE_DEFAULT      14
//...

// ??
// N�veis de prioridade.
#define QUEUE_LEVEL_MIN 15
#define QUEUE_LEVEL_MED 16
#define QUEUE_LEVEL_MAX 17


#define MAX_QUEUES 3


// Essa � a organiza��o padr�o de uma lista de ponteiros de lista encadeada.
// 0 = DRIVERS
// 1 = SERVERS
// 2 = USER APPS
// 3 = NULL 
extern unsigned long QUEUES[3];
 
 
/*
 **********************************************************
 * queue_d:
 *     Estrutura para organizar v�rias listas de ponteiros de lista encadeada.
 */

struct queue_d
{
	// #importante
	// MAX_QUEUES � o n�mero m�ximo de filas que pode haver na lista.
	// A lista cont�m o potneiro head de uma lista encadeada.
	//
   	
	//Movimento 1, initialized --> standby. 
    int standbyHead; 
    int standbyTail;
    int standbyMax;
    unsigned long standbyList[MAX_QUEUES+1];    


	//Movimento 2, standby --> running.
	//Movimento 4, ready   --> running.    
	//*** deve estar em sintonia com a fila do dispatcher.	
    int runningHead; 
    int runningTail;
    int runningMax;
    unsigned long runningList[MAX_QUEUES+1];    
	
	//Movimento 3, running --> ready.
	//Movimento 6, waiting --> ready.
	//Movimento 8, blocked --> ready.	
    int readyHead; 
    int readyTail;
    int readyMax;
    unsigned long readyList[MAX_QUEUES+1];     
	 
	 
	//Movimento 5, ready --> waiting.
    //Esperando para retomar a execu��o.	
    int waitingHead;
    int waitingTail;
    int waitingMax;
    unsigned long waitingList[MAX_QUEUES+1];
	  
	  
	//Movimento 7, running --> blocked.	
    int blockedHead;
    int blockedTail;
    int blockedMax;
    unsigned long blockedList[MAX_QUEUES+1];
	  
	//Movimento 9, running --> zombie.	
    int zombieHead;
    int zombieTail;
    int zombieMax;
    unsigned long zombieList[MAX_QUEUES+1];
	  
	  
	//Movimento 10, zombie --> dead.
    int deadHead;
    int deadTail;
    int deadMax;
    unsigned long deadList[MAX_QUEUES+1];    

	//Movimento 11, zombie --> initalized.
    //Movimento 0,       x --> initalized. (created)	
    int initializedHead;
    int initializedTail;
    int initializedMax;
    unsigned long initializedList[MAX_QUEUES+1];
	
	
	/*
     * RACE: 
	 *    Filas do loop do sistema. 
	 *    Coopera��o e Concorr�ncia.
     */ 
	  
	  
    //Coopera��o, sistema.
    int syscoopHead; 
    int syscoopTail;
    int syscoopMax;
    unsigned long syscoopList[MAX_QUEUES+1];   

	//Concorr�ncia, sistema.
    int sysconcHead; 
    int sysconcTail;
    int sysconcMax;
    unsigned long sysconcList[MAX_QUEUES+1];

	/*
     * RACE: Filas do loop do usu�rio. Coopera��o e Concorr�ncia.
     */ 

	
	//Coopera��o, usu�rio.
    int usercoopHead; 
    int usercoopTail;
    int usercoopMax;
    unsigned long usercoopList[MAX_QUEUES+1];  	

	//Concorr�ncia, usu�rio.
    int userconcHead; 
    int userconcTail;
    int userconcMax;
    unsigned long userconcList[MAX_QUEUES+1];   

	
    /*
     * PITSTOP: Outras filas.
     */ 

   //realtime tasks queue. 
    int realtimeHead; 
    int realtimeTail;
    int realtimeMax;
    unsigned long realtimeList[MAX_QUEUES+1];  //real time rr. 
	
	
    //default queue
    int defaultHead;
    int defaultTail;
    int defaultMax;
    unsigned long defaultList[MAX_QUEUES+1]; 
	
	
	// #test
    // Listas para filas de threads que se encaixam emdeterminadas faixas de prioridade.
	
	
	//M�nimo = 'level <= PRIORITY_LOW'
    int minHead; 
    int minTail;
    int minMax;
    unsigned long minList[MAX_QUEUES+1];
	
	//M�dio == 'PRIORITY_LOW > level <= PRIORITY_NORMAL'
    int medHead; 
    int medTail;
    int medMax;
    unsigned long medList[MAX_QUEUES+1];
    
	//M�ximo = ' level > PRIORITY_NORMAL '
	int maxHead; 
    int maxTail;
    int maxMax;
    unsigned long maxList[MAX_QUEUES+1];
	
};
extern struct queue_d *queue;


/*
 * wait_queue_d:
 *     Lista encadeada que pode ser usada para threads que est�o esperando 
 * por algum evento.
 */

struct wait_queue_d
{
	int size;
	struct thread_d *head;
	struct thread_d *tail;
};
extern struct wait_queue_d *wait_queue;



//
// ======== Prototypes ========
//

int init_queue(struct queue_d *q);

//queue_insert_head: Coloca um dado no fim da fila. (LIFO)
int 
queue_insert_head ( 
    struct queue_d *q, 
    unsigned long data, 
     int type );

int 
queue_insert_data( 
    struct queue_d *q, 
    unsigned long data, 
    int type );

struct thread_d *queue_get_data ( struct queue_d *q, int type );
  
void show_queue_information(struct queue_d *q);
void ScanReadyQueue(struct queue_d *q);

void 
feed_ready_queue( 
    struct queue_d *q, 
    int type );


#endif    


//
// End.
//


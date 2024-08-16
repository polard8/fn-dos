// object.h
// 2016 - Created by Fred Nora.
 
#ifndef __OBJECT_H
#define __OBJECT_H    1


/*
 * struct object_d:
 *     Object controle ...
 *     Estrutura para controle de objetos.
 *     Isso deve ficar no in�cio de cada estrutura 
 *     para controlar a utiliza��o do objeto por parte 
 * dos processos e threads.
 * 
 */

struct object_d 
{
    // haha !!
    // Objeto do tipo objeto.
    object_type_t objectType;
    object_class_t objectClass;

    int id; 
 
    int used;  
    int magic; 

    char *path;             // '/root/user/(name)'
    char __objectname[64];    // HOSTNAME_BUFFER_SIZE
    size_t objectName_len;    // len 
  

    //Lista de processos que possuem o objeto.
    int pidList[32];
    int pidCount;
    int currentPID;
   
 
    //endere�os
    unsigned long obj_address;
    unsigned long obj_procedure;
   
    //
	// Status do objeto.
	//   
	 
    int token; //algum processo 'pegou' o objeto e esta usando.

    int task_id; //id da tarefa que pegou o processo.

    
	//int signaled;
	//struct process_d *waitListHead;
	
	//channel	
    //process
	//thread
	//window
	
	//continua...
};

// ??
// Repensar isso.
// #bugbug: Muito espa�o. (#todo: deprecated this)
extern struct object_d  objects_km[256+1];  //objetos em kernel mode.
extern struct object_d  objects_um[256+1];  //objetos em user mode. 
extern struct object_d  objects_gui[256+1]; //objetos gr�ficos. 

// Se o gerenciador de recursos foi inicializado.
extern int g_object_manager_status;

//id do objeto atual
extern int g_current_object;

//id da lista ao qual o objeto atual pertence.
// object_km, object_um, object_gui. 
extern int g_current_list;

//
// prototypes ==========
//
 
int init_object_manager (void);

#endif   

//
// End
//


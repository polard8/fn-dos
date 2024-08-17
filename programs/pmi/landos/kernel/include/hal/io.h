/*
 * File: io.h
 *
 * Descri��o:
 *     Arquivo principal do I/O Manager.
 *     Todo gerenciamento de dispositivos,
 *     toda concess�o de acesso passar� por 
 *     esse gerenciador, que faz parte da
 *     camada de abstra��o de hardware oferecidad pelo
 *     kernel base.
 *
 * History:
 *     2016 - Created by Fred Nora.
 */


#ifndef ____IO_H
#define ____IO_H


// Estrutura para gerenciamento de buffer de i/o. 

struct ioBuffer_d
{
    object_type_t objectType;
    object_class_t objectClass;

    struct process_d *OwnerProcess;    // processo dono do buffer.
    unsigned long address;             // Address.
    
    int size;                          // size in number of bytes.
}; 

 // Escalonamento de dispositivo.
// Todo dispositivo tem uma fila de threads esperando 
// para usar o dispositivo.
// Nessas vari�veis colocaremos qual � a thread que 
// est� usando o dispositivo no momento.
// #bugbug essa informa��es deve estar na estrutura de dispositivo.
//
// ## input control 
//

struct ioControl_d
{

    int id;
    int used;
    int magic;

    //identifica��o do dispisitivo
    int did; 

	// Aqui identificaremos qual a thread que est� 
	// usando o dispositivo no momento.

    //identifica��o da thread.
    int tid; 

    // a janela que esta usando o dispositivo.
    int wid;  
};

extern struct ioControl_d *ioControl_keyboard;   //0
extern struct ioControl_d *ioControl_mouse;      //1

extern unsigned long ioControl[32];


//
// Prototypes =========================================================
// 
 
// Handler for services.
int io_ioctl ( int fd, unsigned long request, unsigned long arg );
int ioInit (void);

#endif   

//
// End
//


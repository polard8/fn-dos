/*
 * File: mm\aspace.h 
 * Address Space.
 *     Address Space Manager.
 */

#ifndef __MM_ASPACE_H
#define __MM_ASPACE_H    1

typedef enum {
	aspacetypeShared,
	aspacetypePersonal,
}aspace_type_t;


typedef struct aspace_d aspace_t;
struct aspace_d
{
    //Obs: Essa estrutura � para qualquer regi�o da
	//mem�ria f�sica. A outra estrutura mm_block �
	//apenas para gerenciar �reas de mem�ria alocadas 
	//dentro do heap do kernel.
	
	//Object.
	object_type_t objectType;
	object_class_t objectClass;
	
	int used;
	int magic;

	aspace_type_t type;
	
	char *name;  //Qual � o nome desse Address Apace.
	file *_file;   //Qual arquivo � referente � esse espa�o.
	//metafile??

	unsigned long virtual_address;
	unsigned long physical_address;
	unsigned long size;  //Tamanho em bytes.
	
	//...
	
	
	//
	// @todo: Informa��es sobre os processos que est�o utilizando
	//        essa �rea de mem�ria.
	//
	
	//Lista de processos utilizando esse objeto.
	struct process_d *processListHead;
	//int processCount;
	
	// propriedades da regi�o.
	// permiss�es de leitura e escrita.
	//informa��es sobre todos os arquivos associados com a regi�o.
	
	//
	// Deve-se encadear as regi��es de mem�ria em um �rvore,
	// de forma a facilitar o acesso.
	// Obs: Acho que a estrutura de contas em bancos
    // cumpre esse papel.	
	//
	
	//?? @questionamento: Uma conta poderia pertencer � mais de um banco
	// ou devemos indicar aqui � que banco essa conta pertence.
	//struct bank_d *bank;

	//navega��o.
	struct aspace_d *next;
};
//aspace_t *ASpace;
//...

#endif   


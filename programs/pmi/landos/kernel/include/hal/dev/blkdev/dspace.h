/*
 * File: blkdev\dspace.h 
 * 
 * Disk Space. 
 *    Gerenciamento de espa�o em disco. Isso est� no m�dulo de mem�ria 
 * para servir de interface entre o gerente de mem�ria e o gerente de disco 
 * no suporte a mem�ria virtual. Principalmente swap.
 *      
 * Obs: O lugar natural desse disco seria na classe de dispositivos, certo ?
 *      Mas ficar� aqui, porque tem uma grande real��o com mem�ria ram,
 *      pois s�o desses endere�os de disco que sair�o as p�ginas usadas nas contas
 * de p�ginas.  
 */

#ifndef  __DSPACE_H
#define  __DSPACE_H    1

typedef enum {
    dspacetypeNull,
    dspacetypeShared,
    dspacetypePersonal
}dspace_type_t;

struct dspace_d
{
	//Object.
	object_type_t  objectType;
	object_class_t objectClass;
	
	int used;
	int magic;

	dspace_type_t type;
	
	char *name;  //Qual � o nome desse Disk Apace.
	file *_file;   //Qual arquivo � referente � esse espa�o.
	//metafile??	

	//Endere�o correspondente na mem�ria ram.
	unsigned long virtual_address;
	unsigned long physical_address;
	
	//Tamanho em setores..
	unsigned long size;  	
	unsigned long sector_size;   //Tamanho de um setor dado em bytes
	
	
	//Lista de processos utilizando esse objeto.
	struct process_d *processListHead;
	//int processCount;	
	
	//...
	
	//navega��o.
	struct dspace_d *next;
};
//struct dspace_d *DSpace;
// dspace_t *DSpace;
//...

#endif    

// halmm.h
// 2015 - Created by Fred Nora.
// Created by Fred Nora.

/* 
 *    Header para o driver do placa de mem�ria.
 *    Aqui devem ficar informa��es sobre o hardware 
 *    do cart�o de mem�ria, como modelo, velocidade, etc... 
 *    Obs: 
 *    As inform��es sobre o gerenciamento de mem�ria 
 *    devem ir para um m�dulo de gerenciamento de memoria 
 *    dentro do executive, chamado mm.h

 */

#ifndef ____MEMORY_H
#define ____MEMORY_H  1
 
/*
 * memory_d:
 *     Memory card info structure.
 *     Informa��es sobre o hardware do cart�o de mem�ria.
 */ 
struct memory_d 
{
    object_type_t  objectType;
    object_class_t objectClass;

	//callback ;d

    int type;             //ddr2, ddr3 ...
    unsigned long size;   //
    int channel;          // single ou dual.
    unsigned long nb_frequency;	
	//fsb:dram
	//cas latency cl
	//ras to cas delay
	//ras precharge
	//cycle time
	//row refresh cycle time
	//command rate
	//...
	
	//module size
	//max bandwidth
	//manufacturer 
	//part number
	//serial number
	//week/ year
	//
};


#endif   


//
// End
//

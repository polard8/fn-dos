// modules.h  

/*
 *
 * Descrição:
 *     Header principal para o gerenciamento de módulos do kernel.
 *     Faz operações como carregamento e ligação de módulos,
 *     correção das chamadas presentes no módulos, coloca módulos em 
 *     índices e tabelas, etc ...
 *
 * Obs:
 *     O kernel tem módulos que estão dentro do kernel base
 *     e são incluídos na hora da compilação. Porém o Kernel
 *     também pode possuir módulos que estão fóra do kernel base
 *     mas ainda estão em kernel mode, esses são ligados na hora
 *     do carregamento ou na hora da execução.
 *
 *     Extendendo a idéia pode haver módulos em qualque um dos 
 *     anéis 0,1,2,3.
 * 
 *     Os módulos no kernel base são chamados de 'MB' e os
 *     módulos do kernel em kernel mode são chamados de 'M0'.
 *     
 *     ... @todo: BUG BUG
 *
 * 2015
 */

#ifndef __MODULES_H
#define __MODULES_H    1


/*
 * module_d:
 *
 */ 
 
/* 
typedef struct module_d module_t;  
struct module_d
{
    int Id;
	int Used;
	int Magic;
    //...	
}; 
module_t *CurrentModule; 
 
unsigned long moduleList[32];
 */

#endif  

//
//
//


/*
 * File: sm/sys/signal.c  
 * #bugbug: esse n�o � o tratamento de sinal da libc ... o da libc deve ser resolvido em klibc
 *
 * Descri��o:
 *     Signal Manager.
 *     Gerencial o uso de sinais.
 *
 * Vers�o: 1.0, 2016 - Created.
 */


/*
  Signal Manager: Gerencia os sinais recebidos e enviados pelos processos.
                 Os sinais enviados para o processo kernel ser�o atendidos
 na forma de requests. A rotina de request sinaliza os processo sobre a ocorrencia
 de eventos e toma deceis�es relativas ao estado dos processos, se eles devem esperar
 ou proceguir etc...   
 
 Obs: Com sinais, os processo podem conversar um com o outro.

 Obs: Um sinal significa que rodar� uma rotina espec�fica de sinal que ativar�
      um request do kernel al�m de rodar outros m�todos.
      A vari�vel Signal ser� interna aqui em signal.c, podendo ser manipulada
      somente por esse arquivo. J� as defini��es de sinal ser�o globais e p�blicas
      para que as aplica��es possam utilizar sinais. O que n�o impede implementar
      sinais exclusivos para determnados m�dulos. (Isso parece ser muito legal:)).
      Para isso � s� separa os sinais por grupos, um grupo para cada m�dulo,
      isso ajudaria a organizar os m�dulos por n�meros al�m dar prioridade
      para alguns m�dulos.

 Os grupos de sinais:
 ===================
 Para simplificar usaremos apenas cinco grupos de sinais, s�o eles:

 0 - KernelSignal - Sinais usados pelo processo kernel e rotinas de muito privil�gio.
 1 - HalSignal - Sinais utilizados pelo m�dilo /hal que lidam com hardware.
 2 - MicrokernelSignal - Sinais utilizados pelo m�dulo /microkernel. Atuam sobre processos e threads.
 3 - ExecutiveSignal - Sinais utilizados pelo m�idulo /executive. Atuam sobre o sistema de uma forma geral.
 4 - UserSignal - Sinais utilizados pelos processos criados pelos usu�rios.

*/

#include <kernel.h>


/*
  @todo: (signals) 
  Interrup��o de teclado.
  abort
  
  ...
  
 */



//
// Aqui degue uma defini��o interna dos n�meros dos sinais que ser�o usados por cada grupo 
// de sinais.
//


//
//  0 - KernelSignal
//
#define KERNELSIGNAL_x 4000
//4000~4999
//...

//
// 1 - HalSignal
//
#define HALSIGNAL_x 3000
//3000~3999
//...

//
// 2 - MicrokernelSignal
//
#define MICROKERNELSIGNAL_x 2000
//2000~2999
//...

//
// 3 - ExecutiveSignal
//
#define EXECUTIVESIGNAL_x 1000
//1000~1999
//...

//
// 4 - UserSignal
//
#define USERSIGNAL_NULL 0
#define USERSIGNAL_KILLPROCESS 1
//0~999
//...


/*
enum signal_t {
	KernelSignal,  //0
	HalSignal,     //1
	MicrokernelSignal,  //3
	ExecutiveSignal,    //4
	UserSignal,         //5
};
*/


int Signal=0;




// Unix signal support.
// This routine was called by the task switch as a extra service.
// See: ts.c

int KiSignal(void)
{
    // #todo
    // Vamos olhar o supporte a sinais na estrutura do processo
    // e chamarmos os tratadores adequados de acordo com o sinal recebido.
    // ee: p->signal   p->umask  p->sigaction[]
    
    //debug_print("KiSignal: [TODO] Unix signal support.");
    return 0;
}





/*
 * signalSend:
 *     Envia um sinal para um processo.
 */
 
int 
signalSend ( 
    struct process_d *process, 
    int signal )
{

	//SIGNAL_COUNT_MAX
	
	//Limit
    //if(signal >= 32){
	//	return 1;
	//}


    if (signal < 0 || signal >= 32)
    {
        debug_print ("sendSignal: signal limits\n");
        return 1;
    }

    if ( (void *) process == NULL ){
        debug_print ("sendSignal: process\n");
        return 1;
        
    }else{

        // #todo:
        // Check mask.
        // Check sigaction structure. p->sigaction[32];

        process->signal = (unsigned long) signal;
        
        //ok
        return 0; 
    };

// fail
    debug_print ("sendSignal: [FAIL] \n");
        
    return (int) -1;
}


/*
 * signalInit:
 *     Inicializa��o do m�dulo de gerenciamento de sinais.
 */

int signalInit (void){
	
    Signal = 0;	

	return 0;
}


//
// End.
//


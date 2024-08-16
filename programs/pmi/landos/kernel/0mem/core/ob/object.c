/*
 * File: ob/object.c
 *
 * Descri��o:
 *   #importante: 
 *   O gerente de arquivos ser� o manipulador de arquivos usados pelo sistema 
 * de arquivos. Lembrando que o assim como no UNIX tudo � considerado um 
 * arquivo, aqui, tudo � considerado um objeto. Ent�o o sistema de arquivos 
 * manipular� os objetos. Mas ele poder� chama-los de arquivos se quiser. 
 *
 *    Object manager, m�dulo do tipo MB - M�dulos inclu�dos no Kernel Base.
 *
 * Arquivo principal do m�dulo sm\ob do executive.
 *    
 * Gerencia os recursos do sistema. Criando, abrindo, fechando objetos e 
 * concedendo ou negando o acesso a ele.
 *
 *    Para gerenciar o uso de um recurso o kernel faz utiliza semaforos, 
 * mutexes.
 * 
 * Ex: Um fs � um objeto, que tem seu channel pra receber mensagens e uma 
 * aplica��o solicita alguma coisa do sistema de arquivos atrav�s de um 
 * canal de comunica��o. O fs pode estar indispon�vel no momento. 
 * A aplica��o cliente pode ser um cliente n�o valido.
 *
 * Obs: 
 * O object manager � o melhor lugar pra implantar rotinas de seguran�a.
 *
 * Claro que o Object Manager deve chamar as rotinas do m�dulo de seguran�a, 
 * mas o Object Manager receber� solicita��es de usu�rios e processos para 
 * manipular objetos, ent�o deve decidir se o usu�rio, grupo ou processo 
 * tem autoriza��o para manipular o objeto.
 *
 * Obs: 
 * Uma estrutura de objeto deve conter indica��es de que processo ou usu�rio 
 * est� manipulando o objeto no momento. Tamb�m um n�mero m�ximo de processos 
 * que pode ficar na fila para usar esse objeto. A fila decrementa e quando 
 * chegar a zero, esse objeto pode ser fechado, caso n�o seja um objeto f�sico, 
 * como no caso de discos.
 *
 *IMPORTANTE: 
 * Que ningu�m duvide da import�ncia do gerente de objetos. Pois os recursos 
 * do sistema s�o configurados como objetos, ent�o para um processo ter acesso 
 * � algum recurso do sistema ter� que solicitar o recurso ao gerente de objetos, 
 * que pode interagir com o sistema de seguran�a para ver se o processo ou 
 * usu�rio tem permiss�o para utilizar o recurso desejado. 
 *
 * @todo: 
 * Ainda h� muito pra aprender sobre objetos e gerencia de objetos. 
 * Tendo em vista que o conceito de objetos para kernel mode em C e para 
 * User Mode com linguagem de alto n�vel � bem diferente.
 *
 * 2015 - Created by Fred Nora.
 */



#include <kernel.h>


struct object_d  objects_km[256+1];  //objetos em kernel mode.
struct object_d  objects_um[256+1];  //objetos em user mode. 
struct object_d  objects_gui[256+1]; //objetos gr�ficos. 

// Se o gerenciador de recursos foi inicializado.
int g_object_manager_status=0;

//id do objeto atual
int g_current_object=0;

//id da lista ao qual o objeto atual pertence.
// object_km, object_um, object_gui. 
int g_current_list=0;


/*
 * init_object_manager:
 *     Inicializa o gerenciador de objetos.
 */

int init_object_manager (void)
{
    int Status = 0;


//#ifdef EXECVE_VERBOSE	
	//printf("Initializing Object Manager..\n");
//#endif	
    
    // ??
    g_current_object = 0;         //objeto numero 0
    g_current_list = 0;            //lista de objetos em kernel mode.



   // #todo: 
   // Initialize object List.

    //Inicializado.
	g_object_manager_status = 1;
	g_module_objectmanager_initialized = 1;
	
//#ifdef EXECVE_VERBOSE	
	//printf ("Done\n");
//#endif	


    return (int) Status;
}


//
// End.
//


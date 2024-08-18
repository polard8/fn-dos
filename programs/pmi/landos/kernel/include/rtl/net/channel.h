/*
 * File: channel.h 
 *
 * Descri��o:
 *     Header for channel manager.
 *     Channel manager. 
 *     Gerenciamento de canais Client/Server para troca de mensagens entre 
 * processos.
 *    " Um canal de comunica��o � composto de dois soquetes, um para o cliente 
 * e outro para o servidor. "
 *
 * ?? isso n�o deveria fazer parte do /pc/ipc
 *
 * Vers�o 1.0, 2015, 2016.    
 */

#ifndef ____CHANNEL_H
#define ____CHANNEL_H  1


/*
#define  LISTEN_CHANNEL 0x1
#define MESSAGE_CHANNEL 0x2

typedef enum _ECHANNEL_STATE {
    ClientIdle,
    ClientSendWaitReply,
    ClientShutdown,
    ServerIdle,
    ServerReceiveMessage,
    ServerShutdown
} ECHANNEL_STATE;
*/



/*
 * Estrutura para canal.
 * Serve para estabelecer uma conex�o,
 * ?? pelo jeito n�o serve para 
 * trocar mensagens, somente para estabelecer a 
 * conex�o.
 * Obs: Essa estrutura � aceit�vel, est� em conformidade 
 * com os padr�es encontrados
 */

struct channel_d
{
    object_type_t objectType;
    object_class_t objectClass;

    int id;
    
    int used;
    int magic;

    int type; //??

    int state;    //Aberto ou fechado.

    //...

    //Os dois soquetes do canal de comunica��o.
    // acho que soquete tem stream.


    struct socket_d *server_socket;
    struct socket_d *client_socket;

    // Buffer usado pelo dois soquetes na mesma m�quina.
    // 

    void *____BUFFER;


    // Quem � o dono do canal?
    // Quem est� enviando?
    // Quem est� recebendo.
    //struct process_d *OwnerProcess;
    //struct process_d *SenderProcess;
    //struct process_d *ReceiverProcess;

	// usado para comuni��o entre threads.
	//#importante
	//Quando a comunica��o for entre processos,
	//podemos que usar a thread de controle do processo que 
	//est� recebendoa mensagem.
    //struct thread_d *SenderThread;
    //struct thread_d *ReceiverThread;

	//#importante:
	//context ??
	//me parece que um ponteiro pra uma estrutura do 
	//tipo context � necess�rio 
	//context deve conter os elementos necess�rios 
	//para a transmiss�o da mensagem. Como o buffer 
	//de mem�ria compartilhada.
	//
    
	//?? O que � isso ???
	//me parece que � necess�rio.
	//struct channel_d *serverchannel;
};
//struct channel_d *CurrentChannel;
//...

//unsigned long channelList[32];


//
// Prototypes ====================================================
//

//#todo: arguments.
void *CreateChannel (void);

int DestroyChannel (struct channel_d *channel);

//#todo: arguments.
int OpenChannel ( void );
int CloseChannel (struct channel_d *channel);


#endif    


//
// End.
//


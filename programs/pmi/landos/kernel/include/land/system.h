// system.h (System Management)
// 2015 - Created by Fred Nora.

#ifndef __SYSTEM_H
#define __SYSTEM_H    1

/*
 *     Header para rotinas de gerenciamento do sistema dentro do m�dulo 
 * executive do kernel.
 *     O subsistema recebe as chamadas dos programas que est�o em use mode. 
 * � a porta de entrada para o kernel.
 *     Lembrando que o sistema compreende o Boot, Kernel e User.
 * @todo:
 *     todos os servi�os oferecidos est�o nos 
 *     arquivos principais dos m�dulos hal microkernel e executive
 *     e come�am com 'sys_'.
 */

// int current_taskman_server; 

//
// getpid_t:
//     �ndices usados pela fun��o gde_get_pid(x)
//     Usada para obter o pid de alguns drivers e servidores
// do sistema. Aqueles servidores que s� podem ter um do tipo 
// rodando ao mesmo tempo.
//

typedef enum {
    GETPID_NULL,
    GETPID_WS,
    GETPID_WM
    //...
}getpid_t;


//
// ## sys storage support ##
//

// see: main.c
extern int system_disk;
extern int system_volume; 
 
//======================================== 
//Esses s�o os principais arquivos usandos na 
//inicializa��o do sistema. 
//Obs: No fat16 eles se apresentam em mai�sculas.
//#define INITTXT_PATH  "/root/init.txt"
//#define BM_PATH       "/root/bm.bin"
//#define BL_PATH       "/root/bl.bin"
//#define KERNEL_PATH   "/root/kernel.bin"
//#define INIT_PATH     "/root/init.bin"
//#define SHELL_PATH    "/root/shell.bin"
//#define TASKMAN_PATH  "/root/taskman.bin" 
//...
//========================================
 

//#define SYSTEMMODE_EDITBOX  0
//#define SYSTEMMODE_TERMINAL 1
//int g_system_mode;  //terminal ou edibox. 


//
// Identifica��o do processo que est� efetuando logon e 
// identifica��o do processo que est� efetuando logoff.
// Precisamos registrar o processo que efetuou logon.
// ?? Porque eu ainda n�o sei.
// Uma rotina de registro de processo de logon 
// ser� oferecida para processos em user mode,
// � necessario enviar uma flag de seguran�a,
// pode ser um magic number ...
// ent�o esse proecesso ter� direito de efetuar o logon 
// se tiver privil�gios v�lidos em sua estrutura.
// logo em seguida registraremos qual foi o processo 
// que efetuou logon. Outro processo n�o poder� 
// efetuar logon durante aquela sess�o.
// Caso semelhante � o logoff. O processo dever� 
// enviar uma flag de seguran�a e ter atributos v�lidos 
// para efetuar o logoff.
//

// see: main.c
extern int gLogonPID;
extern int gLogoffPID;
 
/*
 * Abaixo temos uma lista de variaveis de ambiente usadas
 * pelo sistema, come�adas com SYSTEM_.
 */ 

/*
 * Disks
 *    Discos f�sicos   
 */
#define SYSTEM_DISK0  "/disk0" 
#define SYSTEM_DISK1  "/disk1"
#define SYSTEM_DISK2  "/disk2"
#define SYSTEM_DISK3  "/disk3"
#define SYSTEM_DISK SYSTEM_DISK0  
//...

/*
 * Volumes
 *    Cada parti��o � um volume.
 *    Um volume pode ocupar mais de um disco. 
 */
#define SYSTEM_VOLUME0  "/volume0"   //vfs
#define SYSTEM_VOLUME1  "/volume1"   //parti��o de boot
#define SYSTEM_VOLUME2  "/volume2"   //parti��o do sistema.
#define SYSTEM_VOLUME3  "/volume3"   //??indefinido.

#define VHS_VOLUME    SYSTEM_VOLUME0
#define BOOT_VOLUME   SYSTEM_VOLUME1
#define SYSTEM_VOLUME SYSTEM_VOLUME2  
//...

#define SYSTEM_ROOT      "root:/"
#define SYSTEM_ROOTDIR   SYSTEM_ROOT      

 
/*
 * /disk0
 *     Esse ser� sempre o disco principal.
 *     Lista de diret�rios dentro do disco principal.
 */
 
//
// Obs: Isso s�o op��es ainda n�o definidas.
// 
 
//principais.  
#define SYSTEM_GUSERS    "/user"    // (os perfis de usu�rio ficar�o aqui.)
#define SYSTEM_GCMD      "/cmd"      //COMANDO USADOS PELO SHELL CHAMAR�O OS PROGRAMAS QUE EST�O AQUI.
#define SYSTEM_GTMP      "/tmp"      //ARQUIVOS TEMPOR�RIOS
#define SYSTEM_GDOWNLOAD "/download"  //DOWNLOADS

//secund�rios.
#define SYSTEM_GBUILD    "/gbuild"   //Build
#define SYSTEM_GDOCS     "/gdocs"    //Docs
#define SYSTEM_GRAMADO   "/gramado"  //System (aqui ficar�o os bin�rios dos programas, em pastas)
#define SYSTEM_GSDK      "/gsdk"     //SDK 
#define SYSTEM_GSRC      "/gsrc"     //Source 


//...

//files (path para alguns arquivos principais)
#define SYSTEM_BM       "/BM.BIN"
#define SYSTEM_BL       "/BL.BIN"
#define SYSTEM_KERNEL   "/KERNEL.BIN"
#define SYSTEM_IDLE     "/IDLE.BIN"
#define SYSTEM_TASKMAN  "/TASKMAN.BIN"
#define SYSTEM_SHELL    "/SHELL.BIN"
#define SYSTEM_INIT     "/INIT.TXT"   // CONFIGURA��ES DE INICIALIZA��O.
#define SYSTEM_SWAP     "/SWAP.BIN"   // (ARQUIVO DE PAGINA��O)
//...

 
//Computer.
#define SYSTEM_COMPUTER    "COMPUTER=$"

//Hadware.
//...

//User.
#define SYSTEM_USER        "USER=/$"
#define SYSTEM_USERNAME    "USERNAME="
//...

//Media.
#define SYSTEM_MEDIADISK    "MEDIA=/disk(0000)"
#define SYSTEM_MEDIAVOLUME  "MEDIA=/volume(0000)"    //Parti��o.
//...
 
//

//devices.
#define SYSTEM_DEVICE          "DEVICE=/$"
#define SYSTEM_DEVICECPU       "DEVICE=/cpu"
#define SYSTEM_DEVICEMEMORY    "DEVICE=/memory"
#define SYSTEM_DEVICENIC       "DEVICE=/nic"     //NIC (placa de rede).
#define SYSTEM_DEVICEKEYBOARD  "DEVICE=/keyboard"
#define SYSTEM_DEVICEMOUSE     "DEVICE=/mouse"
//...


//
// @todo: Continuar criando vari�veis de ambiente.
//

//...


//
//  SYSTEM METRICS INDEX
//


//*Importante.
#define SM_NULL 0  
#define SM_SCREENWIDTH 1
#define SM_SCREENHEIGHT 2
#define SM_BPP          3 //Bits Per Pixel.
#define SM_BACKBUFFER_VA 4  //Virtual address for backbuffer.
#define SM_BACKBUFFER_PA 5  //phisical address for backbuffer.
#define SM_FRONTBUFFER_VA 6  //Virtual address for frontbuffer.
#define SM_FRONTBUFFER_PA 7  //phisical address for frontbuffer.
#define SM_KERNELSIZE 8
#define SM_KERNELHEAPSIZE 9
#define SM_KERNELSTACKSIZE 10
#define SM_CHARWIDTH 11
#define SM_CHARHEIGHT 12
#define SM_DEVELOPER_EDITION 13

#define SM_GETMOUSEX 20
#define SM_GETMOUSEY 21

//Continua ...
//@todo.


//
//    ****    SYSTEM STATUS INDEX   **** 
//

#define SS_NULL          0  
#define SS_LOGGED        1  //estamos logados.?
#define SS_USING_GUI     2  // estamos no modo gr�fico?
#define SS_KERNELSTATUS  3  //
//Continua ...
//@todo.

//procedure tupe mode
//@TODO: CRIAR UM ENUM
#define PROCEDURE_TYPE_MODE_TERMINAL  1    //digitando em um terminal/
#define PROCEDURE_TYPE_MODE_EDITBOX   2    //digitando em um editbox.
//...
 
//
// Globals.
// 

// ??
typedef enum {
    systemsizeNull,
    systemsize1,     //#  1 O sistema tem pelo menos 32 MB
    systemsize2,     //#E 2 O sistema tem pelo menos 64 MB
    systemsize3,     //#F 3 O sistema tem pelo menos 96 MB
    systemsize4,     //#G 4 O sistema tem pelo menos 128 MB 
    systemsize5,     //#A 5 O sistema tem pelo menos 160 MB 
    systemsize6,     //#B 6 O sistema tem pelo menos 192 MB 	
    systemsize7,     //#C 7 O sistema tem pelo menos 224 MB
    systemsize8,     //#D 8 O sistema tem pelo menos 256 MB
    systemsizeFull,  //     O sistema tem pelo menos 288 MB	
}system_size_t;


//?? rever esse coment�rio.
// Aqui salvaremos o n�mero que identifica o tipo de sistema dado o tamanho.
// Se o sistema tiver 288 MB ou mais ent�o ele ser� do tipo Full
// e conter� 8 bancos de mem�ria de 32Mb mais uma user session de tamnaho variado.
extern int systemSize;

//Flag para habilitar as op��es para o desenvolvedor.
extern int gDeveloperOptions;

// ??
extern int gSystemEdition;

extern int gSystemStatus; //?? Usado pelo construtor.

//
//  Shutdown support
//

//Salvar aqui o endere�o da rotina do BM que desliga a m�quina via APM.
//O endere�o e a rotina s�o de 32bit.
extern unsigned long shutdown_address;

static char *default_user_name = DEFAULT_USERNAME;

/*
 * version_d:
 *     Estrutura para vers�o do sistema.    
 *     O que determina a vers�o do sistema � a vers�o do Kernel.
 *
 * @todo: 
 *     Usar apenas esses 4 elementos.
 *     Dados complementares sobre a vers�o devem ficar 
 *     na estrutura versioninfo.
 *
 * Obs: Talvez usar um header. version.h.
 * #bugbug: 
 * J� tem version_t tefinida em algum lugar.
 *         Aparentemente n�o deu mais problema. 
 */

struct version_d
{
    unsigned long Major;
    unsigned long Minor;
    unsigned long Build;
};
extern struct version_d  *Version;
//...

/*
 * version_info_d:
 *     Dados complemetares sobre a vers�o.
 */

struct version_info_d
{
    struct version_d *version;

    char *string;             //String para o nome da vers�o "VERSION..."
    char *copyright_string;   //"ex: (c) Copyright Nora Code"
    // ...
};
extern struct version_info_d *VersionInfo;


/*
 * system_d:
 *     System information structure:
 *     Essa estrutura guarda as informa��es gerais sobre o sistema.
 *     Guarda ponteiros para as principais estruturas do sistema, 
 * desde informa��es de boot, at� informa��es se��es de usu�rios.
 * 
 */

struct system_d
{
    int used;
    int magic;

    // Version
    struct version_d *version;
    struct version_info_d *version_info;

    // storage 
    int disk;
    int volume;

    // System  info.
    int ProcessorArchitecture;
    int NumberOfProcessors;
    int PageSize;

    struct devices_d *deviceList;

    //...
};
extern struct system_d *System;


//
// == Prototypes ===============================================
//


void servicesPutChar(int c);
unsigned long serviceCreateWindow ( char * message_buffer );

/*
 * SendMessage:
 *     Envia mensagem para um procedimento de janela.
 */
 
unsigned long 
SendMessage ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

// System Server support.
int init_systemserver (void);

//Metodo nulo.
//Pode ser usado em di�logos.
void *systemNull (void);  

/*
 * systemLinkDriver:
 *     Linkando um driver ao sistema operacional
 */
 
void *systemLinkDriver ( 
    unsigned long arg1, 
    unsigned long arg2, 
    unsigned long arg3 );
 
/*
 * systemShowDevicesInfo:
 *     Mostrar informa��es sobre o sistema, seguindo a ordem de
 *     velocidade dos dispositivos e barramentos.
 *     Ex: CPU, Mem�ria, PCIE (video), South Bridge, Super Io ...
 *     Apresentar em ordem alfab�tica.
 */
 
void systemShowDevicesInfo (void);

void systemSetupVersion (void); 

/*
 * SystemMenu: 
 * System Menu para manipular a janela ativa.
 * Interface que chama o control menu da janlea ativa.
 */

int SystemMenu (void);


/*
 * system_get_pid: 
 *     A api solicita o pid de alguns servidores e drivers.
 * 
 */ 
int system_get_pid (int index);

/*
 * systemGetSystemMetrics: 
 *     A api solicita algumas informa��es de m�trica de sistema.
 */ 
unsigned long systemGetSystemMetrics ( int index );
 

/*
 * SystemMenuProcedure:
 *     O procedimento do Control Menu principal.
 *     Menu do sistema, manipula a janela ativa.
 */
 
unsigned long 
SystemMenuProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
   
void systemReboot (void);    //systemReboot: Reboot stuff.

void systemShutdown (void);      //systemShutdown: Shut down stuff.

//Chamar a fun��o de 32 bit herdado do BM.
void systemShutdownViaAPM (void); 

//Pega informa��es de medida de elementos do sistema.
void *systemGetSystemMetric(int number);

//Pega informa��es de status de elementos do systema.
void *systemGetSystemStatus(int number);

int init_executive (void);

#endif   

//
// End
//

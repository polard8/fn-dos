// window.h 
// 2014 - Created by Fred Nora.

/*
 * Fun��es e par�metros para o kernel controlar a interface gr�fica 
 * e as opera��es com v�deo.
 * WINDOW -> DESKTOP -> ROOM (WINDOW STATION) -> USER SECTION.
 */


#ifndef __WINDOW_H
#define __WINDOW_H    1

// z order support.

#define KGWS_ZORDER_BOTTOM  0 
#define KGWS_ZORDER_TOP     1023   //top window
#define KGWS_ZORDER_MAX     1024   //max

// kgws.c
extern unsigned long Windows[KGWS_ZORDER_MAX];

// kgws.c
//id da janela que o mouse est� em cima.
extern int window_mouse_over; 

//
//  ## Ponteiros para �cones ##
// 
 
// Ponteiros para o endere�o onde os �cones 
// foram carregados.

// queremos saber se o endere�o alocado eh compartilhado ...
// para o window server usar ... entao chamaremos de sharedbufferIcon.

// kgws.c
extern void *shared_buffer_app_icon;  //1
extern void *shared_buffer_file_icon; 
extern void *shared_buffer_folder_icon;
extern void *shared_buffer_terminal_icon;
extern void *shared_buffer_cursor_icon;
// ... 

// =======================


// pega a janela que est� mais ao topo da zorder e que
// corresponda �s cordenadas do mouse.
// retorna window id
int top_at ( int x, int y );


void *ui_get_system_icon( int n );

//testando ... devemos chamar isso
//somente depois que todas as estruturas 
//necess�rias estiverem inicializadas.
//como filsystem. 

int windowLoadGramadoIcons (void); 
 
//test: suporte a getch();

int window_getch (void); 

// #importante:
// Tipos de mensagem de comunica��o nos di�logos 
// e procesimento de janelas:
// 
// SIGNAL_       Sinal. N�o cont�m argumentos.
// MSG_          Message. Cont�m os argumentos padr�o.
// STREAMMSG_    Streams. O argumento � um ponteiro para uma stream.
// BUFFER_MSG_   Buffer. O argumento � um ponteiro para um buffer.
// CAT_MSG_      Concatenate. Os argumentos long1 e long devem ser concatenados.
 
//
// Window handle status
// Se uma janela est� aberta ou n�o. 
//
#define HANDLE_STATUS_CLOSE 0
#define HANDLE_STATUS_OPEN 1
 
 
//used
#define WINDOW_NOTUSED   0
#define WINDOW_USED      1
#define WINDOW_GC        216   //Sinalizada para o GC.
//...

//magic
#define WINDOW_NOTMAGIC  0
#define WINDOW_MAGIC     1234 
#define WINDOW_CLOSED    4321
//... 
 
 
//desktop window. (�rea de trabalho) 
//#define MAINWINDOW_DEFAULTX  ?
//#define MAINWINDOW_DEFAULTY  ?
  
// N�mero m�ximo de janelas.
//@todo: Aumentar esse tamanho.


// # window lock support #
#define WINDOW_LOCKED 1
#define WINDOW_UNLOCKED 0


/*
 * Messages.
 * mensagens para procedimentos de janelas e 
 * para di�logos dentro do gws.
 * Obs: Isso refere-se principalmente � janelas.
 */

 //??tipos de mensagens ??
#define MSG_NULL          0 
#define SIGNAL_NULL       0 
#define STREAM_MSG_NULL   0 
#define BUFFER_MSG_NULL   0 
#define CAT_MSG_NULL      0  
 
//window (1-19)  
#define MSG_CREATE        1
#define MSG_DESTROY       2
#define MSG_MOVE          3 
#define MSG_SIZE          4
#define MSG_RESIZE        5
//#define MSG_OPEN        6
#define MSG_CLOSE         7
#define MSG_PAINT         8
#define MSG_SETFOCUS      9
#define MSG_KILLFOCUS     10
#define MSG_ACTIVATE      11
#define MSG_SHOWWINDOW    12 
#define MSG_SETCURSOR     13
#define MSG_HIDE          14  // ?? (MIN)
//#define MSG_MINIMIZE    14  // ?? (MIN)
#define MSG_MAXIMIZE      15
#define MSG_RESTORE       16
#define MSG_SHOWDEFAULT   17


//keyboard (20-29)
#define MSG_KEYDOWN       20
#define MSG_KEYUP         21
#define MSG_SYSKEYDOWN    22
#define MSG_SYSKEYUP      23

//mouse (30 - 39)
//tem uma lista de eventos de mouse em events.h
#define MSG_MOUSEKEYDOWN  30
#define MSG_MOUSEKEYUP    31
#define MSG_MOUSEBUTTONDOWN	30
#define MSG_MOUSEBUTTONUP	31 
#define MSG_MOUSEMOVE	    32
#define MSG_MOUSEOVER	    33
#define MSG_MOUSEWHEEL	    34
#define MSG_MOUSEPRESSED	  35
#define MSG_MOUSERELEASED	  36
#define MSG_MOUSECLICKED	  37
#define MSG_MOUSEENTERED	  38    //?? capturou ??
#define MSG_MOUSEEXITED	       39   //?? descapturou ??
//#define MSG_MOUSEMOVEBYOFFSET
//#define MSG_MOUSEMOVETOELEMENT

//outros (40 - ...)
#define MSG_COMMAND       40
#define MSG_CUT           41
#define MSG_COPY          42
#define MSG_PASTE         43
#define MSG_CLEAR         44 
#define MSG_UNDO          45
#define MSG_INSERT        46
#define MSG_RUN_PROCESS   47
#define MSG_RUN_THREAD    48

//Quando um comando � enviado para o terminal. ele ser� atendido pelo
//m�dulo /sm no procedimento de janela do sistema.
//Todas as mensagens de terminal ser�o atencidas pelo procedimento de janela 
//nessa mensagem.
//#bugbug: temos outro grupo de mensagems abordadndo esse tema logo abaixo.

#define MSG_TERMINAL_COMMAND 49
#define MSG_TERMINAL_SHUTDOWN 50
#define MSG_TERMINAL_REBOOT   51

#define MSG_DEVELOPER 52


//UM TIMER SE ESGOTOU,
#define MSG_TIMER 53   
//...


//o servidor de rede se comunica com o processo.
#define MSG_AF_INET 54
#define MSG_NET_DATA_IN 55

//o driver de network est� notificando um processo em ring3.
#define MSG_NETWORK_NOTIFY_PROCESS 56


//
// mouse support: continua��o ...
//
#define MSG_MOUSE_DOUBLECLICKED   60
#define MSG_MOUSE_DRAG            61
#define MSG_MOUSE_DROP            62
//...

//
//  terminal commands
//

#define MSG_TERMINALCOMMAND      100
#define TERMINALCOMMAND_PRINTCHAR 1000
//#define TERMINALCOMMAND_PRINT??? 1001
//...


// o evento de rolagem aconteceu ...
// O n�mero do evento ser� entregue em long1.
#define MSG_HSCROLL 2000
#define MSG_VSCROLL 2001



// 
// ==== Window Type ====
//

#define WT_NULL          0 
#define WT_SIMPLE        1
// Igual simples, mais uma bordinha preta.
#define WT_EDITBOX       2
// Sobreposta (completa)(barra de titulo + borda +client area). 
#define WT_OVERLAPPED    3  
// Um tipo especial de sobreposta, usada em dialog ou message box. 
// (com ou sem barra de titulo ou borda)
#define WT_POPUP         4
// Caixa de sele��o. Caixa de verifica��o. 
// Quadradinho.  
#define WT_CHECKBOX      5
// Cria uma scroll bar. 
// Para ser usada como janela filha.  
#define WT_SCROLLBAR     6  
#define WT_EDITBOX_MULTIPLE_LINES 7
#define WT_BUTTON        8   
#define WT_STATUSBAR     9
// Pequeno ret�ngulo com uma imagem bmp e talvez texto.
#define WT_ICON          10
#define WT_TITLEBAR 11
//... 



// window style
#define WINDOW_STYLE_FLOATING 1000 
#define WINDOW_STYLE_DOCKING  2000  //(atracada em algum canto.)
//...


// window status
#define WINDOW_STATUS_ACTIVE       1
#define WINDOW_STATUS_INACTIVE     0
//...

//window relationship status. (seu status em rela��o as outras janelas.)
//Obs: tem uma estreita liga��o com o status da thread que est� trabalahndo com ela 
//e com a prioridade dessa thread e do processo que a possui.
// *** RELA��O IMPLICA PRIORIDADE ***
#define WINDOW_REALATIONSHIPSTATUS_FOREGROUND     1000
#define WINDOW_REALATIONSHIPSTATUS_BACKGROUND     2000
#define WINDOW_REALATIONSHIPSTATUS_OWNED          3000  //Possuida por outra janela.
#define WINDOW_REALATIONSHIPSTATUS_ZAXIS_TOP      4000
#define WINDOW_REALATIONSHIPSTATUS_ZAXIS_BOTTOM   6000
//...

// Apresenta��o.
#define VIEW_NULL       0
#define VIEW_FULL       1
#define VIEW_MAXIMIZED  2  
#define VIEW_MINIMIZED  4
#define VIEW_NORMAL     8  // Normal (restaurada)
// ...


//
// ## botoes  ##
//

//button state
#define BS_NULL 0 
#define BS_DEFAULT 1
#define BS_FOCUS   2
#define BS_PRESS   3
#define BS_HOVER   4
#define BS_DISABLED 5
#define BS_PROGRESS 6
//...


    //button states:
    //0. NULL.
	//1. Default 
    //2. Focus
    //3. Expanded/Toggled/Selected
    //4. Disabled
    //5. Hover and Active	

//#define BN_CLICKED  200
//#define BN_DOWN     1
//#define BN_UP       2
//#define BN_SELECTED 3



 
//@todo: what ??? 
//?? um handle para o desktop. 
#define HWND_DESKTOP 0



/*
 * Dimens�es: 
 * 
 * Parametro principal para dimens�es de janela.
 * todos os outros tomam esse como ref�rencia.
 * depende do modo que estiver usando.
 *
 * vesa 112:
 *
 * 640x480x24bit - (3 bytes por pixel)
 * 
 * @todo, o kernel usar� dimens�es 640x480 no modo gr�fico.
 */   
#define KERNEL_COL_MAX 640 
#define KERNEL_LIN_MAX 480 

#define	BAR_STEPS   46
#define LINE KERNEL_COL_MAX 

//dimens�es - provisorio
#define COL_MAX   KERNEL_COL_MAX 
#define LINHA_MAX KERNEL_LIN_MAX  


/*
 * Constants para a task bar.
 */
 
//#define TASKBUTTONS_BASE 40
//#define CLOCK_BASE  (KERNEL_COL_MAX-40)


//=========================================
//    ****    KERNEL WINDOW    ****
//Defini��es padronizadas para janelas do kernel usadas para 
//fornecer informa��es sobre o sistema.
// (Ret�ngulo grande no topo da tela.)
// #bugbug
// Isso n�o � uma coisa boa.

#define KERNEL_WINDOW_DEFAULT_LEFT 0
#define KERNEL_WINDOW_DEFAULT_TOP  0
#define KERNEL_WINDOW_DEFAULT_WIDTH  800
#define KERNEL_WINDOW_DEFAULT_HEIGHT (600/4) 
#define KERNEL_WINDOW_DEFAULT_CLIENTCOLOR  xCOLOR_GRAY2
#define KERNEL_WINDOW_DEFAULT_BGCOLOR      xCOLOR_GRAY1
//...


//  ESSA VARI�VEL BLOQUEIA O FOCO NA JANELA DO DESENVOLVEDOR
extern int _lockfocus;

// ESSA SER� USADA DEPOIS QUANDO A INTERFACE GR�FICA ESTIVER MAIS ROBUSTA;
extern int gFocusBlocked;   

// #todo: deletar.
extern unsigned long g_mainwindow_width;
extern unsigned long g_mainwindow_height;
extern unsigned long g_navigationbar_width;
extern unsigned long g_navigationbar_height;


/*
 * button_d:
 *     Structure for button object.
 */

struct button_d
{
    object_type_t objectType;
    object_class_t objectClass;
    int used;
    int magic;

    // ??
    // Ordem dos bot�es que pertencam � mesma janela.
    // A qual janela o bot�o pertence.
    // Esse �ndice pode trabalhar junto com 
    // a lista encadeada de 'next'.

    //int index;	
    struct window_d *window; 
    
	// label
	// #todo: mudar o tipo para (char *)
    unsigned char *string; 
	
	// Estilo de design.
	// 3D, flat ...
    int style;
	
    //button states:
    //1. Default
    //2. Focus
    //3. Expanded/Toggled/Selected
    //4. Disabled
    //5. Hover and Active	
    int state;

	//Check Boxes
	//Group Boxes
	//Push Buttons
	//Radio Buttons

    int type;

    int selected;
	
	// Border color
    // Isso � para o caso do estilo 3D.
	// Ou para causar alguns efito em outros estilos.

    unsigned long border1;
    unsigned long border2;

    // Deslocamento em rela��o ao left da janela
    // Deslocamento em rela��o ao top da janela

    unsigned long x;    
    unsigned long y;   
    unsigned long width; 
    unsigned long height;

    // Background color.
    unsigned long color;

	//More ??
	//...

    // Next button.    
    struct button_d *Next;  
};
//Bot�es na janela principal. 
extern struct button_d *mainButton1;  
extern struct button_d *mainButton2;  
extern struct button_d *mainButton3;  
//...

/*
 * taskbar_d: 
 * Estrutura para a task bar.
 * Essa estrutura � marcador oficial das dimens�es da barra de tarefas.    
 * Essa � a barra de tarefas tradicional, aquela que normalmente fica 
 * em baixo e cont�m �cones dos programas abertos.
 * Por�m essa barra na verdade � uma janela e pode ser redimensionada 
 * ou movida.
 * O kernel ter� registro disso para salvar as dimens�es da
 * �rea de trabalho, que � o tamanho da tela menos o tamanho da barra.
 */

// #bugbug
// Lembrando que a taskbar deve ser um app.

struct taskbar_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    int used;
    int magic;
	
	//estilo de design.
	int style;

    unsigned long Left;
    unsigned long Top;
    unsigned long Width;
    unsigned long Height;
}; 
extern struct taskbar_d *TaskBar; 


/*
 * menubar_d: 
 *     Estrutura para a menu bar.
 *     Essa estrutura � marcador oficial das dimens�es
 *     da barra de menu.    
 *
 *     Essa � a barra de menu tradicional,
 *     que aparece no topo da tela e oferece
 *     um conjunto de menus para manipular
 *     o porcesso com a janela ativa.
 */

struct menubar_d
{
	object_type_t objectType;
	object_class_t objectClass;	
	
    int used;
    int magic;
	
	//estilo de design.
	int style;
	
    unsigned long Left;
    unsigned long Top;
    unsigned long Width;
    unsigned long Height;
}; 
extern struct menubar_d *MenuBar; 


/*
 * rect_d:
 *     Estrutura para gerenciamento de ret�ngulos.
 *     Um ret�ngulo pertence � uma janela.
 */
// #todo
// Usar isso para lidar com dirty rectangles.
struct rect_d 
{
    object_type_t  objectType;
    object_class_t objectClass;
    int used;
    int magic;

    int flag;

    // Estilo de design
    int style;

    //int focus;
    //int dirty;

    unsigned long x;
    unsigned long y;
    unsigned long cx;
    unsigned long cy;

    unsigned long left;
    unsigned long top;
    unsigned long width;
    unsigned long height;

    unsigned long right;
    unsigned long bottom;

    unsigned long bg_color; 

    struct rect_d *next;
};


// Isso pode ser �til principalmente
// para passar um ret�ngulo de um ambiente para outro.
// � muito mais did�tico que a figura do ret�ngulo como objeto.
struct surface_d
{
    int used;
    int magic;
    int dirty;
    struct rect_d *rect;
    
    struct surface_d *next;
};


struct tagRGBA
{
    object_type_t  objectType;
    object_class_t objectClass;

   char red;
   char green;
   char blue;
   char alpha;
};
//struct tagRGBA *RGBA;


	//
	// Window Class support.
	//

// ?? rever. 
// Enumerando classe de janela 
typedef enum {
    WindowClassNull,
    WindowClassClient,    // 1 cliente
    WindowClassKernel,    // 2 kernel
    WindowClassServer,    // 3 servidor
}wc_t;



//classes de janelas controladas pelos aplicativos.
typedef enum {
    WindowClassApplicationWindow,	
	//...
}client_window_classes_t;


//??bugbug: t� errado.
//classes de janelas controladas exclusivamente pelo kernel.
typedef enum {
    WindowClassKernelWindow,    //janelas criadas pelo kernel ... coma a "tela azul da morte"
    WindowClassTerminal,  //janela de terminal usada pelos aplicativos que n�o criam janela e gerenciada pelo kernel	
    WindowClassButton,
    WindowClassComboBox,
    WindowClassEditBox,
    WindowClassListBox,
    WindowClassScrollBar,
    WindowClassMessageOnly, //essa janela n�o � vis�vel, serve apenas para troca de mensagens ...
    WindowClassMenu,
    WindowClassDesktopWindow,
    WindowClassDialogBox,
    WindowClassMessageBox,
    WindowClassTaskSwitchWindow,
    WindowClassIcons,
    WindowClassControl,   //??
    WindowClassDialog,
    WindowClassInfo,
    //...	
}kernel_window_classes_t;


//classes de janelas controladas pelos servidores.
typedef enum {
    WindowClassServerWindow,
    //...	
}server_window_classes_t;



//estrutura para window class
struct window_class_d
{
	
	//Que tipo de window class.
	// do sistema, dos processos ...
    //tipo de classe.
	
	wc_t windowClass; 

	//1
    client_window_classes_t	clientClass;
	//2
	kernel_window_classes_t	kernelClass;
	//3
	server_window_classes_t	serverClass;
	
	//Endere�o do procedimento de janela.
	//(eip da thread primcipal do app)
	unsigned long procedure;
    //...
};


// Single message struct model.
struct msg_d 
{
    int used;
    int magic;
    
    struct window_d *window;
    int msg;
    unsigned long long1;
    unsigned long long2;
};


/*
 * window_d:
 *     Window - n�vel 1. 
 *     Estrutura para janelas.
 * terminal:
 *     Toda estrutura de janela poder� ter apenas 
 * um terminal.
 *     Colocar um terminal dentro da estrutura de janela 
 * n�o impede o sistema de ter as estruturas tradicionais 
 * de terminal, por�m pode trazer algumas vantagens na hora 
 * da manipula��o do ret�ngulo que compreende tanto a tela
 * do terminal quanto a �rea de cliente da janela.
 *    Por�m um terminal pode ser full screen e n�o 
 * pertencer a uma janela. Para isso ele considera apenas 
 * as dimens�es da tela. Nesse caso o terminal seria 
 * gerenciado por uma estrutura tradicional de terminal.
 *
 */

// #todo
// Cada janela deve especificar qual � o tipo de
// ponteiro de mouse que ela quer usar. Ent�o esse deve ser
// o ponteiro usado enquanto o mouse estiver sobre essa janela.

struct window_d
{
    object_type_t   objectType;
    object_class_t  objectClass;

    struct object_d *object;

    int used;
    int magic;

    // #todo
    // Change to 'int'
    unsigned long id;    //Window Id. 

    char *name;          //Window name.
    unsigned long type;  //tipo ... (editbox, normal, ...)  style???


    // Created by this thread.
    // This is valid for overlapped windows 
    // created by applications.
    // When the kernel creates primitives just like the root window,
    // so this window will receive the number -1.

    int tid;

	// Caracter�sticas dessa janela..

	//Estado: (Full,Maximized,Minimized...)
    int view; 

    // Background color.
    unsigned long bg_color; 

	//dimens�es e margens.
	
	//#bugbug 
	//Esses conceitos est�o sob revis�o.
	//Estou aprendendo ...

	//+margem � o deslocamento at� encontrar a borda.
	//+padding � o deslocamento entre a borda e a janela.

    unsigned long left;        //margem esquerda 
    unsigned long top;         //margem superior
    unsigned long right;       //margem direita  
    unsigned long bottom;      //margem inferior  

    unsigned long width;
    unsigned long height;

	// ??
	// Deslocamento dentro da janela?
    unsigned long x;           //deslocamento x
    unsigned long y;           //deslocamento y 

    int z;                     // z order.
    
    //invalidadas.
    //indica que precisamos repintar essa quando
    //chamarmos a rotina redraw_windows ou redraw_screen
    //See wm.c
    // #todo: Dever�amos usar a flag 'dirty' ao inv�s dessa.
    
    int dirty;

//==================================================

    // Alertartando que exite uma mensagem para essa janela.
    int msgAlert;  

    //?? rever
    int sendOffset;
    int receiveOffset;

	//Filas para uma janela receber mensagens.
	//S�o os quatro argumentos de um procedimento de janela padr�o.

	//
	// CURRENT MESSAGE !!!
	// 

	//shared by producer and consumer 
    struct window_d *msg_window;  //arg1.
    int msg;                      //arg2.
    unsigned long long1;          //arg3.
    unsigned long long2;          //arg4.

    //O aplicativo depois de pegar os 4 elementos, autoriza o 
    //kernel a colocar uma nova mensagem.
    //'0' indica que n�o temos uma mensagem v�lida.
    //'1' indica que temos uma nova mensagem.
    int newmessageFlag;

    // MESSAGE QUEUE !!!
    //shared by producer and consumer
    unsigned long hwndList[32];
    unsigned long msgList[32];
    unsigned long long1List[32];
    unsigned long long2List[32];

    //struct msg_d *msg;

	// procedure support. 
	//(poderia ser um argumento ou elemento da classe.)
    unsigned long procedure;               //procedimento da janela
    struct window_procedure_d *wProcedure; //procedure struct

//==================================================

//
// Active?
// 

    // #bugbug: See the flag 'status'
    //unsigned long status;              //ATIVA OU N�O.

    //FAST FLAG. Essa ser� a flag de ativa ou n�o. (decidindo isso)
    int active; 

//
// Focus
//

    // Se tem o foco de entrada ou n�o.
    int focus; 
//==================================================

//
// Cursor
//

    // Cursor
    // #remember: 
    // We want to use the cursor structure.
    // We are using the current console structure.

    // Cursor position inside the window in chars.
    unsigned long CursorX;
    unsigned long CursorY;

    // #maybe
    //unsigned long CursorXInPixels;
    //unsigned long CursorYInPixels;

    unsigned long CursorColor;
    //int CursorIconIndex;
    //unsigned long CursorIconAddress;
    // ...

//
// Mouse pointer
//

    // #todo
    // The mouse pointer type.
    // The address of the pointer.
    // The position inside the window.
    // Cursor and pointer are not the same thing.

    // unsigned long mouse_pointer_icon_address;
    //unsigned long mouse_pointer_x_pixel;
    //unsigned long mouse_pointer_y_pixel;

//===============================================

	// Bars support.
	// Cada tipo de janela tem seus itens espec�ficos.
	// Esses s�o os status dos �tens. Se eles est�o presentes ou n�o.

    int backgroundUsed;
    int shadowUsed;
    int titlebarUsed;
    int menubarUsed; 
    int toolbarUsed;
    int clientAreaUsed;
    int statusbarUsed;
    int minimizebuttonUsed;
    int maximizebuttonUsed;
    int closebuttonUsed;
    int borderUsed;
	// ...

//==================================================

	// Buffer.
	// DedicatedBuffer
	// DedicatedBuffer --> LFB.
	// Endere�o de mem�ria onde a janela foi pintada.
	// Obs: Toda janela deve ter seu pr�prio buffer de pintura para poder 
	// passar a janela direto de seu pr�prio buffer para o LFB, sem passar 
	// pelo Backbuffer.

    void *DedicatedBuffer;  // Qual buffer dedicado a janela usa.
    void *BackBuffer;       // Qual backbuffer a janela usa.
    void *FrontBuffer;      // Qual frontbuffer a janela usa. (LFB).


//==================================================
    // Window Class
    struct window_class_d *window_class;
//==================================================

//==================================================
// Desktop
    struct desktop_d  *desktop;

//==================================================

//
// == Windows ========
//

// Parent
    struct window_d  *parent;

//
// Childs
//

    // Se cada janela apontar para uma child, ent�o temos uma lista.
    // Child support.
    struct window_d *childListHead;  //Lista encadeada de janelas filhas.
    int childCount;                  //Tamanho da lista.

    struct window_d *child;

    //Configuramos isso quando efetuamos um raise_window
    //colocando a janela acima das outras.
    struct window_d *child_with_focus; 

//==================================================

//
// Client window and client rectangle.
//
    // Client window support.
    // � a janela propriamente dita, 
    // excluindo a moldura e a barra de rolagem.
    // Tudo o que h� dentro da janela menos o frame.
    // � a parte que � exibida quando a janela est� em full screen.

    struct window_d  *client_window; 
    struct rect_d    *rcClient; 

    // Cor do ret�ngulo da �rea do cliente.
    unsigned long clientrect_bg_color; 

//==================================================

    // We don't need menubar in this environment.
    //struct window_d  *menubar;

//
// Tool bar
//

    // Main toolbar.
    // That one below menubar.
    // How many toolbars a widnow can have in kgws?

    struct window_d  *toolbar;

// Status bar
    struct window_d  *statusbar;

//==================================================

//
// Terminal
//

    // #todo
    // Estrutura tty deve ser uma coisa associada ao uso de terminal.
    // ID da tty usada.
 
    int tty_id;


    // TERMINAL SUPPORT
    // Obs: 
    // Essas vari�veis s� ser�o inicializadas se o 
    // aplicativo decidir que conter� um terminal em sua janela.
    // Um aplicativo s� poder� ter um terminal dentro de cada janela.
    // Ou seja, se um aplicativo quiser ter mais de um terminal virtual, 
    // vai precisar de uma janela para cada terminal dentro do aplicativo.
    // isso permite facilmente que um mesmo aplicativo rode v�rios
    // programas, um em cada aba.
    // Ao inv�s de criar um frame para cada aplicativo que rode em terminal,
    // � s� criar uma nova aba no gerenciador de terminais virtuais ...
    // esse gerenciador de terminais virtuais poderia ser o shell.bin

	//flags

	//configura o status do terminal dentro da janela
    int terminal_used;     //Se � um terminal ou n�o.
	
	//validade e reusabilidade das vari�veis de terminal 
	//dentro da estrutura de janela.	
    int terminal_magic;
	
	//tab
	//n�mero da tab.
	//indica qual tab o terminal est� usando.
	//@todo:
	// Criar uma forma de contar as tabs de terminal 
	// dentro do gerenciador de terminais.
    int terminal_tab; // em qual tab do gerenciador de terminais est� o terminal.
	
	//rect
    unsigned long terminal_left;
    unsigned long terminal_top;
    unsigned long terminal_width;
    unsigned long terminal_height;

    unsigned long terminal_right;
    unsigned long terminal_bottom;

	//...

    // #todo: isso deve pertencer a uma janela.
    // se uma janela tiver o foco de entrada e for um terminal 
    // a disciplica de linhas poder� usar essas carcter�stica do terminal.
    // See: terminal.h

    struct terminal_d  *wTerminal;

//==================================================

    // style: 
    // Isso poderia ser estilo de design ...
    // Qualquer janela pode ter v�rios estilos de design 
    // ex: um editbox poder� ser de v�rios estilos.	

	//window style:
	//WINDOW_STYLE_FLOATING (flutuante) 
	//WINDOW_STYLE_DOCKING   (atracada em algum canto)

    int style;

//==================================================

	//full screen mode = modo tela cheia. 
	//( utiliza a resolu��o atual do dispositivo )
	// deve ser a janela em primeiro plano. acima de todas as outras.
	//mas podemos configurar para que uma jenela esteja em full screen 
	//enquanto outra janela � a janela ativa e ainda outra tenha o foco de entrada.
	//uma janela em modo full screen pode conter barras de rolagem.
	//embedded mode = dentro de uma janela ou de um navegador. 

//==================================================    

    // Seu estatus de relacionamento com outras janelas.
    unsigned long relationship_status;   

//==================================================    

	//ordem na pilha de janelas do eixo z.
	//A janela mais ao topo � a janela foreground.
    //int zIndex;    

	//z-order global.
	//Sua ordem em rela��o a janela gui->main.    
    //struct zorder_d *zorder;

//==================================================    

    //Qual buffer dedicado a janela usa.
    //void *buffer;        

//==================================================    

	//?? Se mudar para Rect pode deletar alguns elementos acima
	//como x, y, width ...
    struct rect_d *rcWindow;

	//Lista encadeada dos ret�ngulos que pertencem a essa janela.
	//Quando uma janela for deletada, devemos desalocar toda a mem�ria 
	//uada por esses recursos.
    struct rect_d *rectList;

//==================================================    

	//
	// CLists
	//

	// Um ponteiro para um array de ponteiros de estruturas de linhas
	// Explicando: 
	// Nesse endere�o teremos um array. Cada ponteiro armazenado
	// nesse array � um ponteiro para uma estrutura de linha.
	// Obs: 
	// #todo: 
	// Todos esses elementos podem formar uma estrutura e ficaria aqui 
	// apenas um ponteiro para ela.

    void *LineArray;
    int LineArrayIndexTotal;    //Total de �ndices presentes nesse array.
    int LineArrayIndexMax;      //N�mero m�ximo de �ndices permitidos no array de linhas.
    int LineArrayTopLineIndex;  //Indice para a linha que ficar� no topo da p�gina.
    int LineArrayPointerX;      //Em qual linha o ponteiro est�. 	
    int LineArrayPointerY;      //em qual coluna o ponteiro est�.
	//...

//==================================================    

	//thread de controle
	//Usada para input de mensagens e sinais.
    struct thread_d *control;

//==================================================    

    //  A que processo a janela pertence??
    struct process_d *process;

//==================================================    

	//
	// Menus support.
	//

	//?? Qual janela o menu usar�.
    struct window_d *menu_window;   //Menu Window.

    struct menu_d *sysMenu;         //menu de sistema.(control menu)
    struct menu_d *barMenu;         //menu da barra de menu.
    struct menu_d *defaultMenu;     //menu da janela (*importante)
	//...

    int selected;     //sele��o  de item de menu.

//==================================================    

    // This window is a ...

    int isMenu;
    int isMenuItem;
    int isControl;
    int isButton;
    int isEditBox;
    int isCheckBox;
    int isIcon;
    // ...

//==================================================    

	// Se a janela for do tipo bot�o, ent�o essa ser� a 
	// estrutura para o gerenciamento do bot�o.
    struct button_d *button;
    
//==================================================    

    // ??
    const char *text; 

//==================================================    

    // Controls

    struct window_d  *minimize;
    struct window_d  *maximize;
    struct window_d  *close;
    int isMinimize;
    int isMaximize;
    int isClose;

//==================================================    

    // Qual janela � um �cone para essa janela.
    // Por exemplo, o �cone que fica na �rea de trabalho.
    struct window_d *icon;

//==================================================    

    //
    // Actions.
    //

    int draw; 
    int redraw;
    int show;   //se precisa ou n�o mostrar a janela.	
    // Continua ...

//==================================================    

	// Text Cursor support.
	// fica para uma vers�o estendida da estrutura.
	// Estrutura de cursor para a janela.
    struct cursor_d *cursor;

//==================================================    

	//unsigned long bgcolor;		// Background color.
	//unsigned long fgcolor;		// Foreground color. 

//==================================================    

    struct button_d *current_button;  //Bot�o atual.      
    struct button_d *buttonList;      //Lista encadeada de bot�es em uma janela.

//==================================================    

	// ??
	// Status do puxador da janela.
	// Se est� aberta ou n�o.
	// HANDLE_STATUS_OPEN ou HANDLE_STATUS_CLOSE
	int handle_status;

//==================================================
    // Trava. 
    // Se travada, n�o pode mudar nada.
    // Podemos travar a janela m�e quando 
    // estamos criando uma janela filha.
    // Enables or disables mouse and keyboard input to the 
    // specified window or control.

    int locked; 

//==================================================

    //
    // Terminal.
    //
    
    int isTerminal;
    struct vt_d *terminal;

    // Navigation.
    struct window_d *prev; 
    struct window_d *next; 
};

extern struct window_d *CurrentWindow;    //Janela atual
extern struct window_d *ActiveWindow;     //Janela atual.
extern struct window_d *WindowWithFocus;  //Janela com o foco de entrada.   
//...

// Lista encadeada de janelas.
extern struct window_d *window_Conductor2;
extern struct window_d *window_Conductor;
extern struct window_d *window_rootConductor;
//...

// see: kgws.c
// Window list.
extern unsigned long windowList[WINDOW_COUNT_MAX];


// ===================================

extern struct window_d *FULLSCREEN_TABWINDOW;   



//
// z order support
//

//#define ZORDER_COUNT_MAX  128  //??PROVIS�RIO   

extern int zorder;

//esses tipo indicam algum posicionamento dentro da xorder.
typedef enum {
	zordertypeNull,     //ignorado
    zordertypeTop,      //acima de todas
    zordertypeBottom,   //abaixo de rodas.
    //...	
}zorder_type_t;



//essas s�o as camadas onde os objetos gr�ficos ficam ...
//est�o associadas com formul�rios e containers.
typedef enum {
	zorderlayerNull,     //ignorado
    zorderlayerBack,     //back layer. � a �rea onde os m�todos invocar�o a constru��o de objetos gr�ficos.
    zorderlayerMiddle,   //middle layer. � onde os objetos gr�ficos e as etiquetas de controle s�o colocadas.
	zorderlayerFront,    //front layer. s�o colocados os controles n�o gr�ficos como: 
	                     //CommandButton, CheckBox e ListBox 
    //...	
}zorder_layer_t;

extern int zorderCounter;         //contador de janelas incluidas nessa lista.   
extern int zorderTopWindow;
//...

//
//Estrutura para controlar um �ndice de janela 
//ponteiros de inst�ncias dessa estrutura ficar�o na lista zorderList[].
// Obs: uma estrutura de janela pode ter um poteiro para essa 
// estrutura que controlar� todas as propriedades de zorder relaticas a aquela janela.
//
struct zorder_d
{
	// tipo ... top ou bottom.
	//encontraremos com facilidade se ela � top ou bottom.
	
	//zorder_type_t zorderType; 
	//zorder_layer_t zorderLayer;
	
	int zIndex;
    
	//?? ...
	
    struct window_d *window;
	
	//toda janela est� na lista de zorder de outra janela.
	struct window_d *parent; //janela m�e... 
	
	struct zorder_d *next;
};

/*
 * zorderList[] support.
 *     Sobreposi��o de janelas.    
 *     ?? Precisamos reorganizar a lista ??
 *     ?? seria melhor uma lista encadeada ??
 *     ??e quando fecharem uma janela no meio da lista ??
 *
 *  >> Quando criamos uma janela ela � inclu�da no primeiro lugar vago da lista.
 *  >> quando deletamos uma janela, apenas excluimos ela da lista, n�o precisamos reorganizar.
 *  >> uma janelas minimizada � excluida dessa lista, � zerada z_axis_order na sua estrutura.
 *  >> repintaremos come�ando do zero.
 */ 
//unsigned long zorderList[ZORDER_COUNT_MAX];


//
// Backbuffer support. (espelho da mem�ria de video)
//

struct backbufferinfo_d
{
	//@todo: object support

    int used;
    int magic;
	
    unsigned long start;
    unsigned long end;
    unsigned long size;
    //...

    //@todo:
	// ?? O que nos podemos ter aqui ??	
	// terminal., window, line disciplice, cursor ...
	//input buffer? z-order ??
};
extern struct backbufferinfo_d *BackBufferInfo;

//
// Frontbuffer support. (mem�ria de v�deo)
//

struct frontbufferinfo_d
{
	//@todo: object support
	
	int used;
	int magic;
	
    unsigned long start;
    unsigned long end;
    unsigned long size;
	
	unsigned long width;
    unsigned long height;
	unsigned long bpp;
	//
	
    //@todo:
	// ?? O que nos podemos ter aqui ??	
	// terminal., window, line disciplice, cursor ...	
};
extern struct frontbufferinfo_d *FrontBufferInfo;

/*
 * gui:
 *     N�vel 0 
 *     ## gui  ##
 * Obs: Foi inclu�do aqui os ponteiros para as janelas principais usadas nos 
 * principais recursos gr�ficos, como control menu do desktop por exemplo.
 *
 * Hist�rico: 
 * 2015 - Created.
 * 2016 - inclu�ndo novos elementos.
 * ...
 */

// #bugbug
// Muita coisa nessa estrutura precis ser revista.
// Tendo em vista que ela apenas contempla o kgws
// como provedor de recursos gr�ficos.
// Dessa forma essa estrutura s� faz sentido no ambiente 
// de setup, que usa o kgws.

struct gui_d
{
    // Se a gui est� ou n�o inicializada.
    int initialised;
    // Procedimento da janela ativa.
    unsigned long procedure;  

    // #bugbug
    // precisamos de estrutura de device context,
    // onde teremos informa��es sobre o hardware
    // respons�vel pelos recursos gr�ficos.

    // BUFFERS
    // Ponteiros para os principais buffers usados pelo sistema.

    // LFB:
    // O endere�o do in�cio da mem�ria de v�deo do cart�o de mem�ria.
    // obs: Quantos desses ponteiros precisamos dentro da mem�ria de
    // v�deo? E se tivermos v�rias placas de mem�ria de v�deo, seria
    // um lfb para cada placa?
    // Esse valor foi configurado pelo BIOS pelo metodo VESA.

    unsigned long lfb;
 
    // Backbuffer
    // O Backbuffer pe o buffer para colocar a imagem de pano de fundo.
    // Ele ser� o buffer dedicado da janela principal gui->main. 

	// #importante.
	// Um backbuffer pode cobrir a �rea de v�rios monitores.
	// O conceito de backbuffer pode estar relacionado com o conceito de room,
	// (window station), com v�rios desktops e monitores.

    unsigned long backbuffer;

    void *backbuffer1; 
    void *backbuffer2; 
    void *backbuffer3;
    // ...


	/*
	 * Default dedicated buffers.
	 *     Esses ponteiros podem ser usados para aloca
	 * mem�ria para buffer dedicado antes mesmo de se criar a estrutura
	 * da janela.
	 * Obs: Toda janela tem que ter um buffer dedicado, onde ela ser� pintada.
	 * Depois de pintada ela pertencer� a uma lista de janelas que ser�o
	 * enviadas para o LFB seguindo a ordem da lista.
	 */
	
	//void* defaultWindowDedicatedBuffer1;
	//void* defaultWindowDedicatedBuffer2;
	//void* defaultWindowDedicatedBuffer3;
    //...	


    // redraw
    // Flag para repintar todas as janelas.
    // #todo: #bugbug, Isso parece estranho. Cada janela
    // est� pintada em seu buffer dedicado e fica por conta de
    // cada janela decidir se repinta ou n�o apenas ela.

    int redraw;


    // refresh
    // Flag para enviar do backbuffer para a mem�ria de video.
    // Seguindo uma lista linkada, copiaremos o conte�do do buffer
    // dedicado de cada janela da lista no LFB. Primeiro � Backbuffer
    // que � o buffer da janela principal, que funcionar� como
    // Head da lista.

    int refresh;


    // status das janelas usadas pelo sistema.
	int screenStatus;
	int backgroundStatus;
	int logoStatus;
	int mainStatus;
	int navigationbarStatus;
	int menuStatus;
	int taskbarStatus;
	int statusbarStatus;
	int infoboxStatus;
	int messageboxStatus;
	int debugStatus;
	int gridStatus;

	/*
	 *    ****    Windows    ****
	 *
	 * Obs: Ponteiros para as janelas principais usadas na interf�ce
	 * gr�fica. Essas janelas n�o dependem dos processos e sim os
	 * processos dependem delas. Os processos do sistema poder�o recriar
	 * essas janelas e registrar seus ponteiros aqui. Por exemplo, o control
	 * menu pode sofrer altera��es e depois registrar o ponteiro aqui.
	 * Outro exemplo � o control menu da janela ativa, toda vez que
	 * trocar a janela ativa, deve-se registrar o ponteiro do control menu
	 * da janela aqui, para f�cil acesso.
	 *
	 * Os ponteiros aqui ser�o organizados em grupos:
	 * ==============================================
	 * Screen - root window
	 * Grupo 0: Background, Logo, Desktop, Taskbar.
	 * Grupo 1: Main (Full Screen), Status Bar. 
	 * Grupo 2: Grid. (grid de �cones flutuantes)
	 * Grupo 3: Control menu.(Control menu da janel atual).
	 * Grupo 4: Info Box, ToolTip.
	 * Grupo 5: ??
	 * Grupo 6: Outras.
	 */

    // #bugbug
    // All this are pointing to the root window.

    struct window_d  *screen; 
    struct window_d  *root_window; 
    struct window_d  *background; 

    // The logo used in the initialization.
    struct window_d *logo;

    // Dividing the screen in parts:
    struct window_d *main;      // �rea de trabalho.
    struct window_d *taskbar;   // Barra de tarefas.

 
	//
	// Grupo 2: Grid. 
	//

	/*
	 *Grid:
	 *   (�rea para colocar o grid de �cones).
	 *    �rea din�mica dentro da �rea de trabalho.
	 *    Essa �rea de grid pode ser reposicionada
	 *    de acordo com o layout escolhido.
	 */

    struct window_d  *grid;

	//
	// Grupo 3: Control menu.
	//
	
    /*
	 * Menu:  
	 *     Ponteiro para a estrutura do control menu atual.    
	 *     Isso depende da janela ativa e da janela com o foco de entrada.
	 *     Esse ser� o ponteiro para o control menu que dever� ser aberto.
	 *     Varia conforme muda a janela com o foco de entrada.
	 */

    struct window_d *menu; 

    struct window_d  *notification;

    struct window_d  *infobox;
    struct window_d  *tooltip;

    struct window_d  *messagebox;
    struct window_d  *dialogbox;


	//
	// Grupo 6: Outras.
	//
	
	
	//Debug: Janela usada pelo Kernel para mensagens de erro.
    // struct window_d *debug;   

    //Menu bar.
	struct window_d *mbhWindow;       //Janela principal da menu bar.
	struct menu_d *mb;               //a menu bar � um menu
	struct menu_d *mbControlPanel;   //Painel de controle
	struct menu_d *mbComputer;       //Meu computador(discos, diretorios ...)
	struct menu_d *mbFile;           //File manager. (abre e fecha arquivos)
	struct menu_d *mbWindow;         //Window manager (igual sistem menu) 
    //...	
	
	//
	//   **** BARs   ****
	//
	
	
	// Qualquer dessas barras ser�o gerenciadas pelo kernel ...
	// n�p fazem parate de um aplicativo, Por�m o aplicativo gerenciador
	// de arquivos (explorer) ser� o respons�vel pela barra de tarefas que ser� 
	// usada pelo usu�rio.
	// Essas barras abaixo tem a finalidade de dar alguma navegabilidade
	// mesmo sem algum programa de gerenciamento de arquivos.
	// E tamb�m n�o h� problemas em os dois conviverem.

	//TopBar.
	struct window_d *topbar;	
	struct menu_d *logonMenu;         //Logon
	struct menu_d *logoffMenu;	      //Logoff 

    //Navigation Bar.
    struct window_d *navigationbar;	
    struct menu_d *desktopMenu;       //Desktop 
    struct menu_d *setupMenu;         //Ambiente de configura��o.

	//Current Menu.
	//Aponta para a estrutura do menu atual.
	//Seja ele de qual tipo for.
    struct menu_d *currentMenu;       //Current. Para outros ambiente.


    // #todo
    // Check this structure.
    // Where is it defined?

    //Informa��es sobre a tela.
    struct screen_d *ScreenInfo;

	// Backbuffer support. (espelho da mem�ria de video)
	struct backbufferinfo_d  *backbufferInfo;  
	
	// Frontbuffer support. (mem�ria de v�deo)
	struct frontbufferinfo_d *frontbufferInfo; 

//
// Security
//

    struct usession_d  *CurrentUserSession;
    struct room_d      *CurrentRoom;
    struct desktop_d   *CurrentDesktop;

//
// User info.
//

    struct user_info_d *User; 

    //...
};

// kgws.c
// #importante
// Estrutura global. 
// (Usada para passar estutura entre fun��es)
// Primeira e �nica. 
extern struct gui_d  *gui; 


//
// == Prototypes ===============================================
//


/*
 * SetGuiParameters:
 *     Configura a inicializa��o das janelas gerenciadas pelo kernel.
 *     @todo: Limite de janelas (+- 10)
 */

void 
SetGuiParameters ( 
    int refresh, 
    int screen,
    int background, 
    int logo, 
    int taskbar, 
    int main, 
    int menu,
    int infobox, 
    int messagebox,  
    int debug, 
    int navigationbar, 
    int grid );


//
// Bars support. (menubar)
//

int 
UpdateStatusBar ( 
    struct window_d *window, 
    unsigned char *string1, 
    unsigned char *string2 );


struct window_d *StatusBar ( 
    struct window_d *window, 
    unsigned char *string1, 
    unsigned char *string2 );


struct window_d *ToolBar ( struct window_d *window );


//
// menubar
//

void *create_menubar (struct window_d *pwindow); 

int 
create_menubar_item (
    struct menu_d *menu, 
    unsigned char *string, 
    int status );

int 
draw_menubar_item ( 
    struct window_d *window, 
    unsigned char *string );

//int select_menubar_item(struct menuitem_d *menuitem);


int kgws_create_menubar (struct window_d *window);


// Color.
void set_up_color(unsigned long color);


void 
set_up_text_color ( 
    unsigned char forecolor, 
    unsigned char backcolor );


void 
update_button (  
    struct button_d *button,
    unsigned char *string,
    int style,
    int state,
    int type,
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color );


void *draw_button ( 
    unsigned char *string,
    int style,
    int state,
    int type, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color );


int redraw_button ( struct button_d *button );

int button_down ( struct window_d *window );

int button_up ( struct window_d *window );



// Focus support.


void kgwmSetFocus ( struct window_d *window );

void *kgwmGetFocus (void); 

void kgwmKillFocus ( struct window_d *window );


// service 301
int kgwm_next(void);


//foreground window support

void *windowGetForegroundWindow (void);

int windowSetForegroundWindow(struct window_d *window);

//parent.
void *GetParentWindow(struct window_d *hwnd);

//desktop
void *GetWindowDesktop(struct window_d *hwnd);


// pegando ponteiros para estrutura de janela na estrutura 'gui->'.
// kgws.c

void *guiGetScreenWindow (void);

void *guiGetDeveloperScreenWindow (void);

void *guiGetBackgroundWindow (void);

void *guiGetLogoWindow (void);

void *guiGetDesktopWindow (void);

void *guiGetTaskbarWindow (void);

void *guiGetMainWindow (void);

void *guiGetStatusbarWindow (void);

void *guiGetGridWindow (void);

void *guiGetMenuWindow (void);

void *guiGetInfoboxWindow (void);

void *guiGetTooltipWindow (void);

void *guiGetMessageboxWindow (void);

void *guiGetDialogboxWindow (void);

void *guiGetDebugWindow (void);

// ?
void *guiGetMbhWindowWindow (void);

void *guiGetTopbarWindow (void);

void *guiGetNavigationbarWindow (void);

void *guiGetShellWindowWindow (void);

void *guiGetShellClientWindowWindow (void);



// Background support.
void bg_load_image (void);
void backgroundDraw(unsigned long color);
void backgroundSetColor(unsigned long color);
void backgroundRedraw(unsigned long color);
void backgroundBackground (void);    

// Not good
int backgroundInit (void);


int Background_initialize(void);


//
// Char and String support.
//

void 
draw_string ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned char *string );


void 
draw_text ( 
    struct window_d *window,
    unsigned long x,  
    unsigned long y,  
    unsigned long color, 
    unsigned char *string );


void 
my_buffer_char_blt ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c);


void set_char_width( int width );
void set_char_height( int height );


int get_char_width (void);
int get_char_height (void);





// desenha um caractere transparente.
void 
d_drawchar_transparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c);


// desenha um caractere.
void 
d_draw_char ( 
    unsigned long x, 
    unsigned long y,  
    unsigned long c,
    unsigned long fgcolor,
    unsigned long bgcolor);
 
 

//
// Pixel, line rect support.
//

//pega um pixel no backbuffer
unsigned long get_pixel( unsigned long x,  unsigned long y );


//envia um pixel do backbuffer para o frontbuffer
void refresh_pixel( unsigned long x,  unsigned long y );


void 
refresh_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2 );
  


// envia um ret�ngulo do backbuffer para o frontbuffer
void 
refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//envia um ret�ngulo de um buffer para outro.
void 
refresh_rectangle2 ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    unsigned long buffer1,
    unsigned long buffer2 );


//
// ## salvando ret�ngulos ##
//

//a ideia � salvar os bytes usados por um ret�ngulo que est� no backbuffer 
//em um buffer do tamanho do ret�ngulo.
//um buffer cosntante, suficientemente grande para salvar um ret�ngulo do tamanho da 
//tela ser� alocado e gerenciado por uma estrutura.
//essa estrutura dever� registrar as dimens�es e posicionamento do ret�ngulo,
//e tamab�m controlar o fluxo do transmiss�o do ret�ngulo do backbuffer para esse buffer 
//e de volta para o backbuffer.
//isso ser� usado nas opera��es de movimenta��o de janela.
//m�ltiplos buffers poder�os ser usados no futuro. Principalmente para gerar eleito.

struct saved_rect_d
{
    void *buffer_address;

    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;

    int pixels;  //quantidade de pixels.
    int bytes;   //quantidade de bytes.
    int bpp;     //bytes per pixel.
	
	// O buffer est� cheio. 
	// 1 ret�ngulo foi salvo nele.

    int full; 
};
extern struct saved_rect_d *SavedRect;


// ==================================


int initialize_saved_rect (void);

// #testando ...
// Salvar um ret�ngulo no buffer ser� semelhante ao 
// m�todo de salvar um bmp em um arquivo.

int 
save_rect ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//pintar no backbuffer o ret�ngulo salvo vai ser semelhante ao processo 
//de decodificar um bmp, copiando do arquivo para o backbuffer.
// esses argumentos devem representar o posicionamentod esejado do 
//ret�ngulo no backbuffer.

int 
show_saved_rect ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//#todo: deprecated.
void scroll_screen_rect (void);


// Pinta um pixel em um buffer de janela.
void 
pixelPutPixelWindowBuffer ( 
    void *buffer, 
    unsigned long x, 
    unsigned long y, 
    unsigned long color );


  
/*
 * pixelPutPixelDedicatedWindowBuffer:
 *     Coloca um pixel no buffer da janela.
 *     Serve para pintar janelas que ir�o direto do seu buffer para 
 * o LFB da mem�ria de v�deo, sem passar pelo back buffer. (OVERLAPPED)
 */

void 
pixelPutPixelDedicatedWindowBuffer ( 
    struct window_d *window, 
    unsigned long x, 
    unsigned long y, 
    unsigned long color ); 



//
// pixel
//


void 
backbuffer_putpixel( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx );


void 
lfb_putpixel ( 
unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx );

//
// line
//
 
void 
my_buffer_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2,  
    unsigned long color );


// rectangle.

void 
drawDataRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color );



void *rectStrCopyMemory32 ( 
    unsigned long *dest, 
    unsigned long *src, 
    int count ); 



//
// Window support.
// 
 
int init_window_manager (void);

int init_windows (void);

int RegisterWindow (struct window_d *window);

void set_current_window (struct window_d *window);
void *get_current_window (void);

//salva o ret�ngulo de uma janela no buffer de salvamento.
//isso ser� usado para mover a janela.
int save_window (struct window_d *window);

//mostrar uma janela que tem seu ret�ngulo salvo no buffer de salvamento.
//#obs: antes de chamarmos essa fun��o podemos chamar a fun��o replace_window
//para mudar a janela de lugar.
int show_saved_window (struct window_d *window);


//mostra o ret�ngulo de uma janela que est� no backbuffer.
//tem uma janela no backbuffer e desejamos enviar ela para o frontbuffer.
int show_window_rect (struct window_d *window);


int 
resize_window ( 
    struct window_d *window, 
    unsigned long cx, 
    unsigned long cy );


int 
replace_window ( 
    struct window_d *window, 
    unsigned long x, 
    unsigned long y ); 


// coloca a janela acima das outras.
int raise_window ( struct window_d *window );

int redraw_window (struct window_d *window, unsigned long flags );

//redraw all windows.
int redraw_screen (void);                          

int is_window_full(struct window_d *window);
int is_window_maximized(struct window_d *window);
int is_window_minimized(struct window_d *window);



void *kgwmGetActiveWindow (void);
void kgwmSetActiveWindow (struct window_d *window);


void CloseWindow(struct window_d *window);

void DestroyWindow(struct window_d *window);

void CloseActiveWindow (void);

void MinimizeWindow (struct window_d *window);
void MaximizeWindow (struct window_d *window);

//
// Show
//

void windowShowWindowList (void);

void show_window_with_focus (void);

void show_active_window (void);

//
// z-order support.
//

int z_order_get_free_slot (void);

int get_zorder ( struct window_d *window );


// Pegando a o ponteiro da janela que est� 
// no topo da lista

struct window_d *getTopWindow (void);



//configurando a top window.

void set_top_window ( int id );
int get_top_window (void);

void closeActiveWindow (void);

//bloqueando e desbloqueando o foco.
void windowBlockFocus (void);
void windowUnblockFocus (void);

int windowGetMainWindowDescriptor (void);

int windowGetWindowID ( struct window_d *window);


//@todo: Criar windowRefreshScreen();

void windowSwitchFocus (void);

void windowLock (struct window_d *window);
void windowUnlock (struct window_d *window);

int windowCreateDedicatedBuffer (struct window_d *window);


// Envia mensagem para a fila da janela com foco de entrada.

void 
windowSendMessage ( 
    unsigned long arg1, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );


//
// pega uma mensagem na estrutura da janela com o foco de entrada.
//

void *windowGetHandleWindow (struct window_d *window); 
void *windowGetMessage (struct window_d *window);
void *windowGetLong1 (struct window_d *window);
void *windowGetLong2 (struct window_d *window);


// Mostra o buffer de mensagens da janela com foco de entrada.

void windowShowWWFMessageBuffers (void); 


//color support.
int windowInitializeColorSchemeSupport (void);
int windowSelectColorScheme ( int type );


void 
guiSetUpMainWindow ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//
// timer
//

int windowKillTimer ( struct window_d *window, int id );

 
//janela
//id do timer
//tempo(medida indefinida ainda)
int
windowSetTimer ( 
    struct window_d *window, 
    int id, 
    int time );



// Escaneia as janelas existentes procurando uma 
// que contenha o posicionamento do cursor.
int windowScan ( unsigned long x, unsigned long y );

int windowOverLappedScan ( unsigned long x, unsigned long y );

//Envia uma mensagem PAINT para o aplicativo atualizar a �rea de trabalho.
void windowUpdateWindow ( struct window_d *window );



//faz a janela atual entrar ou sair do modo fullscreen.
int windowSwitchFullScreen (void);


int DrawIcon ( struct window_d *window, int n );

int 
DrawTitleBar ( 
    struct window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style,
    char *string );


int 
DrawFrame ( 
    struct window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style );


/*
 **********************************************
 * CreateWindow:
 *     Cria uma janela com base em um tipo.
 */

void *CreateWindow ( 
    unsigned long type,         //1 - tipo de janela (popup ..normal ...)
    unsigned long status,       //2  - estado da janela (ativa ou nao)
    unsigned long view,         //3  - (min, max ...)
    char *windowname,           //4  - titulo                                
    unsigned long x,            //5  - deslocamento em rela��o �s margens do desktop(sua instancia)        
    unsigned long y,            //6  - idem
    unsigned long width,        //7  - largura da janela  
    unsigned long height,       //8  - altura
    struct window_d *pWindow,   //9  - id da janela mae, se for zero, essa � a janela mae.
    int desktop_id,              //10 - desktop ID.
    unsigned long clientcolor,  //11 - Client Area Color.
    unsigned long color         //12 - cor do bg (para janelas simples, tipo 1)
);



// #todo: 
// Talvez deletar essa fun��o e usar apenas CreateWindow.
void *kgws_create_window ( 
    unsigned long type, 
    unsigned long status, 
    unsigned long view, 
    char *windowname, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    struct window_d *pWindow, 
    int desktopid, 
    unsigned long clientcolor, 
    unsigned long color );
 

// #todo: deprecated.
int scroll_client_window ( struct window_d *window );

#endif  

//
// End.
//


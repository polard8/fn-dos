/*
 * File ws/ws.h
 *
 *     KGWS - kernel Gramado Window Server
 *
 * Esse é o principal header do gws, preferenciamente
 * devem ficar aqui as globais usadas no servidor.
 *
 * #importante:
 *     Os dados serão emcapsulados nesse servidor  
 * e serão acessíveis através de métodos.
 *     Ficarão aqui as principais globais de controle
 * dos recursos gráficos.
 *
 * Obs: Um processo vai operar como grenciador de janelas
 * em ring e vai dialogar com o servidor para obter recursos.
 * Provavelmente esse gerenciador de janelas se chamará GWM
 * Gramado Window Manager. Porém podemos ter vários gerenciadores 
 * de janela em user mode.
 *
 *
 * History:
 *     2018 - Created by Fred Nora.
 */


#ifndef __WS_H
#define __WS_H    1


// Counters.
#define USER_SESSION_COUNT_MAX  16
#define ROOM_COUNT_MAX          16
#define DESKTOP_COUNT_MAX       16

#define WINDOW_COUNT_MAX          1024 
#define MAX_WINDOWS WINDOW_COUNT_MAX 

// # video mode support #
#define VIDEO_MODE_TEXT     1
#define VIDEO_MODE_GRAPHIC  2 
 
 
// # char support # 
#define CHAR_WIDTH   8
#define CHAR_HEIGHT  8 
#define DEFAULT_CHAR_WIDTH   8
#define DEFAULT_CHAR_HEIGHT  8
//...


//
// == Colors =======================================================
// 


#define COLOR_WHITE    0xFFFFFF
#define COLOR_BLACK    0x000000
#define COLOR_RED      0xFF0000 
#define COLOR_GREEN    0x00FF00
#define COLOR_BLUE     0x0000FF
#define COLOR_GRAY     0x00808080 
#define COLOR_PINK     0x00FFC0CB
#define COLOR_ORANGE   0x00FFA500
#define COLOR_YELLOW   0x00FFFF00
// ...


// My gray scale.
#define xCOLOR_BLACK 0x000000  //preto
#define xCOLOR_GRAY1 0x202020  //cinza mais escuro
#define xCOLOR_GRAY2 0x404040  //cinza
#define xCOLOR_GRAY3 0x606060  //cinza
#define xCOLOR_GRAY4 0x808080  //cinza
#define xCOLOR_GRAY5 0xa0a0a0  //cinza
#define xCOLOR_GRAY6 0xc0c0c0  //cinza
#define xCOLOR_GRAY7 0xe0e0e0  //cinza mais clarinho
#define xCOLOR_WHITE 0xffffff  //branco  


#define HUMILITY_COLOR_BACKGROUND                0x00008080 
#define HUMILITY_COLOR_WINDOW                    0x00FFFFFF 
#define HUMILITY_COLOR_WINDOW_BACKGROUND         0x00202020 
#define HUMILITY_COLOR_ACTIVE_WINDOW_BORDER      0x00404040 
#define HUMILITY_COLOR_INACTIVE_WINDOW_BORDER    0x00606060 
#define HUMILITY_COLOR_ACTIVE_WINDOW_TITLEBAR    0x00404040 
#define HUMILITY_COLOR_INACTIVE_WINDOW_TITLEBAR  0x00606060 
#define HUMILITY_COLOR_MENUBAR                   0x00808080 
#define HUMILITY_COLOR_SCROLLBAR                 0x00FFF5EE 
#define HUMILITY_COLOR_STATUSBAR                 0x0083FCFF 
#define HUMILITY_COLOR_MESSAGEBOX                0x00404040 
#define HUMILITY_COLOR_SYSTEMFONT                0x00000000 
#define HUMILITY_COLOR_TERMINALFONT              0x00FFFFFF 
//...

#define PRIDE_COLOR_BACKGROUND                  0x00008080 
#define PRIDE_COLOR_WINDOW                      0x00FFFFFF 
#define PRIDE_COLOR_WINDOW_BACKGROUND           0x00202020 
#define PRIDE_COLOR_ACTIVE_WINDOW_BORDER        0x0080FFFF
#define PRIDE_COLOR_INACTIVE_WINDOW_BORDER      0x0080FFFF
#define PRIDE_COLOR_ACTIVE_WINDOW_TITLEBAR      0x0080FFFF
#define PRIDE_COLOR_INACTIVE_WINDOW_TITLEBAR    0x0080FFFF
#define PRIDE_COLOR_MENUBAR                     0x00808080
#define PRIDE_COLOR_SCROLLBAR                   0x00FFF5EE
#define PRIDE_COLOR_STATUSBAR                   0x002EB982
#define PRIDE_COLOR_MESSAGEBOX                  0x00808080
#define PRIDE_COLOR_SYSTEMFONT                  0x00000000
#define PRIDE_COLOR_TERMINALFONT                0x00FFFFFF
// ...

//
// ===================================================================
//



/*
 *****************************************************
 * ColorSchemeType:
 *     Enumerando os esquemas de cores. 
 *     Esses são esquemas default.
 *     Poderemos carregar outros e cada esquema terá 
 * seu índice.
 *     Esses serão sempre os primeiros.    
 */
typedef enum {
	ColorSchemeNull,      // 0 - Null.
	ColorSchemeHumility,  // 1 - Gray stuff.
	ColorSchemePride,     // 2 - Colorful.
	//...
}ColorSchemeType;



/*
 ******************************************************
 * ColorSchemeIndex:
 *     csi - color scheme index. 
 *     Enumerando os elementos gráficos
 *     O esquema de cores se aplica ao servidor 
 * de recursos gráficos. GWS.
 */
typedef enum {
	
	csiNull,                    //0
	csiDesktop,                 //1 área de trabalho.

	//window
	csiWindow,                  //2
	csiWindowBackground,        //3
	csiActiveWindowBorder,      //4
	csiInactiveWindowBorder,    //5
	                    
	//bar
	csiActiveWindowTitleBar,    //6	
	csiInactiveWindowTitleBar,  //7
	csiMenuBar,                 //8
	csiScrollBar,               //9
	csiStatusBar,               //10
	
	csiMessageBox,              //11
	csiSystemFontColor,         //12 BLACK
	csiTerminalFontColor,       //13 WHITE
	//...
	
	//@todo: focus,
	
	//@todo: Window 'shadow' (black??)
}ColorSchemeIndex;  
 
 
/*
 ***************************************************
 * color_scheme_d:
 *     Estrutura para esquema de cores. 
 *     O esquema de cores se aplica ao servidor de recursos gráficos. 
 * GWS.
 *
 */ 
struct color_scheme_d
{
    // #todo: 
    // É preciso ainda definir esse tipo de objeto.
    // definir em gdef.h

    object_type_t  objectType;
    object_class_t objectClass;

    //#todo Not initilized yet.
    int id;

    int used;
    int magic;

	//marcador de estilo de design para 
	//o padrão de cores.
	//cada estilo pode invocar por si um padrão de cores.
	//ou o padrão de cores por si pode representar um estilo.

    int style;

    char *name; 

	//cada índice desse array representará um elemento gráfico,
	//os valores no array são cores correspondentes aos elementos gráficos 
	//representados por índices.

    unsigned long elements[32];

    //...
};

// gkws.c
// #ps:
// The kernel only have two color schemes:
// Humility and Pride.
extern struct color_scheme_d *HumilityColorScheme; // Simples.
extern struct color_scheme_d *PrideColorScheme;    // Colorido.
extern struct color_scheme_d *CurrentColorScheme;

// ===============================================================


//
// # Principais variáveis globais #
//

// monitor. (hardware)
extern int current_display; 
   
// superficie.
// Um monitor pode ter varias screens
// e uma screen pode estar em mais de um monitor
extern int current_screen;      

extern int guiStatus;       //Status da Interface gráfica do usuário.


//Status de ambientes gráficos.
extern int logonStatus;              //Logon status.
extern int logoffStatus;             //Logoff status.
extern int userenvironmentStatus;    //User environment status.


//Contagens de ambientes;
extern int rooms_count;  
extern int desktops_count;
extern int windows_count;  


extern int current_window;         //gws
extern int current_menu;           //gws

//
// # Outras variáveis globais #
//

//a janela que está em full screen.
extern int fullscreen_window;
//janela ativa
extern int active_window;
//janela com foco de entrada. 
extern int window_with_focus;
//janela com o mouse em cima.(captured mouse);
extern int mouseover_window;
//Indice 0 na zorder atual.  
extern int top_window;
//edit box atual
extern int editbox_window;
//combobox atual
extern int combobox_window;
//janela atual do terminal atual.
extern int terminal_window;

// ## tests ##
//int mouseover_window;
//int current_button_window;
////cada janela tem seu controle first responder.
//int current_first responder.
//...

//
// gws fonts
//


//As fontes usadas pelo servidor gws
extern unsigned long gws_currentfont_address;  // fonte atual.
extern unsigned long g8x8fontAddress;          // 8×8, 80×25,CGA, EGA
extern unsigned long g8x14fontAddress;         // 8x14,80×25,EGA
extern unsigned long g8x16fontAddress;         // ??
extern unsigned long g9x14fontAddress;         // 9x14,80×25,MDA, Hercules
extern unsigned long g9x16fontAddress;         // 9x16,80×25,VGA
//...

extern int gfontSize;

// draw char support
extern int gcharWidth;
extern int gcharHeight;

extern unsigned long g_system_color;
extern unsigned long g_char_attrib;


// LFB - address for kernel graphic mode
extern unsigned long g_kernel_lfb; 

//video mode
extern unsigned long g_current_vm;          //video memory
extern unsigned long g_current_video_mode;  //video mode


//status do cursor.
//se ele deve aparecer e piscar ou não.
extern int g_show_text_cursor;

//status: aceso ou apagado.
//0=apaga 1=acende.
extern int textcursorStatus;      

extern unsigned long g_mousepointer_x;
extern unsigned long g_mousepointer_y;


//
// == window server ==================================================
//

// types of window server.
typedef enum {
    WindowServerTypeNull,
    WindowServerTypeEmbedded,       // Embedded inside the base kernel.
    WindowServerTypeRing0Process,
    WindowServerTypeRing3Process
    // ...
} window_server_t;

// The window server struct.
// Here we will find all the info we need about the window server
// that the system is using in the moment. Things like, name, pid ... 
// The system is able to run only one window server.
// We can select one window server per desktop.
// The window server is a ring3 process.
// The system also have an embedded window server inside the base kernel.
// Maybe we will create different kinds of window server in the future,
// but this is gonna be the struct for then all. Only one structure.


// #todo:
// maybe the window server can be an kind of device
// and we can use the file dev/ws to setup the properties.
// and use ioctl.


// #bugbug
// Estamos com problemas na hora dos aplicativos pegarem 
// informaçoes que estao dentro de estruturas do kernel.
// Por isso suspendemos essa estrutura por enquanto.
// Leia as notas de design.

//struct window_server_d
//{
    // #bugbug
    // It works fine on qemu.
    // But we lost all these values when testing on my real machine. 
    // Why?
    // ps: We are using the embedded command, 'metrics' on gdeshell.
    // Maybe the problem is in the gdeshell application.

    extern int WindowServer_initialized;
    
    extern window_server_t WindowServer_type;  // tipo de window server.
    
    // the pid for loadable window servers.
    // When the window server is the embedded so this pid needs to be
    // the pid of the kernel process.
    
    extern pid_t WindowServer_pid; 
    //struct desktop_d *desktop;    // the desktop associated with the widnow server. 

    // Limiting the nale to 64.
    extern char WindowServer_name[64];

    //file *ws_file;
    
    // the virtual console used by this window server.
    extern  int WindowServer_virtual_console;
    
    //no navigation.
//};
//static struct window_server_d WindowServer;


//
// == prototypes ==============================================
//


// This is called at the kernel initialization to initialize
// the window server struct with the embedded window server info.
int ws_init(void);


void ws_show_info(void);

// Let's setup the window server.
// See:
// 2io/ws.c
int 
ws_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg );


#endif    




//
// End
//


/*
 * File: security/desktop.c
 *
 * Descri��o:
 *     Ger�ncia a cria��o de desktops.
 *     Cada desktop pertence � uma window station. Cada desktop cont�m v�rias 
 * janelas e menus. Cada desktop tem um prop�sito, as vezes gen�rico, as vezes 
 * espec�fico. 
 *     Define como as janelas est�o empilhadas, qual est� em foregroud (Por cima).
 *     Define uma lista encadeada de janelas, trocando a janela ativa e o 
 * foco de entrada. Etc...  
 *     Faz parte do m�dulo Window Manager do tipo MB.
 *
 * Obs:
 *     Os aplicativos poder�o acessar esses servi�os em user mode. Atrav�s de 
 * um subsistema em user mode que gerencia janelas.
 *     O desktop abarca v�rios componentes como janelas especiais, 
 * janelas normais, �reas de mem�ria para usos diversos, permissoes, 
 * caracter�sticas diversas ... etc ...
 *    Obs: *IMPORTANTE: Um desktop tem um heap de mem�ria. A gerente de
 * mem�ria alocar� mem�ria para os processos pertencentes � um desktop
 * espec�fico no pr�prio heap do desktop ao qual o processo pertence. 
 *
 * 
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


// This is the desktop used by the base kernel.
// So, the kgws and the kgwm can be here. 
struct desktop_d *desktop0;
// O desktop atual.
struct desktop_d *CurrentDesktop;
//List.
unsigned long desktopList[DESKTOP_COUNT_MAX];



/*
    Buffer creation:
	===============
    
	//Supposing the display is 800x600 with 32 bpp (meaning 32/8 = 4 bytes per pixel).
    uint8_t *BackBuffer = ((uint8_t *) (kmalloc(800 * 600 * 4)));
	
	//24bpp.
	unsigned char *BackBuffer = ( (unsigned char *) (kmalloc(800 * 600 * 3))); 
*/


/*
 * RegisterDesktop:
 *     Registrando um desktop numa lista de desktops.
 *     @todo: Mudar para desktopRegisterDesktop(.). 
 */

int RegisterDesktop (struct desktop_d *d)
{
    int Offset = 0;


    if ( (void *) d == NULL ){
        debug_print ("RegisterDesktop: [FAIL] d\n");
        return (int) 1;  
    }


	// #bugbug: 
	// Pode aparacer um loop infinito aqui.
	// #todo: usar for.

    while ( Offset < DESKTOP_COUNT_MAX )
    {
        if ( (void *) desktopList[Offset] == NULL )
        {
            desktopList[Offset] = (unsigned long) d; 
            
            d->desktopId = Offset;
            
            return 0;
        }

       Offset++;
    };

	// Fail.
	
    return (int) 1;
}

/*
 * get_current_desktop:
 *     Pega o endere�o da estrutura do desktop atual.
 *     @todo: Mudar para desktopGetCurrentDesktop().
 */

void *get_current_desktop (void)
{
    //Check limits.

    if ( current_desktop < 0 || 
         current_desktop >= DESKTOP_COUNT_MAX )
    {
        return NULL;
    }
    
    return (void *) desktopList[current_desktop];
}


/*
 * set_current_desktop:
 *     Seta o desktop atual.
 *     @todo: Mudar para desktopSetCurrentDesktop(.). 
 */

//Configura a vari�vel global.

void 
set_current_desktop ( struct desktop_d *desktop )
{
    if ( (void *) desktop == NULL )
    { 
        return; 
    }

    current_desktop = (int) desktop->desktopId;
    CurrentDesktop = desktop;
}


int get_current_desktop_id (void)
{
    return (int) current_desktop;
}


/*
 * init_desktop_list:
 *     Inicializa o array de ponteiros de desktop.
 */

void init_desktop_list (void)
{
    int i=0;
    while ( i < DESKTOP_COUNT_MAX )
    {
        desktopList[i] = 0;
        i++; 
    };
}


/*
 * CreateDesktop:
 *     Cria um desktop em uma window station.
 */

void *CreateDesktop ( struct room_d *room )
{
    struct desktop_d *Current;
    struct desktop_d *Empty;

    int i=0;
    //... 


    if ( (void *) room == NULL ){
        debug_print ("CreateDesktop: [FAIL] room\n");
        return NULL; 
    }

	//
	// #todo: 
	// O usu�rio precisa de permiss�o pra criar desktops.
	//


    Current = (void *) kmalloc ( sizeof(struct desktop_d) );

    if ( (void *) Current == NULL ){
        panic ("CreateDesktop: Current\n");
    } else {

        Current->room = (void *) room;

		//continua...
    };


    while ( i < DESKTOP_COUNT_MAX )
    {
        Empty = (void *) desktopList[i];

        if ( (void *) Empty == NULL )
        {
            desktopList[i] = (unsigned long) Current;

            Current->desktopId = i;

            return (void *) Current;
        }

        i++;
    };

    return NULL;
}


/*
 * set_current_menuwindow:
 *     Configura a menu window atual.
 */
 
void 
set_current_menuwindow ( 
    struct desktop_d *desktop, 
    struct window_d  *window )
{
    if ( (void *) desktop == NULL || (void *) window == NULL )
    {
        debug_print ("set_current_menuwindow: parameters\n");
        return; 
    }

    desktop->menuWindow = (void *) window;  
}


/*
 * set_current_foreground:
 *     Configura a foreground window atual.
 */

void 
set_current_foreground ( 
    struct desktop_d *desktop, 
    struct window_d *window )
{
    if ( (void *) desktop == NULL || (void *) window == NULL )
    { 
        debug_print ("set_current_foreground: parameters\n");
        return; 
    }  
    
    desktop->foregroundWindow = (void *) window;
}


/*
 * set_current_messagewindow:
 *     Configura a message window atual.
 */
 
void 
set_current_messagewindow ( 
    struct desktop_d *desktop, 
    struct window_d *window )
{
    if ( (void *) desktop == NULL || (void *) window == NULL )
    { 
        debug_print ("set_current_messagewindow: parameters\n");
        return; 
    }  

    desktop->messageWindow = (void *) window;
}


/*
 * set_current_traywindow:
 *     Configura a tray window atual.
 */
 
void 
set_current_traywindow ( 
    struct desktop_d *desktop, 
    struct window_d *window )
{
    if ( (void *) desktop == NULL || (void *) window == NULL )
    {
        debug_print ("set_current_traywindow: parameters\n");
        return; 
    }  

    desktop->trayWindow = (void *) window; 
}


/*
 * set_current_tooltipwindow:
 *     Configura a tooltip window atual.
 */

void 
set_current_tooltipwindow ( 
    struct desktop_d *desktop, 
    struct window_d *window )
{
    if ( (void *) desktop == NULL || (void *) window == NULL )
    { 
        debug_print ("set_current_tooltipwindow: parameters\n");
        return; 
    }  

    desktop->tooltipWindow = (void*) window;
}


/*
 * change_foreground:
 *    Change foreground window for a desktop.
 */
 
void change_foreground ( struct desktop_d *desktop ){
	
    //Foreground window.
    struct window_d *fw;


    if ( (void *) desktop == NULL )
    { 
        debug_print ("change_foreground: desktop\n");
        return; 
    }  


    fw = (void *) desktop->foregroundWindow;

    if ( (void *) fw == NULL ){
        debug_print ("change_foreground: fw\n");
        return;
    }

    //Use a pr�xima janela indicada na estrutura da atual.

    // Deixa a mesma que estava.
    if ( (void *) fw->next == NULL ){
        desktop->foregroundWindow = (void *) fw;

    // Muda para a pr�xima.
    }else{
        desktop->foregroundWindow = (void *) fw->next;
        return;
    };
}


/*
 * set_current_sysMenu:
 *     Configura o sysMenu atual.
 */
 
void 
set_current_sysMenu ( 
    struct desktop_d *desktop, 
    struct menu_d *menu )
{
    if ( (void *) desktop == NULL || (void *) menu == NULL )
    {
        debug_print ("set_current_sysMenu: parameters\n");
        return; 
    }


    desktop->sysMenu = (void *) menu;
}


/*
 * set_current_dialogsysMenu:
 *     Configura o dialogsysMenu atual.
 */

void 
set_current_dialogsysMenu ( 
    struct desktop_d *desktop, 
    struct menu_d *menu )
{
    if ( (void *) desktop == NULL || (void *) menu == NULL )
    { 
        debug_print ("set_current_dialogsysMenu: parameters\n");
        return; 
    }

    desktop->dialogsysMenu = (void *) menu; 
}


/*
 * set_current_menuHScroll:
 *     Configura o menuHScroll atual.
 */

void 
set_current_menuHScroll ( 
    struct desktop_d *desktop, 
    struct menu_d *menu )
{
    if ( (void *) desktop == NULL || (void *) menu == NULL )
    { 
        debug_print ("set_current_menuHScroll: parameters\n");
        return; 
    }

    desktop->menuHScroll = (void *) menu; 
}


/*
 * set_current_menuVScroll:
 *     Configura o menuVScroll atual.
 */

void 
set_current_menuVScroll ( 
    struct desktop_d *desktop, 
    struct menu_d *menu )
{
    if ( (void *) desktop == NULL || (void *) menu == NULL )
    {
        debug_print ("set_current_menuVScroll: parameters\n");
        return; 
    }

    desktop->menuVScroll = (void *) menu;
}


/*
 ***********************************************
 * init_desktop:
 *     Inicializa o desktop 0.
 *     @todo: Mudar para: desktopInit().
 */

void init_desktop (void){

    int i=0;


    debug_print ("init_desktop:\n");

    //printf("init_desktop: Initializing..\n");


    desktops_count = 0;

	// Inicializa a lista.
    init_desktop_list ();

    //
    // Struct.
    //

    desktop0 = (void *) kmalloc ( sizeof(struct desktop_d) );

    if ( (void *) desktop0 == NULL ){
        panic ("init_desktop: desktop0\n");
    }else{
        desktop0->desktopUsed  = 1;
        desktop0->desktopMagic = 1234;

        //todo: object
        
        desktops_count = 1;
        desktop0->desktopId = 0;

        desktop0->lTail = 0;
        desktop0->lHead = 0;
        for (i=0; i<8; i++){
            desktop0->list[i] = (unsigned long) 0;
        };


	    // #todo
	    // Depois precisamos colocar aqui
	    // o pid do processo kernel.
	    // Cada desktop ter� sem ws e sua wm.
        desktop0->ws = -1;
        desktop0->wm = -1;
        // ...
    
 
        // Registrando na lista

        desktopList[0] = (unsigned long) desktop0;
        //RegisterDesktop (desktop0); 
 
        set_current_desktop (desktop0);  

        set_current_menuwindow (desktop0, NULL); 
        set_current_foreground (desktop0, NULL); 
        set_current_messagewindow (desktop0, NULL); 
        set_current_traywindow (desktop0, NULL); 
        set_current_tooltipwindow (desktop0, NULL); 
        set_current_sysMenu (desktop0, NULL);
        set_current_dialogsysMenu (desktop0, NULL);
        set_current_menuHScroll (desktop0, NULL);
        set_current_menuVScroll (desktop0, NULL);

        //desktop0->room = NULL;
    };
}



int desktop_setup_ws ( struct desktop_d *desktop, int ws_pid )
{
    if ( (void *) desktop != NULL )
    {
        desktop->ws = ws_pid;
        return 0;    
    }

    return -1;
}


int desktop_setup_wm ( struct desktop_d *desktop, int wm_pid )
{
    if ( (void *) desktop != NULL )
    {
        desktop->wm = wm_pid;
        return 0;
    }
 
    return -1;
}


//
// End.
//

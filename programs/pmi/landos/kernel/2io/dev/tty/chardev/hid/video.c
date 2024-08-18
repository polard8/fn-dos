/*
 * File: video.c
 *
 * Descri��o: 
 *     Rotinas paga gerenciar os controladores de video.
 *     Crt, Vga ...
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2017 - Revision and small changes.
 */


// See:
// https://wiki.osdev.org/Accelerated_Graphic_Cards


// # importante
// Essa deve ser a �nica maneira em que o sistema acessa
// o controlador de v�deo.
// Por aqui o sistema far� configura��es no controlador
// e enviar� dados para o lfb.


//
// == VGA =======================================================
//

/*
  
    This index lists the VGA's I/O ports in numerical order, 
    making looking up a specific I/O port access simpler.
 
    3B4h -- CRTC Controller Address Register
    3B5h -- CRTC Controller Data Register
    3BAh Read -- Input Status #1 Register
    3BAh Write -- Feature Control Register
    3C0h -- Attribute Address/Data Register
    3C1h -- Attribute Data Read Register
    3C2h Read -- Input Status #0 Register
    3C2h Write -- Miscellaneous Output Register
    3C4h -- Sequencer Address Register
    3C5h -- Sequencer Data Register
    3C7h Read -- DAC State Register
    3C7h Write -- DAC Address Read Mode Register
    3C8h -- DAC Address Write Mode Register
    3C9h -- DAC Data Register
    3CAh Read -- Feature Control Register
    3CCh Read -- Miscellaneous Output Register
    3CEh -- Graphics Controller Address Register
    3CFh -- Graphics Controller Data Register
    3D4h -- CRTC Controller Address Register
    3D5h -- CRTC Controller Data Register
    3DAh Read -- Input Status #1 Register
    3DAh Write -- Feature Control Register

See:
    https://web.stanford.edu/class/cs140/projects/pintos/specs/freevga/vga/portidx.htm
 */




#include <kernel.h>


//Defini��es internas.

//@todo: Criar um arquivo para gerenciar fontes.
#define VIDEO_BIOS_FONT8X8_ADDRESS    0x000FFA6E
//#define VIDEO_BIOS_FONT8X16_ADDRESS (0x000FFA6E+??)
//...

#define VIDEO_BIOS_FONT8X8_WIDTH   8
#define VIDEO_BIOS_FONT8X8_HEIGHT  8
//...

//
// Vari�veis importadas.
//

//??
extern unsigned long SavedBootMode;

//Vari�veis. (head.s)
extern unsigned long SavedBootBlock;    //Par�mtros passados pelo Boot Loader.

extern unsigned long SavedLFB;          //LFB address.  
extern unsigned long SavedX;            //Screen width. 
extern unsigned long SavedY;            //Screen height.
extern unsigned long SavedBPP;          //Bits per pixel.
//...

unsigned long g_video_mode=0;

Graphics_t *Graphics;

struct video_d  VideoBlock;


int videoStatus=0;
int videoError=0;
//...


//Screen sizes and bpp.
unsigned long g_device_screen_width=0;
unsigned long g_device_screen_height=0;
unsigned long g_device_screen_bpp=0;


// LFB - Esse � o endere�o usado pelo driver de v�deo em /x
// para acessar o LFB, ou seja o frontbuffer.
// Lembrando que o driver de v�deo deve ser independente do 
// kernel ent�o o kernel s� poder� obter esse endere�o se
// solicitar par asse driver.
// Mas o kernel n�o deve enviar dados para o frontbuffer,
// para isso ele deve usar esse driver.
// #importante: Esse driver poder� ser diferente para
// cada modelo de placa de v�deo.

unsigned long __frontbuffer_va=0;
unsigned long __frontbuffer_pa=0;

//cga
unsigned long __cga_va=0;
unsigned long __cga_pa=0;







/*
 **********************************
 * __video_lfb_putpixel:
 *
 *    # todo:
 *    Estamos trazendo essa rotina aqui para o driver de v�deo.
 *    Que � a camada mais baixo. A camada que tem acesso ao controlador
 *    de v�deo.
 * 
 * IN: 
 *     color, x, y, 0
 */ 


/*
void 
__video_lfb_putpixel ( unsigned long ax, 
               unsigned long bx, 
		       unsigned long cx, 
		       unsigned long dx );
void 
__video_lfb_putpixel ( unsigned long ax, 
               unsigned long bx, 
		       unsigned long cx, 
		       unsigned long dx )
{
	unsigned char *where = (unsigned char *) 0xC0400000;
	
	unsigned long color = (unsigned long) ax;
	
	char b, g, r, a;
	
	b = (color & 0xFF);	
	g = (color & 0xFF00) >> 8;
	r = (color & 0xFF0000) >> 16;
	a = (color >> 24) + 1;
	
	int x = (int) bx;
	int y = (int) cx;

	// = 3; 
	//24bpp
	int bytes_count;
	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//...
	}	
	
	//#importante
	//Pegamos a largura salva.
	int width = (int) SavedX; 
	
	int offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );
	
	where[offset] = b;
	where[offset +1] = g;
	where[offset +2] = r;

	//teste
	if ( SavedBPP == 32 )
	{
	    where[offset +3] = a;	
	}
}
*/


/*
//pega um pixel no BACKBUFFER
//tem que usar vari�vel pra bytes per pixel e screen width. 
//A ideia � poder pegar os p�xel de um ret�ngulo e salv� los
//para depois devolver ao backbuffer.

unsigned long __video_get_pixel ( unsigned long x,  unsigned long y ){
	
	//SALVA A COR
	unsigned long COLOR;
	
	unsigned char *rgba = (unsigned char *) &COLOR;
	
	unsigned char *backbuffer = (unsigned char *) BACKBUFFER_ADDRESS;

	// = 3; 24bpp
	int bytes_count;

	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
		
		//...
	}	

	// #importante
	// Usando largura salva.
	
	int width = (int) SavedX; 
		
	unsigned long pos = (unsigned long) (y* bytes_count * width)+(x * bytes_count);	
	
	COLOR = *( unsigned long * ) &backbuffer[pos];
	
    return (unsigned long) COLOR;	
}
*/



/*
  #
//copia um pixel do backbuffer para o frontbuffer
//tem que usar vari�vel pra bytes per pixel e screen width.
//#todo: TESTAR ESSA FUN��O

void __video_refresh_pixel ( unsigned long x,  unsigned long y ){
	
	//SALVA A COR
	unsigned long COLOR;
	
	unsigned char *rgba = (unsigned char *) &COLOR;
	
    unsigned char *frontbuffer = (unsigned char *) FRONTBUFFER_ADDRESS;	
	
	// = 3; 24bpp
	int bytes_count;
	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//...
	}	

	//#importante
	//Usando largura salva.
	
	int width = (int) SavedX; 	

	unsigned long pos = (unsigned long) (y* bytes_count * width)+(x * bytes_count);
	
	//pego o pixel no backbuffer
	COLOR = __video_get_pixel ( x, y );
		
	//#todo:
	// Checar o limite de pos.
	//unsigned long address = &frontbuffer[pos];
	
	// #bugbug:
	// Isso � potencialmente perigoso para compilar.	
	
	*( unsigned long * ) &frontbuffer[pos] = COLOR;
}
*/



/*
//copia um pixel do backbuffer para o frontbuffer
//tem que usar vari�vel pra bytes per pixel e screen width.
//#todo: TESTAR ESSA FUN��O

void __video_refresh_pixel ( unsigned long x,  unsigned long y ){
	
	//SALVA A COR
	unsigned long COLOR;
	
	unsigned char *rgba = (unsigned char *) &COLOR;
	
    unsigned char *frontbuffer = (unsigned char *) FRONTBUFFER_ADDRESS;	
	
	// = 3; 24bpp
	int bytes_count;
	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//...
	}	

	//#importante
	//Usando largura salva.
	
	int width = (int) SavedX; 	

	unsigned long pos = (unsigned long) (y* bytes_count * width)+(x * bytes_count);
	
	//pego o pixel no backbuffer
	COLOR = get_pixel ( x, y );
		
	//#todo:
	// Checar o limite de pos.
	//unsigned long address = &frontbuffer[pos];
	
	// #bugbug:
	// Isso � potencialmente perigoso para compilar.	
	
	*( unsigned long * ) &frontbuffer[pos] = COLOR;
}
*/


/*
 ***********************************************************
 * refresh_rectangle:
 *     Copiar um ret�ngulo do backbuffer para o frontbuffer. 
 * 
 *     @todo: Rotina parecida com essa pode ser criada e usada para manipular 
 * regi�es da tela, como �rea de cliente efetuar scroll de buffer em p�ginas 
 * de navegador ou menus .. mas para isso, a c�pia seria dentro do pr�prio 
 * backbuffer ou de um terceiro buffer para o backbuffer. 
 *
 * Hist�rico:
 *     2017 - Criado por Frederico Lamberti Pissarra.
 *     2018 - Fred Nora.
 */	


//#importante
//� bem mais r�pido com m�ltiplos de 4.
 
/* 
void 
__video_refresh_rectangle ( unsigned long x, 
                    unsigned long y, 
                    unsigned long width, 
                    unsigned long height )
{
	void *p = (void *) FRONTBUFFER_ADDRESS;
	const void *q = (const void*) BACKBUFFER_ADDRESS;

	//#TEST
	register unsigned int i;
	//unsigned int i;

	unsigned int line_size, lines;
	unsigned int offset;
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();

	int count; 

	// = 3; 24bpp
	int bytes_count;

	line_size = (unsigned int) width; 
	lines = (unsigned int) height;

	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//...
	}

	// #aten��o.
	
	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	
	offset = (unsigned int) ( (bytes_count*SavedX*(y)) + (bytes_count*(x)) );
	
	p = (void *) (p + offset);    
	q = (const void *) (q + offset);    
	 
	// #bugbug
	// Isso pode nos dar problemas.
	// ?? Isso ainda � necess�rio nos dias de hoje ??
	
	vsync ();	
		
	//(line_size * bytes_count) � o n�mero de bytes por linha. 

	//#importante
	//� bem mais r�pido com m�ltiplos de 4.	
	
	//se for divis�vel por 4.
	if ( ((line_size * bytes_count) % 4) == 0 )
	{
        count = ((line_size * bytes_count) / 4);  	

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso n�o seja divis�vel por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * bytes_count);
	 		p += (Width * bytes_count);
	    };
	}

	//se n�o for divis�vel por 4.
	if ( ((line_size * bytes_count) % 4) != 0 )
	{
	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * bytes_count) );
		    
			q += (Width * bytes_count);
		    p += (Width * bytes_count);
	    };	
	}
}
*/




/*
 * videoSetupCGAStartAddress:
 *     Configura o endere�o inicial da mem�ria de video em modo texto   
 *     fis=b8000  vir=0x800000 
 */

void videoSetupCGAStartAddress (unsigned long address){
	
    g_current_vm = (unsigned long) address;
	//g_current_cga_address
}


/*
 fis=a0000
void videoSetupVGAStartAddress( unsigned long address);
void videoSetupVGAStartAddress( unsigned long address)
{
    g_current_vga_address = (unsigned long) address;
	return;
};
*/


/*
 * get_video_mode: 
 *     Obtem o modo de video atual.
 */

//#todo
//isso pode ser incluido em 'get system parameters' system call.

unsigned long videoGetMode (void)
{
    return (unsigned long) g_current_video_mode;
}


/*
 * videoSetMode:
 *     Configura o modo de video atual.
 */
void videoSetMode (unsigned long mode)
{
	
    unsigned long VideoMode;
    unsigned long Width;
	unsigned long Height;
	//continua...(outros parametros)


    debug_print ("videoSetMode: [BUGBUG] This routine is wrong\n");


	
	VideoMode = (unsigned long) mode;
	
    //
	// todo: Check limits.
	//
	
	//if (){}
	

	//Se estiver nos limites.
	if ( VideoMode > 0 && VideoMode < 9000)
	{
		//g_current_video_mode = (unsigned long) VideoMode;
        g_video_mode = (unsigned long) VideoMode;
		VideoBlock.vesaMode = (unsigned long) VideoMode; 
		//...
	};
	
	
	//
	// @todo:
	// Organizar isso. Os valores atuais devem ser obtidos em real mode 
	// usando os recursos do VESA BIOS.
	//
	
    switch (VideoMode){
		
	    case 0x110: 
		    Width = 800;
			Height = 600;
		break;

	    case 0x111:
		    Width = 800;
			Height = 600;
		break;

	    case 0x112:
		    Width = 800;
			Height = 600;
		break;

	    case 0x113:
		    Width = 800;
			Height = 600;
		break;

	    case 0x114:
		    Width = 800;
			Height = 600;
		break;
		
	    case 0x115:
		    Width = 800;
			Height = 600;
		    break;
	
	    default:
		    Width = 800;
			Height = 600;
		    break;
	};    
	
	
	screenSetSize (Width,Height);
	
	// Continua... (outros parametros)

    g_current_video_mode = (unsigned long) VideoMode;
}




/*
unsigned long 
video_driver_dialog ( int service, 
    unsigned long long1,
    unsigned long long2 );
    
// dialo usado para conversr com o driver de v�deo.
// para obter valores, fazer configura��es
// ou enviar conte�do para o lfb.
unsigned long 
video_driver_dialog ( int service, 
    unsigned long long1,
    unsigned long long2 )
{
	//initialize video driver.
    case 1:
        //__video_initialize ();
        return 0;
        break;
    
    // get lfb physical address
    case 2:
        if ( __video_driver_initialized == 1 )
        {
			return (unsigned long) __frontbuffer_pa;
        }
        // erro
        return (unsigned long) 0;
        break;

    // get lfb virtual address
    case 3:
        if ( __video_driver_initialized == 1 )
        {
			return (unsigned long) __frontbuffer_va;
        }
        // erro
        return (unsigned long) 0;
        break;


    // Get device screen width
    case 4:
        if ( __video_driver_initialized == 1 )
        {
			return (unsigned long) __device_screen_width;
        }
        // erro
        return (unsigned long) 0;
        break;

    // Get device screen height
    case 5:
        if ( __video_driver_initialized == 1 )
        {
			return (unsigned long) __device_screen_height;
        }
        // erro
        return (unsigned long) 0;
        break;
        
    //...
}
*/


/*
// Used in vga controller stuff.
// #todo: We need to use 'unsigned int' in the port?
void 
write_vga_reg ( 
    int port, 
    unsigned char index, 
    unsigned char val);
void 
write_vga_reg ( 
    int port, 
    unsigned char index, 
    unsigned char val) 
{
    
    if (port != 0x3c0) {
         out16 ( (int) port, (unsigned short) val << 8 | index );

    } else {
        out8 ( (int) port, (unsigned char) index );   
        out8 ( (int) port, (unsigned char) val );     
    };
}
*/


/*
 ***********************************************
 * videoInit:
 *     Inicia vari�veis de video de acordo com o modo gr�fico utilizado.
 */ 
 
int videoInit (void){

    int Status=0;


    // Se o modo de video nao esta habilitado
    if ( VideoBlock.useGui != 1 ){
        panic("videoInit:");
    }


    g_useGUI          = TRUE;
    VideoBlock.useGui = TRUE;


    //
    // LFB
    //

	// Esses valores vieram do bootloader.
	// Mas eles precisar ser enviados para esse driver
	// quando o kernel estiver iniciando o driver.
    __frontbuffer_va = (unsigned long) SavedLFB;
    __frontbuffer_pa = (unsigned long) FRONTBUFFER_VA;  


	
	// global usada pelo kernel.
	// #todo: n�o devemos configurar essa global.
	// O kernel deve solicitar esse endere�o. 
	//endere�o f�sico do frontbuffer.
    g_frontbuffer_pa = (unsigned long) SavedLFB;  

	//endere�o virtual do backbuffer.
    g_backbuffer_va = (unsigned long) BACKBUFFER_VA;



    // Device screen sizes. 
    // (herdadas do boot loader.)
    // See: globals/gdevice.h

    g_device_screen_width  = (unsigned long) SavedX;
    g_device_screen_height = (unsigned long) SavedY;
    g_device_screen_bpp    = (unsigned long) SavedBPP;



	// #importante
	// Nesse momento podemos testar o LFB.
	// Enviando alguma coisa diretamente pra la' ...
	
	
	// #DEBUG
	// vamos tentar usar isso como breakpoint.
	// Ok isso funcionou na gigabyte/intel ... vamos usar isso por enquanto.
    //lfb_putpixel ( COLOR_YELLOW, 11, 11, 0 );
	//while(1){}
		
	//@todo: #bugbug Para configurar a estrutura HostDeviceInfo tem que 
	//alocar mem�ria antes, por isso s� faremos isso depois de 
	//inicializarmos o m�dulo runtime. /rt.
	
	//Isso pode n~ao funcionar pois nao temos
	//os endere�os corretos ainda.
	
	//Background.
	
	//#bugbug #hackhack	
	//vamos suprimir essa mensagem para testar
	//o kernel na maquina real gigabyte/intel
	//#importante: nuca mais usaremos essa rotina de bg aqui.
	//vamos passar ela para um ponto onde ela ja possa ser usada,
    
    
	// #DEBUG
	// breakpoint
    //vamos testar se 'e a rotina de bg que est'a falhando...
    //caso seja ela, ent~ao vamos suprimila se possivel.
	//ok isso funcionou, vamos avan�ar.
	
    //lfb_putpixel ( COLOR_YELLOW, 11, 11, 0 );
	//while(1){}

    
		
	//@todo: Isso deve fazer parte do construtor.
		
	//Poder�amos copiar a font da ROM para a RAM.
		
	//
	// ## Font support ##
	//
		
	//Font. (BIOS font).
	//#bugbug: 
	//Na verdade video.c n�o tem acesso a essa vari�vel,
	//� preciso chamar o servidor atrav�s de um m�todo para configur�-la.

    gwsSetCurrentFontAddress ( VIDEO_BIOS_FONT8X8_ADDRESS );
 
    // #todo: 
    // Usar a fun��o que configura essas vari�veis.
    gcharWidth  = VIDEO_BIOS_FONT8X8_WIDTH;
    gcharHeight = VIDEO_BIOS_FONT8X8_HEIGHT;
    gfontSize   = FONT8X8;


    // #bugbug
    // Qual eh o current no momento dessa inicializa�ao
    // so temos 4.
    // eles ja estao inicializados.
    // #todo: podeia ter uma flag que diz se ja inicializamos os consoles.
    
    if (fg_console < 0 || fg_console >= CONSOLETTYS_COUNT_MAX)
    {
        panic("videoInit: fg_console\n");
    }
    
    // cursor dimentions in pixel.
    // #bugbug: determinado
    
    // #todo
    // chamar uma fun�ao helper pra fazer isso
    
    CONSOLE_TTYS[fg_console].cursor_width_in_pixels  = 8;
    CONSOLE_TTYS[fg_console].cursor_height_in_pixels = 8;
       
    CONSOLE_TTYS[fg_console].cursor_color = COLOR_WHITE;

    // Cursor margin
    CONSOLE_TTYS[fg_console].cursor_left = 0;      // Margem esquerda dada em linhas.
    CONSOLE_TTYS[fg_console].cursor_top  = 0;      // Margem superior dada em linhas.
    
    // Cursor limits
    CONSOLE_TTYS[fg_console].cursor_right  = 256;  // Margem direita dada em linhas.
    CONSOLE_TTYS[fg_console].cursor_bottom = 256;  // Margem inferior dada em linhas.


    // Cursor position
    // See: system.c
    set_up_cursor(0,0);
    CONSOLE_TTYS[fg_console].cursor_x = 0;
    CONSOLE_TTYS[fg_console].cursor_y = 0;


	//Continua ...
		
	//
	// Outras configura��es de v�deo independentes do modo de v�deo.
	//
	
	//
    // @todo: Sizes, atribute, atribute color, row, column
	//



	
	// #DEBUG
	// breakpoint
    // ok isso funcionou na gigabyte/intel , vamos avan�ar ...
   // lfb_putpixel ( COLOR_YELLOW, 11, 11, 0 );
   //	while(1){}


	
	
#ifdef BREAKPOINT_TARGET_AFTER_VIDEO
    // #debug 
    // A primeira mensagem s� aparece ap�s a inicializa��o da runtime.
    // por isso n�o deu pra limpar a tela antes.
    printf(">>>debug hang: after video");
    refresh_screen(); 
    while (1){ asm ("hlt"); };
#endif

    return (int) Status;    
}


/*
 *********************
 * videoVideo:
 *     M�todo construtor.
 *     Fun�ao interna. 
 *     Confgura algumas vari�veis.
 *     @todo: isso poderia ter retorno void.
 */

int videoVideo (void)
{
    videoStatus = 0;
    videoError = 0;
    //...

    return 0;
}

// called by main.c
int Video_initialize(void)
{
    videoVideo();
    videoInit();
    // ...

    // Done
    g_driver_video_initialized = TRUE;
   
    return 0;
}


    
    
    


//
// End.
//


/*
 * File: video.h
 *
 * Descri��o:
 *     Header para rotinas de gerenciamento dos controladores de video.
 *     As configura��es de video podem ser usadas pelo shell.
 * 
 * 0xBEEF	VirtualBox Graphics Adapter	0x80EE	Oracle Corporation - 
 *  InnoTek Systemberatung GmbH
 *  todo: Criar um utilit�rio que mostre e configure informa��es de video.
 *  Vers�o 1.0, 2015, 2016. 
 */


#ifndef ____HALVID_H
#define ____HALVID_H    1


/*
  bytes.
  A whole screeen is either 2000 bytes (40*25*2) or 4000 bytes (80*25*2).
*/ 
 
/*
 * LFB e BACKBUFFER
 *     
 *     Constantes para endere�os l�gicos.
 *     O bootloader configura as p�ginas e 
 *     atribui esse endere�o para o LFB.
 */ 

#define LFB_BASE        0xC0400000 
#define BACKBUFFER_BASE 0xC0800000


//Mem�ria de video vga em text mode. b8000
//the address 0xC00B8000 must be used, since the virtual address 0xC0000000 maps 
//to the physical address 0x00000000.


/*
 * Video mode:
 *     Modo de v�deo usado.
 *     //@todo: se estamos encapsulando no m�dulo, retirar o G de global.
 */
extern unsigned long g_video_mode;    


/*
 * Suporte �s dimen��es da tela no modo de v�deo escolhido.
 * @todo: existe uma redefini��o em window.h
 */
//unsigned long gScreenWidth;
//unsigned long gScreenHeight;


//
// Graphic mode support.
//
 
typedef struct tagGraphics  Graphics_t;
struct tagGraphics
{
    unsigned long LFB;
    //unsigned long Backbuffer;
    //...
};
extern Graphics_t *Graphics;


//
// Video support
//

/*
 * video_d:
 *     Estrutura para informa��es sobre par�metros de v�deo.
 */

typedef struct video_d  VideoBlock_t;
typedef struct video_d  video_t;

struct video_d
{
    object_type_t   objectType;
    object_class_t  objectClass;

	//call back ;d
	
	int useGui;   //c, se estamos ou n�o usando gui. text mode, video mode.
	int vgaMode;  //b, n�mero do modo de v�deo se estiver usando vga.
	int vesaMode; //a, n�mero do modo vesa.
	//int 
	//...
	
	//unsigned long flag;  //f
	//unsigned long error; //e
	
	//currente video memory. Ponteiro para a base atual da memoria de video
	// em text mode.
	unsigned long currentVM; 
	char ch;           //caractere.
	char chAtrib;      //atributo do caractere. 
	//...    

    //unsigned long Display[32];    //Ponteiros para as telas.
	
};
extern struct video_d  VideoBlock;

//
// Prototypes ======================================
//

/*
 * Sincroniza o retra�o vertical. 
 * para directdraw usando lfb.
 * @todo: 
 *     Essa fun��o pode ser arte do hal, 
 * ficando aqui apenas uma interface.
 *Obs: Isso � coisa de hardware. v�deo. (HAL)
 */

void vsync (void);  
 
//video.c 
void videoSetupCGAStartAddress(unsigned long address);

unsigned long videoGetMode (void);
void videoSetMode (unsigned long mode);

int videoVideo (void);  
int videoInit (void); 

#endif   

//
// End.
//

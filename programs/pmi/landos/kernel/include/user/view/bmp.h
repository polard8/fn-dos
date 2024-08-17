// bmp.h
// Header para rotinas de BMP.
// 2015 - Created by Fred Nora.

#ifndef __BMP_H
#define __BMP_H    1
 

/* "MB" */ 
#define BMP_TYPE 0x4D42        
 
#define  BMP_CHANGE_COLOR_NULL  0
#define  BMP_CHANGE_COLOR_TRANSPARENT  1000
#define  BMP_CHANGE_COLOR_SUBSTITUTE   2000
//...
  

//flag que avisa que dve haver alguma mudan�a nas cores. 
extern int bmp_change_color_flag; 
//salva-se aqui uma cor para substituir outra. 
extern unsigned long bmp_substitute_color; 
//cor selecionada para ser substitu�da ou ignorada. 
extern unsigned long bmp_selected_color;  
 

/* ## Cancelada ! ## */
static unsigned long cga_16colors_palette[1] = { 0x000000, };

/* ## Cancelada ! ## */
static unsigned long vga_256colors_palette[1] = { 0x00000000, };


/*
 * bmpDirectDisplayBMP:
 * Mostra na tela uma imagem bmp carregada na mem�ria. (no LFB)
 * IN:
 *     address = endere�o base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 */
int bmpDirectDisplayBMP( char *address, 
                   unsigned long x, 
				   unsigned long y );


/*
 * bmpDisplayBMP:
 * Mostra na tela uma imagem bmp carregada na mem�ria. no backbuffer()
 * IN:
 *     address = endere�o base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 */
int bmpDisplayBMP( char *address, 
                   unsigned long x, 
				   unsigned long y );
				   
int bmpDisplayMousePointerBMP( char *address, 
                               unsigned long x, 
				               unsigned long y );
							   

//mostra no lfb
//levando em considera��o tratamento de transpar�ncia.
int bmpDisplayCursorBMP( char *address, 
                         unsigned long x, 
				         unsigned long y );
					

#endif  

//
// End
//

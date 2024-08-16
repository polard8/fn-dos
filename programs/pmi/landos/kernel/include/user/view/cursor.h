/*
 * File: cursor.h
 * Descri��o:
 *     Suporte ao cursor para textos e inputs.    
 *
 * Obs: 
 * Essas vari�veis de posicionamento de cursor tem sido muito �teis
 * nas rotinas de texto.
 *
 * @todo: colocar aqui informa��es sobre cursor.
 */

/* cursor */

#ifndef __CURSOR_H
#define __CURSOR_H    1


#define CURSOR_DRAW     (1)
#define CURSOR_ERASE    (2)
#define CURSOR_MOVE     (3) 
//...

//
// ** Usar essas vari�veis globais.
//    Os valores s�o retirados das estruturas dos objetos
// gr�ficos onde o cursor esta inserido e passadas para c�.
// Os manipuladores de cursor deve se atentar � essas globais.
// @todo: Essas globais ser�o substituidas pelos valores da 
// estrutura do cursor atual. 'CurrentCursor'.
// Cada objeto gr�fico poder� ter uma estrutura de cursor associada � ele.
// #bugbug: estamos tendo problemas com o uso dessa estrutura. Cuidado.
// deixe pra depois, vai usado as globais.
//

//
// ## Cursor ##
//

//Cursor. 
//(disciplica de linhas).
//gws - � natural que o gerenciador de recursos gr�ficos 
//centralise o gerenciamento dos recursos gr�ficos, como o cursor.
//#importante: movido para gws.h
//unsigned long g_cursor_x;
//unsigned long g_cursor_y;
//unsigned long g_cursor_width;   //??
//unsigned long g_cursor_height;  //??
//unsigned long g_cursor_color;
//unsigned long g_cursor_left;     // margem esquerda dada em linhas
//unsigned long g_cursor_top;      // margem superior dada em linhas
//unsigned long g_cursor_right;    // margem direita dada em linhas
//unsigned long g_cursor_bottom;   // margem inferior dada em linhas



// ## IMPORTANTE ## 
// Isso � �timo, por permitir escolher 
// uma posi��o dentro do terminal.


typedef enum {
	cursorTypeDefault,  //Arrow left.
	cursorTypeText,     // '|' 
	cursorTypeWait,     //Ampulheta.
	cursorTypeVerticalResize,
	cursorTypeHorizontalResize,
	cursorTypeDiagonalResize1,
	cursorTypeDiagonalResize2,
	cursorTypeUnavailable,
	cursorTypePrecision,
	cursorTypeXXXX,
    //...	
}cursor_type_t;




/*
 *********************************************
 * cursor_d:
 *     Estrutura de suporte � cursor.
 *     Essa estrutura deve ser inclu�da na estrutura de janela.
 */

typedef struct cursor_d cursor_t;

struct cursor_d
{

    // Object.
    object_type_t  objectType;
    object_class_t objectClass;

	//Posicionamento.
	unsigned long x;
	unsigned long y;
	
    //unsigned long left;     // margem esquerda dada em linhas
    //unsigned long top;      // margem superior dada em linhas
    //unsigned long right;    // margem direita dada em linhas
    //unsigned long bottom;   // margem inferior dada em linhas
	
	//struct window_d *window;
	//struct rect_d *rect;
	
	//Imagem usada como cursor.
    void *imageBuffer;
    void *imagePathName;
    file *cursorFile;

	//Tipo. 
	cursor_type_t cursorType;
	
	//...
};

//cursor_t *Cursor;
//cursor_t *CurrentCursor;
//cursor_t *DeveloperWindowCursor; //test?? Cursor da janela do desenvolvedor.
//...

//======================


// Cursor.
// See: console.c
void set_up_cursor (unsigned long x, unsigned long y);
unsigned long get_cursor_x (void);
unsigned long get_cursor_y (void);

#endif   

//
// End
//



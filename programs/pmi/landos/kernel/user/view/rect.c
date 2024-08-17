/*
 * File: rect.c
 *
 *     Draw rectangles.
 *  
 * History:
 *    2015 - Created by Fred Nora.
 */


#include <kernel.h>



//Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// @todo: Devemos chamar o m�dulo hal para obtermos esses valores.
//depois salvamos em vari�veis internas usadas pela gui.

extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 


struct saved_rect_d *SavedRect;

// ====================================

// ??
// Copiando ...
// Destination is an Null pointer? 
// Source is an Null pointer? 
// Zero-sized copy? 
// Destination is Source?

void *rectStrCopyMemory32 ( 
    unsigned long *dest, 
    unsigned long *src, 
    int count ) 
{

    register int i=0;

    // Yes
    if ( (dest == NULL)  || 
         (src == NULL)   || 
         (count == 0)    || 
         (src == dest) ) 
    {
        return dest;
    }

    // GCC should optimize this for us :)
    // I'm lying.
    for ( i=0; i < count; i++ ) 
    {
        dest[i] = src[i];
    };

    return dest;
}


//
//===============================================================
// refresh rect - Fred. P.
//
// @todo:
// Nessa macro podemos usar vari�veis globais e inicializar
// essas vari�vel. E considerarmos valores como g_bpp, g_screen_width. 
//


//#define RGB_PIXEL_OFFSET(x,y) \
//( (3*800*(y)) + (3*(x)) )

//
// #define RGB_PIXEL_OFFSET(x,y) \
// ( (3*screenGetWidth()*(y)) + (3*(x)) )
//
// #define RGB_PIXEL_OFFSET(x,y) \
// ( ( screenGetBPP() * screenGetWidth()*(y)) + ( screenGetBPP() *(x)) )

// #define RGB_PIXEL_OFFSET(x,y) \
// ( ( g_bpp * g_screen_width *(y)) + ( g_bpp *(x)) )

//================================================


//Usada no refresh rectangle.
//#todo: precisamos de uma vari�vel para a lergura 
//da tela e para bytes per pixel.
//#todo: isso deve virar uma fun��o.
//#define BUFFER_PIXEL_OFFSET(x,y) \
//( (3*800*(y)) + (3*(x)) )

/*
 
 ### Usar isso ###
 
unsigned long function_BUFFER_PIXEL_OFFSET ( unsigned long x, unsigned long y );
unsigned long function_BUFFER_PIXEL_OFFSET ( unsigned long x, unsigned long y )
{
    //( (3*800*(y)) + (3*(x)) )
	
    return (unsigned long) ( ( bytes_per_pixel * pixels_per_line *(y)) + ( bytes_per_pixel *(x)) );    	
};
*/

//
// @todo: Criar uma estrutura para o elemento gr�fico. entre os elementos da estrutura
// pode ter os buffer para o char. backbuffer, frontbuffer, dedicatedbuffer.
//
//


/*
 * rectDrawRectangleWindowBuffer:
 *     Pinta um ret�ngulo no buffer da janela.
 *     Serve para pintar janelas que ir�o direto do seu buffer para o LFB da 
 * mem�ria de v�deo, sem passar pelo back buffer. (OVERLAPPED)
 *
 */
/*
void rectDrawRectangleWindowBuffer(struct window_d *window, 
                                   unsigned long x, 
                                   unsigned long y, 
						           unsigned long width, 
						           unsigned long height, 
						           unsigned long color ); 
void rectDrawRectangleWindowBuffer(struct window_d *window, 
                                   unsigned long x, 
                                   unsigned long y, 
						           unsigned long width, 
						           unsigned long height, 
						           unsigned long color )
{
    return;	
}
*/


/* 
void rectDrawRectangle( struct window_d *window, struct rect_d *rect);
void rectDrawRectangle( struct window_d *window, struct rect_d *rect)
{
	struct window_d *hwndDesktop;
	
    hwndDesktop = guiGetMainWindow();
	
	// Criaremos o ret�ngulo na janela principal caso o ponteiro 
	//passado seja inv�lido.
	
    if( (void*) window == NULL ){
        window = hwndDesktop;
    };

    unsigned long x; 
    unsigned long y; 
	unsigned long width; 
	unsigned long height; 
	unsigned long color;

    x      = window->left + rect->x;	
	y      = window->top + rect->y;
	width  = rect->width;
	height = rect->height;
	color = rect->bg_color;
	
    drawDataRectangle( x, y, width, height, color );
	
}						
*/


/* 
 *************************************
 * drawDataRectangle:
 *     Draw a rectangle on backbuffer. 
 */

void 
drawDataRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color )
{

    // #todo
    // Get the clipping window/rectangle.

    struct rect_d  Rect;
    struct rect_d  ClippingRect;

    int UseClipping = TRUE;


    // dc: Clippint
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();


    //loop
    register unsigned long internal_height = height;


    // Clipping support.
    
    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("drawDataRectangle: [PANIC] w h\n");
        panic       ("drawDataRectangle: [PANIC] w h\n");
    }

//
// Clipping rectangle
//

    // #todo
    // It need to be a blobal thing.
    // We need to handle the surfaces used by 
    // this embedded window server and the loadable one.

    ClippingRect.left   = 0;
    ClippingRect.top    = 0;
    ClippingRect.width  = deviceWidth;
    ClippingRect.height = deviceHeight;

    ClippingRect.right  = deviceWidth;
    ClippingRect.bottom = deviceHeight;

//
// Target rectangle
//

    Rect.bg_color = color;

    // Dimensions.
    Rect.x = 0;
    Rect.y = 0;
    Rect.width  = width;
    Rect.height = height;

    //Margins.
    Rect.left   = x; 
    Rect.top    = y;
    Rect.right  = (Rect.left + Rect.width);
    Rect.bottom = (Rect.top  + Rect.height); 


//
// Clipping
//

	// Limits.
	
	// #todo: 
	// Repensar os limites para uma janela.
	// Uma janela poder� ser maior que as dimens�es de um dispositivo.
	// mas n�o poder� ser maior que as dimens�es do backbuffer.
	// Ou seja: O dedicated buffer de uma janela deve ser menor que
	// o backbuffer.

    //if ( Rect.right  > SavedX ){  Rect.right  = SavedX;  }
    //if ( Rect.bottom > SavedY ){  Rect.bottom = SavedY;  }


    if ( Rect.left   < ClippingRect.left   ){  Rect.left   = ClippingRect.left;   }
    if ( Rect.top    < ClippingRect.top    ){  Rect.top    = ClippingRect.top;    }
    if ( Rect.right  > ClippingRect.right  ){  Rect.right  = ClippingRect.right;  }
    if ( Rect.bottom > ClippingRect.bottom ){  Rect.bottom = ClippingRect.bottom; }


//
// Draw
//

    // Draw lines on backbuffer.

    while (internal_height--)
    {
        my_buffer_horizontal_line ( 
            Rect.left, y, Rect.right, Rect.bg_color );
 
        y++;
        
        // #??
        // Porque podemos desejar escrever no backbuffer
        // um ret�ngulo que ultrapasse a �rea do frontbuffer.
        
        if ( UseClipping == TRUE ){
            if ( y > ClippingRect.bottom ){ break; };
        }
    };
}


/*
//#todo
void refresh_rectangle3( struct rect_d *rectangle );
void refresh_rectangle3( struct rect_d *rectangle )
{
    refresh_rectangle(....)
}
*/


/*
 * #todo 
 * kgws n�o pode acessar o lfb, devemos chamar o di�logo em x/video.c
 * 
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
 
void 
refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

    void *dest       = (void *)      FRONTBUFFER_ADDRESS;
    const void *src  = (const void*) BACKBUFFER_ADDRESS;


    // loop
    register unsigned int i=0;
    register unsigned int lines=0;
    unsigned int line_size=0; 
    register int count=0; 



    // screen line size in pixels * bytes per pixel.
    unsigned int pitch=0;  

    // rectangle line size in pixels * bytes per pixel.
    unsigned int internal_pitch=0;  

    unsigned int offset=0;

    // = 3; 24bpp
    int bytes_count=0;


    int FirstLine = (int) y;

    //int UseVSync = FALSE;
    int UseClipping = TRUE;


    // dc
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();


    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("refresh_rectangle: w h\n");
        panic       ("refresh_rectangle: w h\n");
    }

    line_size = (unsigned int) width; 
    lines     = (unsigned int) height;

    switch (SavedBPP){

        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        // ... #todo
        
        default:
            panic ("refresh_rectangle: SavedBPP");
            break;
    };

//
// Pitch
//
    // Screen line size in pixels plus bytes per pixel.
    pitch = (unsigned int) (bytes_count * deviceWidth);

    // rectangle line size in pixels * bytes per pixel.
    internal_pitch = (unsigned int) (bytes_count * line_size);



	// #aten��o.
	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );

    offset = (unsigned int) ( (y*pitch) + (bytes_count*x) );


    dest = (void *)       (dest + offset); 
    src  = (const void *) (src  + offset); 


	// #bugbug
	// Isso pode nos dar problemas.
	// ?? Isso ainda � necess�rio nos dias de hoje ??

    //if ( UseVSync == TRUE){
        //vsync();
    //}


	//(line_size * bytes_count) � o n�mero de bytes por linha. 

	//#importante
	//� bem mais r�pido com m�ltiplos de 4.	


    // Se for divis�vel por 4.
    // Copia uma linha ou um pouco mais caso n�o seja divis�vel por 4.
    if ( (internal_pitch % 4) == 0 )
    {
        // 'strength reduction'
        // count = ( internal_pitch / 4 ); 
        count = ( internal_pitch >> 2 );  //#todo: Use this one.

        // Copy lines
        for ( i=0; i < lines; i++ )
        {
            // N�o copiamos a parte que est� fora da janela do dispositivo.
            if ( UseClipping == TRUE ){
                if ( (FirstLine + i) > deviceHeight ){ break; }
            }

            memcpy32 ( (void *) dest, (const void *) src, count );
            dest += pitch;
            src  += pitch;
        };
        return;
    }

    // Se n�o for divis�vel por 4.
    if ( (internal_pitch % 4) != 0 )
    {
        // Copy lines
        for ( i=0; i < lines; i++ )
        {
            // N�o copiamos a parte que est� fora da janela do dispositivo.
            if ( UseClipping == TRUE ){
                if ( (FirstLine + i) > deviceHeight ){ break; }
            }
            
            memcpy ( (void *) dest, (const void *) src, internal_pitch );
            dest += pitch; 
            src  += pitch; 
        };
        return;
    }
}


// ??
// A ideia aqui � efetuar o refresh de um ret�ngulo 
// que esteja em um dado buffer.
// ?? Not tested yet

void 
refresh_rectangle2 ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    unsigned long buffer1,
    unsigned long buffer2 )
{  
	


	// #todo
	// Fazer a mesma otimiza�ao que fizemos na outra rotina de refresh rectangle.


    void *p       = (void *)       buffer1;  // destino.
    const void *q = (const void *) buffer2;  // origem.


    register unsigned int i=0;
    register unsigned int lines=0;
    unsigned int line_size=0; 
    register int count=0; 

    unsigned int offset=0;

	// = 3; //24bpp
    int bytes_count;

	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();	


	line_size = (unsigned int) width; 
	lines     = (unsigned int) height;


    switch (SavedBPP)
    {
		case 32:  bytes_count = 4;  break;
		case 24:  bytes_count = 3;  break;
		//#todo: default
    };


	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	offset = (unsigned int) ( (bytes_count*SavedX*(y)) + (bytes_count*(x)) );	

	
	p = (void *)       (p + offset);    
	q = (const void *) (q + offset);    

    //if( use_vsync)
    //vsync ();

	
	//(line_size * 3) � o n�mero de bytes por linha. 
	
	//se for divis�vel por 4.
    if ( ((line_size * 3) % 4) == 0 )
    {
        count = ((line_size * 3) / 4);  	

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso n�o seja divis�vel por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * 3);
	 	    p += (Width * 3);
	    };
    }

	//se n�o for divis�vel por 4.
    if ( ((line_size * 3) % 4) != 0 )
    {

        //count = (line_size * 3);  		
	
	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * 3) );
		    q += (Width * 3);
		    p += (Width * 3);
	    };
    }

	/*
	
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	
	*/
}


// Inicializando a estrutura de gerenciamento de ret�ngulo salvo.

int initialize_saved_rect (void){

	printf ("initialize_saved_rect:\n");
	
	// Alocando mem�ria para a estrutura de gerenciamento do ret�ngulo.

    SavedRect = (void *) kmalloc ( sizeof(struct saved_rect_d) );   

    if ( (void *) SavedRect ==  NULL ){
        panic ("initialize_saved_rect: struct\n");
    } else {
     
        // #bugbug
        // Size of this allocation. Too much space??
     
        // 800x600x3 (resolu��o m�xima) 351+ p�ginas.
        //com isso poderemos salvar uma tela nessa resolu��o.
        SavedRect->buffer_address = (void *) allocPages (360);

        if ( (void *) SavedRect->buffer_address == NULL )
        {
            panic ("initialize_saved_rect: buffer fail\n");
        }

        SavedRect->x = 0; 
        SavedRect->y = 0;
        SavedRect->width = 0;
        SavedRect->height = 0;

        SavedRect->pixels = 0;
        SavedRect->bytes = 0;
        SavedRect->bpp = 0;

        SavedRect->full = 0;   //empty
		
		
		//#todo: limpar o buffer ???
		
	    //...
	};		

	//#debug
	printf ("initialize_saved_rect: done\n");
	//refresh_screen();

	//while (1){ asm ("hlt"); }
	
    return 0;
}


//#testando ...
//salvar um ret�ngulo no buffer ser� semelhante ao m�todo de 
//salvar um bmp em um arquivo.

int 
save_rect ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

        //#debug
        //Ok. est� pegando os valores certos.
        //printf ("l=%d t=%d w=%d h=%d \n", x, y, width, height );
        //refresh_screen();
        //while(1){}


    if ( (void *) SavedRect ==  NULL ){
        printf ("save_rect: SavedRect\n");
        return (int) 1;
    }else{

        if ( (void *) SavedRect->buffer_address == NULL )
        {
            panic ("save_rect: buffer fail");
        }
    };


    // ## transferindo ... ##
    //======================
    //do backbuffer para o buffer de salvamento.


    void *p = (void *) SavedRect->buffer_address;    //(buffer para salvar)
    const void *q = (const void *) BACKBUFFER_ADDRESS;

	//register unsigned int i;
    unsigned int i;

    unsigned int line_size, lines;

	// = 3; //24bpp
    int bytes_count;

    unsigned int offset1;  
    unsigned int offset2;  

    unsigned long Width  = (unsigned long) screenGetWidth ();
    unsigned long Height = (unsigned long) screenGetHeight ();

    int count; 


   
        
    /*
    //#isso funcionou usando o buffer de salvamento.
    refresh_rectangle2 ( 0, 0, 400, 400, SavedRect->buffer_address, BACKBUFFER_ADDRESS );
    refresh_rectangle2 ( 0, 0, 800, 600, BACKBUFFER_ADDRESS, SavedRect->buffer_address);
    //move do backbuffer para o lfb
    refresh_rectangle ( 0, 0, 800, 600); 
    while(1){}
    */
    
    
    // #test
    // Salvando 
    
    refresh_rectangle2 ( 
        x, y, width, height, 
        (unsigned long) SavedRect->buffer_address, 
        (unsigned long) BACKBUFFER_ADDRESS );

// done:

    return 0;
}


/*
 * show_saved_rect:
 *      Pintar no backbuffer o ret�ngulo salvo.
 *      Semelhante ao processo de decodificar um bmp, copiando 
 * do arquivo para o backbuffer.
 * Esses argumentos representam o posicionamento desejado do 
 * ret�ngulo no backbuffer. 
 */

int 
show_saved_rect ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

	// Checando a estrutura que tem informa��es 
	// sobre o ret�ngulo salvo.
	
	if ( (void *) SavedRect ==  NULL )
    {
        printf ("show_saved_rect: SavedRect\n");
	    return (int) 1;
		
	} else {

	    if ( (void *) SavedRect->buffer_address == NULL )
	    {
		    panic ("show_saved_rect: buffer");
	    }
    };
    
    
    
    //#test
    //copiando do buffer de salvamento para o backbuffer.
    refresh_rectangle2 ( x, y, width, height, 
        (unsigned long) BACKBUFFER_ADDRESS, 
        (unsigned long) SavedRect->buffer_address);    
    return 0;
    
    
    //
    //  ----- CUT HERE -------------
    //

	
    //
    // ## Transferindo ... ##
    //
	
	void *p = (void *) BACKBUFFER_ADDRESS;
	const void *q = (const void *) SavedRect->buffer_address;

	//register unsigned int i;
	unsigned int i;
	
	int count; 
	
	// = 3; //24bpp
	int bytes_count;  
	
	unsigned int offset1;  //offset dentro do buffer de salvamento.
	unsigned int offset2;  //offset dentro do backbuffer
	
	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();

	unsigned int line_size, lines;
	
	line_size = (unsigned int) width; //passado por argumento
	lines = (unsigned int) height;    //passado por argumento
	
	
	switch (SavedBPP)
	{
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
	};



   //p backbuffer
	offset1 = (unsigned int) ( ( bytes_count * SavedX * (y) ) + ( bytes_count * (x) ) );


    //q buffer de salvamento.
    //o conte�do salvo est� no in�cio do buffer de salvamento
	offset2 = 0;


    p = (void *) (p + offset1);          //backbuffer.
    q = (const void *) (q + offset2);    //buffer de salvamento


    /*
    //#debug
    //copiando todo o buffer de salvamento no backbuffer,
    //e mostrando o backbuffer.
    //memcpy32 ( (void *) BACKBUFFER_ADDRESS, (const void *) SavedRect->buffer_address, 
    //    (Width * 3)*400);
    //refresh_screen();
    //while(1){}
    */
 
    // #importante:
	// N�o precisa de sincroniza��o pois n�o estamos enviando para o LFB.
	// vsync ();
	
	//(line_size * 3) � o n�mero de bytes por linha. 
	
	//se for divis�vel por 4.
	if ( ((line_size * 3) % 4) == 0 )
	{
        count = ((line_size * 3) / 4);

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso n�o seja divis�vel por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * 3);
	 	    p += (Width * 3);
	    };
	}

	//se n�o for divis�vel por 4.
	if ( ((line_size * 3) % 4) != 0 )
	{

        //count = (line_size * 3);

	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * 3) );
		    
		    q += (Width * 3);
		    p += (Width * 3);
	    };
	}


    //#debug
    //printf ("show_saved_rect: done\n");

    return 0;
}



/*
 ************************* 
 * scroll_screen_rect:
 * 
 *     Scroll a rectangle. ?
 */

// Helper function to scroll routine.
// Called by console_scroll() in tty/console.c

void scroll_screen_rect (void){

    register unsigned int i=0;

    unsigned int line_size=0;  // w 
    unsigned int lines=0;      // h

    unsigned int offset=0;

    // Device info.
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();


    //int cWidth = get_char_width ();
    int cHeight = get_char_height ();

	// = 3; 
	//24bpp
    int bytes_count = 0;
    
    int count = 0; 


    // #debug
    //debug_print ("scroll_screen_rect:\n");

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("scroll_screen_rect: [PANIC] w h\n");
        panic       ("scroll_screen_rect: [PANIC] w h\n");
    }

    // #debug
    //if(cHeight == 8)
        //debug_print("8\n");

    // #debug
    //if(cHeight == 16)
        //debug_print("16\n");


    line_size = (unsigned int) deviceWidth; 
    lines     = (unsigned int) deviceHeight;

    switch (SavedBPP){
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        // ...
        default:
            panic("scroll_screen_rect: SavedBPP");
            break;
    };


//
// Pointers
//

    // Destination and Source.
    // Destination is the first line.
    // Source is the second line. It has the height of a char.

    void *Dest = (void *) BACKBUFFER_ADDRESS;
    const void *Src  = (const void *) BACKBUFFER_ADDRESS + ( bytes_count * SavedX * cHeight ) ;


    //
    // Copy.
    //

	//#importante
	//� bem mais r�pido com m�ltiplos de 4.	


    // Se for divis�vel por 4.
    // Copia uma linha, quatro bytes de cada vez.  
        
    if ( ((line_size * bytes_count) % 4) == 0 )
    {
        // #todo: Create a variable for 'pitch' and use streigh reduction
        count = ((line_size * bytes_count) / 4); 
        // count = (internal_pitch>>2);  // #todo: Use this one.

        for ( i=0; i < lines; i++ )
        {
            memcpy32 (Dest,Src,count);

            Src  += (deviceWidth * bytes_count);
            Dest += (deviceWidth * bytes_count);
        };
        return;
    }

    // Se n�o for divis�vel por 4.
    // Copia a linha, um bytes por vez.
    // #todo: Podemos suprimir esse if e deixarmos ssomente o for.
    
    if ( ((line_size * bytes_count) % 4) != 0 )
    {
        for ( i=0; i < lines; i++ )
        {
            memcpy ( 
                (void *) Dest, 
                (const void *) Src, 
                (line_size * bytes_count) );

            Src  += (deviceWidth * bytes_count);
            Dest += (deviceWidth * bytes_count);
        };
    }
}



//
// End.
//

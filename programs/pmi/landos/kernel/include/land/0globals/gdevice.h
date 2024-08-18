/*
 *  File: gdevice.h
 *
 * Defini��o:
 * Informa��es globais sobre a ger�ncia de dispositivos.
 * 
 * + Informa��es globais sobre o dispositivo onde o sistema operacional 
 * foi instalado.
 *
 * + Informa��es sobre o host device.
 *
 * + N�o � a qui o lugar para se detalhar todos os dispositivos instalados na m�quina.
 * Aqui � lugar de classificar a plataforma alvo para o sistema operacional. Para
 * que as aplica��es possam se adaptar �s caracter�sticas do dispositivo que suportam
 * o sistema operacional.
 *
 * Vers�o 1.0, 2016 - Created.   
 */
 
 
#ifndef ____GDEVICE_H
#define ____GDEVICE_H 1
 
 

// See: devices/devices.h
 
 
/*
 * driver_type_t: 
 *     Tipos de drivers. 
 *     + O driver de sistema � do tipo persistente. N�o poder� ser descarregado,
 * permanecer� na mem�ria o tempo todo. Poder� ser desativado. Pode estar 
 * em qualquer ring.
 *     + O driver modular poder� ser descarregado. 
 */ 
typedef enum {
	DriverTypeSystem,     //Persistente.
	DriverTypeModular,    //Modular.
	//...
}driver_type_t; 
 
 
/*
 * host_device_type_t:
 *     Classes de dispositivos segundo o host que pertencem.
 *     Classes mais comuns de dispositivos.
 *     Outras poder�o ser inclu�das futuramente. 
 */ 
typedef enum {
	HostDeviceTypePC,        //PC.
	HostDeviceTypeMobile,    //Mobile.
	HostDeviceTypeIOT,       //Iot.
	//...
}host_device_type_t; 


 
struct host_device_info_d
{
	//Type.
    host_device_type_t type;
	
	
	//Screen size.
	unsigned long host_device_screen_width;
	unsigned long host_device_screen_height;

    //Continua ...
	
};
typedef struct host_device_info_d  host_device_info_t; 

// devmgr.c
extern host_device_info_t *HostDeviceInfo; 
//

/*
 * #bugbug essa estrutura ja deve ter sido definida em outro lugar , por isso 
 * esta dando problemas.
 * @todo: tirar o x.
 *
typedef struct xdevice_driver_d xdevice_driver_t;
struct xdevice_driver_d
{
	driver_type_t driver_type;  //do sistema ou modular.
	
	struct host_device_info_d *device_info;
	
	int status;  //habilidado ou desabilitado.
	
	//...
};
*/
 
// 
// Globais de f�cil acesso.
// devem refletir os valores armazenados na estrutura.
//

//Screen sizes and bpp.
extern unsigned long g_device_screen_width;
extern unsigned long g_device_screen_height;
extern unsigned long g_device_screen_bpp; 


#endif   

 

//
// End.
//


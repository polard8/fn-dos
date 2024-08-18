// gws.h 


#include "gws00.h"


// rtl
#include <types.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <rtl/gramado.h>

 
#include "globals.h"


// #view
#include "view/render/r_render.h"
#include "view/colors.h"
#include "view/bitblt.h"
#include "view/char.h"
#include "view/dtext.h"
#include "view/line.h"
#include "view/vk.h"       // # view input events
#include "view/wt.h"
#include "view/menu.h"

#include "view/xxxinput.h"   //#test

#include "view/window.h"
#include "view/bmp.h"

// h:0.0
#include "view/screen.h"   // X-like
#include "view/display.h"  // X-like
#include "view/host.h"     // X-like h:0.0

// Teremos isso aqui no window server,
// kgws é outro ws par ao ambiente de setup e tera 
// seu próprio gerenciamento.

#include "view/security.h"


#include "view/gui.h"
#include "view/comp.h"
#include "view/event.h"    // view inputs
// ...


#include "view/grprim.h"


#include "view/sprite.h"

#include "view/demos.h"


// # data model
#include "model/packet.h"


// # model. business logic
// #todo:
// We can put this thing in the library. (libgws)
// or (libcon)
#include "model/connect.h"

// data model

#include "model/nc2.h"   //nelson cole 2 font. 8x8
#include "model/lt8x8.h"
// ...
#include "model/font.h"




// Client structure.
// O proprio servidor poderia ser o cliente 0??

#include "model/client.h"


// # model. business logic
#include "model/services.h"

#include "gwszz.h"





//
// End.
//



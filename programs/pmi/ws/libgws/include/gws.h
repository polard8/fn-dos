// gws.h 
// Client-side library for 32bit FN-DOS display server.
// 2020 -  Created by Fred Nora.


// =======================================
// Protocol request constants
//
// #todo:
// Create a consistent interface.
// See: xxxHandleNextClientRequest() and gwsProcedure on aurora/server/main.c 
// See: 
// All the standar messages, just like MSG_SYSKEYUP ...
// There are some old messages below 369.

#define GWS_GetInputMessage        369
#define GWS_Hello                 1000
#define GWS_CreateWindow          1001
#define GWS_BackbufferPutPixel    1002
#define GWS_DrawHorizontalLine    1003
#define GWS_DrawChar              1004
#define GWS_DrawText              1005
#define GWS_RefreshWindow         1006
#define GWS_RedrawWindow          1007
#define GWS_ResizeWindow          1008
#define GWS_ChangeWindowPosition  1009
#define GWS_BackbufferPutPixel2   2000
#define GWS_Disconnect            2010
#define GWS_RefreshScreen         2020
#define GWS_RefreshRectangle      2021
//#define GWS_GetSendEvent          2030  // send event #
#define GWS_GetNextEvent          2031
#define GWS_GrPlot0               2040
#define GWS_GrCubeZ               2041
#define GWS_GrRectangle           2042
#define GWS_AsyncCommand          2222
#define GWS_DrainInput            8080
// ...

// internal
// used only by the lib
#define __PORTS_WS  4040
#define __PORTS_NS  4041
#define __PORTS_FS  4042
// ...

#define __IP(a, b, c, d)  (a << 24 | b << 16 | c << 8 | d)

//
// window
//

// Virtual keys.
#include "window/vk.h"
// Window Messages.
#include "window/wm.h"
// Window types.
#include "window/wt.h"
// Colors.
#include "window/colors.h"
// Windows.
#include "window/window.h"

//
// host
//

//h:d.s
#include "host/screen.h"
#include "host/display.h"
#include "host/host.h"


#include "ports.h"

// menu
#include "window/menu.h"


// Events.
#include "io/events.h"


// Connecting with the ws.
//#include "connect.h"

#include "gws_pack.h"

// Read and write from socket.
#include "io/rw.h"

// 3d graphics support.
#include "gr/gr.h"


#include "libgws00.h"


//
// End.
//






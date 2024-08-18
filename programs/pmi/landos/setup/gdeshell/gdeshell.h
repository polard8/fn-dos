//
// File: gdeshell.h 
// 2016 - Created by Fred Nora.
//


// Setup current compiler 

#include "compiler.h"

// rtl
#include <sys/ioctl.h>
#include <sys/ioctls.h>
#include <types.h>
#include <stddef.h>
#include <stdarg.h>   
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <termios.h>
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/wait.h> 

// gdeshell stuff 
#include "globals.h"
#include "builtins.h"

// libcore
#include <api.h>


//# bash 1.05 stuff #
#include "variables.h"
#include "general.h"
#include "flags.h"
#include "alias.h"
#include "ndir.h"
#include "version.h"

// tests
#include "tests.h"

// net tests
#include "net.h"

#include "inc00.h"


//
// =================================================
//

//
// End.
//








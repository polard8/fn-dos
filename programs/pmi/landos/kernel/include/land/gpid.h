// gpid.h
// Managing the helper processes.
// Created by Fred Nora.

#ifndef __GPID_H
#define __GPID_H    1

// First of all.
// we need to register some processes.
// Registering 'folders'.

// 1) boot/
// This is the pre-kernel stuff.
// Register this folder is gonna be a noop.
// oops. pode existir nessa pasta também um processo
// de configuração da inicialização. why not?!
extern pid_t __gpidBoot;
//int register_bootsrv_process ( pid_t pid );


// 2) include/
extern pid_t __gpidInclude;
//int register_include_process ( pid_t pid ); //Noop!


// 3) init/
// init.bin
extern pid_t __gpidInit;
//int register_init_process ( pid_t pid );

// 4) install/
extern pid_t __gpidInstall;
//??

// 5) logoff
extern pid_t __gpidLogoff;


// 6) logon/
extern pid_t __gpidLogon;


// 7) net/
// The net server.
// netsrv.bin
extern pid_t __gpidNetServer;
//int register_netsrv_process ( pid_t pid );


// 8) notify/
extern pid_t __gpidNotificationServer;
//int register_notify_process ( pid_t pid );


// 9) sci/
// SCIServer ??
extern pid_t __gpidSCI;
// ??

// 10) security/
extern pid_t __gpidSecurityServer;
// ??

// 11) 
extern pid_t __gpidSysIO;
// ??

// 12)
extern pid_t __gpidSysLib;
// ??

// 13) sysmk/
extern pid_t __gpidSysMK;
// ??

// 14) syssm/ 
//system management
// system server
extern pid_t __gpidSysSM;
// ??

// 15) wm/
// See: kgwm.c
extern pid_t __gpidWindowManager;

// 16) ws/
// See: kgws.c
extern pid_t __gpidWindowServer;

//
//
//

int register_logoff_process ( pid_t pid );
int register_logon_process ( pid_t pid );
int register_wm_process ( pid_t pid );
int register_ws_process ( pid_t pid );

#endif   


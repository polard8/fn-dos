/*
 * File: kernel/0mem/main.c
 *     This is the main file for the kernel.
 *     It's architecture independent.
 *     The Assembly code passed the control for us, so now
 * we're gonna do some architechture intependent initialization
 * and call the next part of the architechture dependent stuff.
 *
 * History:
 *     2019 - Created by Fred Nora.
 *     2020 -
 */


// It starts with the kernel data and
// it has the main routine for the kernel.


#include <kernel.h>

// see: minit.h
struct initialization_d  Initialization;

// up.h
struct ProcessorBlock_d  UPProcessorBlock;    


struct processor_d *processor;

//processors count
int processors_count=0;

// all processors's structs.
// ProcessorBlock_d
unsigned long processorsList[PROCESSORS_MAX_COUNT];

// kernel.h
struct io_control_d  IOControl;

// Global
// see: gspin.h
int __spinlock_ipc=0;

int ____whatchdog_ps2_keyboard=0;
int ____whatchdog_ps2_mouse=0;
//...


// see: terminal.h
// Vamos contar os terminais criados.
int terminal_count=0;
int terminalLine=0;       //Troca de linha;(up down)
int terminalOffset=0;     //Deslocamento dentro da linha; (left right).
int terminalLineMax=0;   //N�mero m�ximo de linhas suportadas.
int terminalOffsetMax=0;  //N�mero m�ximo de caracteres por linha.

// see: terminal.h
struct terminal_d  TERMINAL[TERMINAL_COUNT_MAX];


// security.h
int current_usersession=0;
int current_room=0;
int current_desktop=0; 


// timer interrupt
// kdrivers/timer.c
int __breaker_timer_initialized=0;

// ps2 keyboard
// x/i8042/ps2kbd.c
int __breaker_ps2keyboard_initialized=0;

// Serial ports.
// See: kdrivers/serial.c
int __breaker_com1_initialized=0;
int __breaker_com2_initialized=0;
int __breaker_com3_initialized=0;
int __breaker_com4_initialized=0;

// real time clock
// kdrivers/rtc.c
int __breaker_rtc_initialized=0;

// ps2 mouse
// x/i8042/ps2mouse.c
int __breaker_ps2mouse_initialized=0;

// ata
// kdrivers/ide/ata.c
int __breaker_ata1_initialized=0;
int __breaker_ata2_initialized=0;

//...





int system_disk=0;
int system_volume=0;


int gLogonPID=0;
int gLogoffPID=0;


//?? rever esse coment�rio.
// Aqui salvaremos o n�mero que identifica o tipo de sistema dado o tamanho.
// Se o sistema tiver 288 MB ou mais ent�o ele ser� do tipo Full
// e conter� 8 bancos de mem�ria de 32Mb mais uma user session de tamnaho variado.
int systemSize;

//Flag para habilitar as op��es para o desenvolvedor.
int gDeveloperOptions;

// ??
int gSystemEdition;

int gSystemStatus; //?? Usado pelo construtor.

unsigned long shutdown_address=0;

// see: system.h
struct version_d  *Version;
struct version_info_d *VersionInfo;
struct system_d *System;

int g_is_qemu=0;

// Salvando o �ltimo endere�o v�lido de mem�ria ram.
// usado em head.asm
unsigned long blSavedLastValidAddress=0;
unsigned long blSavedMetafileAddress=0;
unsigned long blSavedDiskNumber=0;
unsigned long blSavedHeads=0;
unsigned long blSavedSPT=0;
unsigned long blSavedCylinders=0;
//...

// see: gdef.h
struct boot_block_d  BootBlock;


unsigned long g_frontbuffer_va=0;
unsigned long g_frontbuffer_pa=0;

unsigned long g_backbuffer_va=0;
unsigned long g_backbuffer_pa=0;


int gNextKeyboardMessage=0;



// pints.h
unsigned long g_profiler_ints_gde_services=0;

// pints.h
unsigned long g_profiler_ints_irq0=0;  // kdrivers/timer.c
unsigned long g_profiler_ints_irq1=0;  // x/i8042/keyboard.c
unsigned long g_profiler_ints_irq2=0;  // cascade.
unsigned long g_profiler_ints_irq3=0;  //
unsigned long g_profiler_ints_irq4=0;  //
unsigned long g_profiler_ints_irq5=0;  //
unsigned long g_profiler_ints_irq6=0;  //
unsigned long g_profiler_ints_irq7=0;  //
unsigned long g_profiler_ints_irq8=0;   // kdrivers/rtc.c
unsigned long g_profiler_ints_irq9=0;   // kdrivers/network/nicintel.c
unsigned long g_profiler_ints_irq10=0; //
unsigned long g_profiler_ints_irq11=0;  //
unsigned long g_profiler_ints_irq12=0;  // x/i8042/mouse.c
unsigned long g_profiler_ints_irq13=0;  //
unsigned long g_profiler_ints_irq14=0;  // kdrivers/kdrivers/ide/atairq.c
unsigned long g_profiler_ints_irq15=0;  // kdrivers/kdrivers/ide/atairq.c


unsigned long kernel_request=0;

// see: request.h
struct request_d  REQUEST;

// First of all.
// we need to register some processes.
// Registering 'folders'.

// 1) boot/
// This is the pre-kernel stuff.
// Register this folder is gonna be a noop.
// oops. pode existir nessa pasta também um processo
// de configuração da inicialização. why not?!
pid_t __gpidBoot=0;

// 2) include/
pid_t __gpidInclude=0;

// 3) init/
// init.bin
pid_t __gpidInit=0;

// 4) install/
pid_t __gpidInstall=0;

// 5) logoff
pid_t __gpidLogoff=0;

// 6) logon/
pid_t __gpidLogon=0;

// 7) net/
// The net server.
// netsrv.bin
pid_t __gpidNetServer=0;

// 8) notify/
pid_t __gpidNotificationServer=0;

// 9) sci/
// SCIServer ??
pid_t __gpidSCI=0;

// 10) security/
pid_t __gpidSecurityServer=0;

// 11) 
pid_t __gpidSysIO=0;
// ??

// 12)
pid_t __gpidSysLib=0;
// ??

// 13) sysmk/
pid_t __gpidSysMK=0;
// ??

// 14) syssm/ 
//system management
// system server
pid_t __gpidSysSM=0;
// ??

// 15) wm/
// See: kgwm.c
pid_t __gpidWindowManager=0;

// 16) ws/
// See: kgws.c
pid_t __gpidWindowServer=0;



int abnt2=0;

//Type of product.
int g_product_type=0;


// GRAMADO_JAIL, GRAMADO_P1 ...
int current_mode=0;

// INPUT_MODE_SETUP, INPUT_MODE_WS ...
//int current_input_mode;

// x86 ...
int current_arch=0;

// Organização de usuários.
int current_user=0;
int current_group=0;

int foreground_process=0;
int foreground_thread=0;

int current_process=0;   // Currently having the processing time.
int current_thread=0;    // Currently having the processing time.

int criticalsection_pid=0;


// see: main.c
// [Focus]
int active_process=0;    // This is the process with the active thread.
int active_thread=0;     // This thread will receive the input.

// see: main.c
//[Scheduler]
int next_thread=0;     //next user mode thread.

// Current runlevel. Used in init process.
int current_runlevel=0;
// Organização dos discos.
int current_disk=0;
int current_volume=0;
// Organização dos arquivos.
int current_directory=0;
int current_file=0;
int current_dead_process=0;
int current_dead_thread=0;
// Organização dos terminais
int current_tty=0;
int current_terminal=0;
//int current_pty=0;
//int current_pts=0;


//size of processor word.
int g_platform_type=0;

//se ele est'a inicializado ou nao
int dead_thread_collector_status=0;

// se 'e para usalo ou nao
int dead_thread_collector_flag=0;

//cr3. current page directoory address.
unsigned long current_process_pagedirectory_address=0;


// Logon.
int g_logged=0;

// GUI
//flag.
//If the kernel is in graphics mode.
int g_useGUI=0;

//Messages support.
unsigned long g_new_message=0;
unsigned long g_next_app=0;       // Procedure adreess.
unsigned long g_proc_status=0;    // Procedure status.

// Drivers support.
int g_driver_ps2keyboard_initialized=0;   //ps2 keyboard
int g_driver_ps2mouse_initialized=0;      //ps2 mouse
int g_driver_video_initialized=0;
int g_driver_apic_initialized=0;
int g_driver_hdd_initialized=0;
int g_driver_pci_initialized=0;
int g_driver_rtc_initialized=0;
int g_driver_timer_initialized=0;
//...

int g_module_shell_initialized=0;
int g_module_debug_initialized=0;
int g_module_disk_initialized=0;
int g_module_volume_initialized=0;
int g_module_fs_initialized=0;
int g_module_gui_initialized=0;
int g_module_logoff_initialized=0;
int g_module_logon_initialized=0;
int g_module_mm_initialized=0;
int g_module_objectmanager_initialized=0;
int g_module_runtime_initialized=0;
int g_module_uem_initialized=0;    //user environment manager.
//...

// Kernel information variables.
unsigned long KernelSize=0;
unsigned long KernelHeapSize=0;
unsigned long KernelStackSize=0;
unsigned long KernelPages=0;
unsigned long KeInitPhase=0;
unsigned long KernelStatus=0;
//...

int g_kernel_symbols_available=0;
unsigned long kernel_switch=0;
unsigned long errno=0;


// kernel00.h
struct kernel_args_d  KernelArgs;
struct system_classes_d  SystemClasses;
struct kernel_classes_d  KernelClasses;
struct platform_d  *Platform; 


// This variables came from BL.BIN.

// The boot mode. CLI or GUI.
extern unsigned long SavedBootMode;

// Boot Block address.
extern unsigned long SavedBootBlock;



//
// == kernel data ==============================
//

// char copyright[] =
// "Copyright (c) 2005-2020 \n\tFred Nora. All rights reserved.\n\n";


// Salvaremos aqui o endereço da idle thread.
// Isso podera ser importado pelo assembly.
// unsigned long Ring0IdleThreadAddress;


// Algum componente em ring0 pode configurar esse callout
// o assmebly pode importar e chamar isso.
// Entao com isso rodariamos uma rotina em ring0 mas fora do kernel.
// unsigned long Ring0CallOut;


// ...


/*
//#test
// The problem here is the variables are imported from 'ld'.
// Thats not what we want.
// We wanna build gramado with our own compiler.
extern unsigned long bss_begin;
extern unsigned long bss_end;
static void clear_bss(void)
{
    memset ( 
        bss_begin,              // start 
        0,                      // data
        bss_end - bss_begin );  // size
}
*/


/*
struct kernel_d
{
    int hasBooted;
    void *scheduler;
};
struct kernel_d Kernel;
*/


// internal
// #todo: Talvez isso precise retornar int.

void preinit_Globals(int arch_type)
{

//
// == Boot block ======================================
//

    //See:
    //landos/kernel/include/land/0globals/gdef.h
    
    BootBlock.initialized = FALSE;

    unsigned long *base = (unsigned long *) SavedBootBlock;

    // #todo
    // Check address validation
    
    //if ( (void *) == NULL ){
        //FAIL
    //}

    BootBlock.bootblock_address  = (unsigned long) SavedBootBlock;
    BootBlock.lfb                = (unsigned long) base[0];  //  0
    BootBlock.x                  = (unsigned long) base[1];  //  4
    BootBlock.y                  = (unsigned long) base[2];  //  8
    BootBlock.bpp                = (unsigned long) base[3];  // 12
    BootBlock.last_valid_address = (unsigned long) base[4];  // 16
    BootBlock.metafile_address   = (unsigned long) base[5];  // 20
    BootBlock.disk_number        = (unsigned long) base[6];  // 24
    BootBlock.heads              = (unsigned long) base[7];  // 28
    BootBlock.spt                = (unsigned long) base[8];  // 32
    BootBlock.cylinders          = (unsigned long) base[9];  // 36
    BootBlock.boot_mode          = (unsigned long) base[10]; // 40
    BootBlock.gramado_mode       = (unsigned long) base[11]; // 44
    BootBlock.initialized = TRUE;

    // ==============================================

    // Kernel status.
    KernelStatus = KERNEL_NULL;

    // Current arch support.
    // We received this arg from Assembly.

    current_arch = arch_type;


    // runlevel
    
    current_runlevel = DEFAULT_RUNLEVEL;
    //current_runlevel = 5;

    // Kernel symbol table.
    // #todo: maybe we will load a kernel.map file.
    g_kernel_symbols_available = FALSE;


    //
    // == gramado mode =============================================
    //

    // The 'gramado mode' or 'gamemode'.
    // jail,p1,home,p2,castle
    // We can't check right here ...
    // there is no messages yet.

    // Saving
    // It is used by the kernel info.
    current_mode = (char) BootBlock.gramado_mode;


//
// == No preemptions ==============================
//

    // Para evitar que exista qualquer tipo de preempção
    // devemos usar essas flags, que serão destravadas
    // no fim da rotina do processo init.bin.

    // #bugbug
    // Talvez alguma rotina de carregamento de arquivo esteja
    // usando essas flags e travando e destravando isso.
    // Uma delas pode destravas antes mesmo o processo init
    // fazer seu trabalho.

    // Disable interrupts, lock taskswitch and scheduler.
    //Set scheduler type. (Round Robin).
    // #todo: call a hal routine for cli.

    asm ("cli");  // #todo: isso é dependente da arquitetura.
    taskswitch_lock();
    scheduler_lock();
    schedulerType = SCHEDULER_RR; 

    // Initializing the global spinlock.
    // #todo: Isso pode ir para init_globals

    //## pre initialization globals.

    __spinlock_ipc = TRUE;



//
// == input mode =============================================
//

    // #deprecated

    // This is the default initial input mode.
    // This mode is gonna change only when we load
    // a ring3 window server.
    
    //current_input_mode = INPUT_MODE_SETUP;

//
// IO Control
//

    IOControl.useTTY = FALSE;        // Model not implemented yet.
    IOControl.useEventQueue = TRUE;  // The current model.
    IOControl.initialized = TRUE;


//
// == Verbose mode ================================
//

	// #obs:
	// Verbose mode do kernel.
	// Initializes a new line when '\n' is found.

    stdio_verbosemode_flag = TRUE;

    // ...
}

// internal
// #todo: Talvez isso precise retornar int.
void preinit_Serial(void)
{
    // Serial
    // See: bottom/dd/serial/serial.c

    serial_init();
}

// internal
// #todo: Talvez isso precise retornar int.
void preinit_OutputSupport(void)
{
    // Virtual Console.
    // See: user/console.c
    debug_print ("[Kernel] kernel_main: Initializing virtual consoles ...\n");
    VirtualConsole_initialize();
}


/*
 ********************************************
 * kernel_main:
 *
 *  Gramado OS kernel C entry point. :)
 * 
 *  This is where C execution begins, after head.asm 
 *  transfers control here.
 * 
 *  The purpose is to initialize the virtual console support,
 *  the video support, the runtime support and starts the
 *  architecture initialization routine.
 * 
 */

// #progress
// name:level:sublevel

int kernel_main (int arch_type)
{
    int Status = (-1);


    // Globals
    // We do not have output yet

    preinit_Globals(arch_type);

    // Serial
    // We do not have output yet

    preinit_Serial();

    // =================================================
    
    //
    // #progress
    // name:level:sublevel
    //

    PROGRESS("---------------------\n");
    PROGRESS(" Initializing landos \n");
    // Now we have serial port output.

    // =================================================


    PROGRESS("Kernel:0:1\n");
    // Initialize the virtual console structures.
    // #IMPORTAT: We do not have all the runtime support yet.
    // We can't use printf yet.

    preinit_OutputSupport();


    PROGRESS("Kernel:0:2\n");
    // Show some basic info.

    debug_print ("Initializing landos kernel ...\n");



    /*
    // #test
    // precisamos importar essa vari'avel?
    if ( kernel_end >= (0xC0000000 + 0x300000) )
    {
        debug_print ("kernel_main: The kernel image is too large\n");
        asm volatile("cli;hlt");
    }
    */



    // ====================================
    // The mode.
    debug_print ("mode: ");

    switch (current_mode){
        // Standard modes.
        case GRAMADO_JAIL:   debug_print ("GRAMADO_JAIL\n");   break;
        case GRAMADO_P1:     debug_print ("GRAMADO_P1\n");     break;
        case GRAMADO_HOME:   debug_print ("GRAMADO_HOME\n");   break;
        case GRAMADO_P2:     debug_print ("GRAMADO_P2\n");     break;
        case GRAMADO_CASTLE: debug_print ("GRAMADO_CASTLE\n"); break;
        // Super modes.
        case GRAMADO_CALIFORNIA:  
            debug_print ("GRAMADO_CALIFORNIA\n"); 
            break;
        //case GRAMADO_CALIFORNIA2:  
        //    debug_print ("GRAMADO_CALIFORNIA2\n"); 
        //    break;
        // ...

        // We can't use printf yet.
        default:  
            debug_print ("[FAIL] Not defined\n");  
            goto fail1;
            break;
    };


    // ====================================
    // The architecture.
    debug_print ("arch: ");
    
    switch (current_arch){

        case CURRENT_ARCH_X86:  
            debug_print ("x86\n");  
            break;

        // We can't use printf yet.
        case CURRENT_ARCH_X86_64:
            debug_print ("x86_64 [FAIL] Not supported\n");
            goto fail1;
            break;
        // ...

        // We can't use printf yet.
        default:
            debug_print ("? [FAIL] Not defined\n");
            goto fail1;
            break; 
    };

    // ====================================
    PROGRESS("Kernel:0:3\n");
    // Video support


    debug_print ("[Kernel] kernel_main: Initializing video support ...\n");

    // First of all.
    // #ps:
    // Boot loader is mapping the LFB.

    // #todo:
    // Device screen sizes.

    // Set graphics mode or text mode using a flag.
    // #bugbug:
    // Text mode is not supported.

    if ( SavedBootMode == 1 ){
        g_useGUI          = GUI_ON;
        VideoBlock.useGui = GUI_ON;
        debug_print ("[Kernel] kernel_main: GUI_ON\n");
        // ...

    // We can't use printf yet.
    }else{
        g_useGUI          = GUI_OFF;
        VideoBlock.useGui = GUI_OFF;
        debug_print ("[Kernel] kernel_main: GUI_OFF\n");
        debug_print ("[Kernel] kernel_main: Text mode not supported! *hang");
        goto fail1;
    };


    if (VideoBlock.useGui == GUI_ON){
        debug_print ("[Kernel] kernel_main: Using GUI\n");
    }

    // ================================================

    // Now we will initialize the video support,
    // the runtime support and clean the background.
    // This way we're gonna be able to use 'printf'.

    //
    // Video
    //

    // In hid/video.c
    Video_initialize();


// ====================================

//
// Runtime
//

    PROGRESS("Kernel:0:4\n");
    // Runtime


    //
    // Runtime
    //

    // #bugbug:
    // We need the runtime initialization for the messages.
    // What about to initialize it early?! now!!!!
    // See: core/runtime.c

    // #bugbug
    // Here the background is not initialized yet,
    // so, we have a lot of dirty things.

    debug_print ("[Kernel] kernel_main: Initializing runtime\n");
    Runtime_initialize();


// =========================
    
    PROGRESS("Kernel:0:5\n");
    // Clear the screen.
    // print some basic info.

    //
    // Background
    //

    // Initializing background 
    // for the very first time.
    // Now we have a black screen.
    // But the cursor position is wrong yet.

    // See: user/draw/view/bg.c
    Background_initialize();


    // ================================================

    //
    // The first char!
    //
   
    // This is the first char ever for 
    // the new background.

    //See:
    //landos/kernel/include/land/0globals/gdef.h

    printf ("$\n");
    printf ("GRAMADO LAND\n");

    if ( BootBlock.initialized != TRUE ){
        panic ("kernel_main: [FAIL] BootBlock not initialized!\n");
    }

    printf ("Boot block address %x\n",BootBlock.bootblock_address);  
    printf ("lfb %x\n",BootBlock.lfb);
    printf ("x   %d\n",BootBlock.x);
    printf ("y   %d\n",BootBlock.y);
    printf ("bpp %d\n",BootBlock.bpp);
    printf (">>>  Gramado mode %d\n", BootBlock.gramado_mode);
    refresh_screen();

    // #debug
    // while(1){}



//=============================

    PROGRESS("Kernel:0:6\n"); 
    // Initialize current archtecture.


	// #todo
	// A partir daqui faremos inicializações de partes
	// dependentes da arquitetura.

    switch (current_arch){

        // See: x86/x86init.c
        case CURRENT_ARCH_X86:
            debug_print ("kernel_main: Initializing x86 arch ...\n");
            printf("kernel_main: Initializing x86 arch ...\n");
            Status = (int) x86main();
            if (Status < 0)
                panic("[Kernel] kernel_main: CURRENT_ARCH_X86 fail\n");
            break;

        // See:
        case CURRENT_ARCH_X86_64:
            printf("kernel_main: [FAIL] x86_64 is not supported!\n");
            debug_print ("[Kernel] kernel_main: [FAIL] x86_64 is not supported!\n");
            //Status = (int) x86_64main();
            goto fail2;
            break;

        // See:
        // armmain (); ??

        // ...

        default:
            debug_print ("kernel_main: [FAIL] Current arch not defined!\n");
            printf("kernel_main: [FAIL] Current arch not defined!");
            goto fail2;
            break;
    };


//=============================

    // Something is wrong
    PROGRESS("Kernel:0:7\n"); 
    debug_print ("kernel_main: Something is wrong\n");


//
// Fail
//

// Rule 22:
// " When in doubt, know your way out. "

// Full console support.
fail2:
    printf ("kernel_main: Fail. *HANG\n");
    refresh_screen();

// Only serial debug support.
fail1:    
    PROGRESS("Kernel:0:0\n"); 
    debug_print ("[Kernel] kernel_main-fail:  *hang \n");

// No output support.
fail0:
    return (int) (-1);
}



// == Idle thread in ring 0  ===============
// #test

// #bugbug
// This thread will start to run at the moment when
// the init process enable the interrupts.

void early_ring0_IdleThread (void)
{
// #danger: Do NOT change this function.
Loop:
    asm ("sti");
    asm ("hlt");
    goto Loop;
}


//
// End.
//


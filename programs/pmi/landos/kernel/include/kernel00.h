// kernel00.h
// Created by Fred Nora.

#ifndef __KERNEL00_H
#define __KERNEL00_H   1


// ==============================

// see: main.c
//keyboard suppport 
//abnt2 flag.
//#todo: Move this to another file.
//maybe gdef.h
extern int abnt2;
//...


// Product type.
typedef enum {
   PT_THINGS,        // Things.
   PT_EDGEDEVICES,   // Edge Devices.
   //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;

// see: main.c
//Type of product.
extern int g_product_type; 



// Platform type
typedef enum {
   PFT_16BIT,     // 16bit processor
   PFT_32BIT,     // 32bit processor
}PlatformType_t;

// UP ou MP
typedef enum {
    SYSTEM_TYPE_NULL,
    SYSTEM_TYPE_UNIPROCESSOR,
    SYSTEM_TYPE_MULTIPROCESSOR
} SystemType_t;



//
// == current ======================================================
//

// see: main.c
// GRAMADO_JAIL, GRAMADO_P1 ...
extern int current_mode;

// INPUT_MODE_SETUP, INPUT_MODE_WS ...
//int current_input_mode;

// see: main.c
// x86 ...
extern int current_arch;

// see: main.c
// Organização de usuários.
extern int current_user; 
extern int current_group; 


// Organização dos processos


// Process used by the console during the job control.
// #hackhack: 
// For now we are using the control thread associated with the
// window with focus.
// #todo
// But we need to use the control thread of the foreground process
// associated with the console TTY.

// see: main.c
extern int foreground_process;
extern int foreground_thread;

// see: main.c
// [Processing time]
// Only these can read the keyboard input.
// Sometime it's the terminal.
// It's child will read into a file.
extern int current_process;   // Currently having the processing time.
extern int current_thread;    // Currently having the processing time.

// see: main.c
extern int criticalsection_pid;

// see: main.c
// [Focus]
extern int active_process;    // This is the process with the active thread.
extern int active_thread;     // This thread will receive the input.

// see: main.c
//[Scheduler]
extern int next_thread;     //next user mode thread.

// see: main.c

// Current runlevel. Used in init process.
extern int current_runlevel;
// Organização dos discos.
extern int current_disk;
extern int current_volume;
// Organização dos arquivos.
extern int current_directory;
extern int current_file;
extern int current_dead_process;
extern int current_dead_thread;
// Organização dos terminais
extern int current_tty;
extern int current_terminal;
//extern int current_pty;
//extern int current_pts;

//...


// ==== ====


// main.c
//size of processor word.
extern int g_platform_type;

// main.c
//se ele est'a inicializado ou nao
extern int dead_thread_collector_status;

// main.c
// se 'e para usalo ou nao
extern int dead_thread_collector_flag;

// main.c
//cr3. current page directoory address.
extern unsigned long current_process_pagedirectory_address;


// main.c
// Logon.
extern int g_logged;

// main.c
// GUI
//flag.
//If the kernel is in graphics mode.
extern int g_useGUI; 


// main.c
//Messages support.
extern unsigned long g_new_message;
extern unsigned long g_next_app;       // Procedure adreess.
extern unsigned long g_proc_status;    // Procedure status.

// main.c
// Drivers support.
extern int g_driver_ps2keyboard_initialized;   //ps2 keyboard
extern int g_driver_ps2mouse_initialized;      //ps2 mouse
extern int g_driver_video_initialized;
extern int g_driver_apic_initialized;
extern int g_driver_hdd_initialized;
extern int g_driver_pci_initialized;
extern int g_driver_rtc_initialized;
extern int g_driver_timer_initialized;
//...

// main.c
// internal modules support.
extern int g_module_shell_initialized;
extern int g_module_debug_initialized;
extern int g_module_disk_initialized;
extern int g_module_volume_initialized;
extern int g_module_fs_initialized;
extern int g_module_gui_initialized;
extern int g_module_logoff_initialized;
extern int g_module_logon_initialized;
extern int g_module_mm_initialized;
extern int g_module_objectmanager_initialized;
extern int g_module_runtime_initialized;
extern int g_module_uem_initialized;             //user environment manager.
//...

// main.c
// Kernel information variables.
extern unsigned long KernelSize;
extern unsigned long KernelHeapSize;
extern unsigned long KernelStackSize;
extern unsigned long KernelPages;
extern unsigned long KeInitPhase;
extern unsigned long KernelStatus;
//...


// main.c
// symbol table
extern int g_kernel_symbols_available;

//Task support variables.

// main.c
extern unsigned long kernel_switch;

// main.c
//#bugbug
//move this to kernel (ring 0) crt support.
//error support.
extern unsigned long errno;

//
// fs support.
//

//directory entries support.
//char buffer_dir_entry[512];

//log buffer
//char KernelLogBuffer[512];



//
// Plataform support.
//

//environment variables.
#define PLATFORM_PATH  "/Platform"
#define HARDWARE_PATH  "/Platform/Hardware"
#define FIRMWARE_PATH  "/Platform/Firmware"
#define SYSTEM_PATH    "/Platform/System"
//#define USERS_PATH     "/Platform/Users"
//...


//node od a linked list.
struct node_d
{
    void *data;

    //struct window_d *window;
    //int msg;	
    //unsigned long long1;
    //unsigned long long2;
    
    struct node_d *flink;
    struct node_d *blink;    
};


//Linked list support.
struct linkedlist_d
{
    struct node_d *head;
    struct node_d *tail;
};


//save args support. 
struct kernel_args_d
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
}; 
extern struct kernel_args_d  KernelArgs;

//system classes.
struct system_classes_d
{
    //unsigned long Gramado; //@todo: Include this one.
    unsigned long Executive;
    unsigned long Microkernel;
    unsigned long Hal;
};
extern struct system_classes_d  SystemClasses;

//Kernel classes.
struct kernel_classes_d
{
    struct system_classes_d *System;
    //..
};
extern struct kernel_classes_d  KernelClasses;
//...



/*
//Kernel Manager.
struct kernel_d
{
    //
    // Kernel info.
    //

    char *name;
    unsigned long address;

    //Kernel information block.
    //struct kernel_block_d *KernelBlock;

    //struct process_d *process;

    //
    // Structs.
    //

    //struct bootmanager_d     *BootManagerBlock;  //Boot Manager.
    //struct bootloader_d      *BootLoaderBlock;   //Boot Loader.
	
    //struct system_d          *SystemBlock;       //System.
    //struct ProcessorBlock_d  *ProcessorBlock;    //Processor info.
    //...

    //
    // CPUs.
    //

    //int processorCount;
    //struct processor_d *processor;
    
	
    //kernel_args_t
    //kernel_classes_t

    //...
};
struct kernel_d *KernelInfo; 
*/
//...


/*
 * plataform_d:
 *     Basic machine components. Hardware and Software. 
 */

struct platform_d
{
    char *name;
    
    // UP or MP;
    SystemType_t system_type;

    struct hardware_d *Hardware;    // hal/hal.h
    struct firmware_d *Firmware;    // hal/hal.h
    struct system_d   *System;      // execve/sm/system.h

    //kernel struct ...
    //struct kernel_d *Kernel;


    // #test #todo
    // unsigned long vesa_lfb_pa;
    
    // void *kernel_entrypoint; 

    // Entry point for application processors.
    // 32 bit part.
    // void *ap_entrypoint;

    // ...
};
extern struct platform_d *Platform; 


#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...

//#define CURRENT_ARCH_ARM      2000
//...

//
// =============================
//


// inicialização do kernel, independente da arquitetura.
// See: kernel/main.c
int kernel_main (int arch_type);

//inicialização da arquitetura x86.
int x86main (void);
//...



//Save args in the structure.
void save_kernel_args (void);    


// Linked list support.

void* newLinkedlist (void);
void* newNode (void);

void Removing_from_the_beginning(struct linkedlist_d *list);
void Removing_from_the_middle(struct linkedlist_d *list);
void Removing_from_the_end(struct linkedlist_d *list);



//
// Count support.
//

//?? somente o protótipo. deletar.
//unsigned long get_tick_count ();


//
// Delay support.
//

void sleep (unsigned long ms);


//
// Finalizations support.
//

void faults (unsigned long number);



//
// Error support
// 

// panic without clean
void panic ( const char *format, ... );   //panic.c

// clean and panic.
void panic2 ( const char *format, ... );   //panic.c

void abort (void);    //abort.c
void die (void);      //system.c





#endif  


/*
 * File: shell.h
 *
 * Descri��o:
 *     Header para o mini-shell dentro do Boot Loader 32 bit.
 *
 * #todo: 
 *     Deixar o minishell enxuto, com poucos recursos.
 *     Deixar principalmente os recursos de configura��o 
 *     da inicializa��o.
 *
 * 2015 - Created by Fred Nora.
 */


// 
// Command support.
//


// Prompt support
extern char prompt[250];             
extern unsigned long prompt_pos;
extern unsigned long g_cmd_status;    //Quando o comando terminou. (string completa).

//
// == Prototypes ===============================================
//

int rescueShell(void);

void shellWaitCmd();
unsigned long shellCompare();
void shellHelp();
//...

//Initialization.
void shellInit();
int shellInitializePrompt();
//...

//Main
int blShellMain ( int argc, char *argv[] );


//
// End.
//


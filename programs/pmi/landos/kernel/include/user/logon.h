/*
 * File: ws/logon.h
 *     Kernel Mode Logon Support Routines.
 *     Header de suporte � cria��o do Logon.
 * OBS:
 *     O Logon est� na WindowStation0 e no Desktop0. 
 *     Existir� um processo em user mode para gerenciamento de Logon e esse 
 * processo poder� chamar rotinas de logon presentes nesse m�dulo.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */
 
#ifndef __LOGON_H
#define __LOGON_H    1

//
// Vari�veis globais.
// 
 
//flag, usar ou na� o default user. 
//int g_use_default_user; 

//
// == Prototypes ====================================
// 

int init_logon_manager (void);

#endif  

//
// End
//


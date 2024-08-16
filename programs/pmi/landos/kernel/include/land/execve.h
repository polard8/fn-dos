// execve.h 
// Created by Fred Nora.

#ifndef __EXECVE_H
#define __EXECVE_H    1

// efetua o serviço execve, rodando um novo programa
// no processo atual;
int 
sys_execve ( const char *pathname, 
             char *argv[], 
             char *envp[] );
        
#endif  

//
// End
//


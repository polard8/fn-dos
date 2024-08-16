// stdlib.h 
// Created by Fred Nora.

#ifndef __STDLIB_H
#define __STDLIB_H    1

/*
 atof 	string para float
 atoi 	string para integer
 atol 	string para long integer
 strtod 	string para double
 strtol 	string para long int
 strtoul 	string para unsigned long int

 Gera��o de seq��ncia pseudo-aleat�ria
rand 	gera um n�mero inteiro pseudo aleat�rio
srand 	seleciona a semente do gerador pseudo aleat�rio

Aloca��o e libera��o de mem�ria
malloc
calloc
realloc 	aloca mem�ria do "heap"
free 	libera mem�ria de volta para o "heap"

Controle de processos
abort 	for�a o t�rmino da execu��o
atexit 	registra uma fun��o "callback" para sa�da do programa
exit 	termina a execu��o do programa
getenv 	obt�m uma vari�vel de ambiente
system 	executa um comando externo

Ordenamento e procura
bsearch 	procura bin�ria em "array"
qsort 	ordena "array" segundo algoritmo Quick Sort

Matem�tica

valor absoluto
abs
labs 	

divis�o inteira
div
ldiv 	
  */


// A rotina terminou normalmente. 
#define EXIT_SUCCESS  0

// A rotina terminou de maneira anormal. 
#define EXIT_FAILURE  1

// N�meros pseudo-aleat�rios   
#define RAND_MAX  32767    //0x7FFF


/*
// tipos de retorno das fun��es div e ldiv.

typedef struct div_d div_t;
struct div_d 
{
	int quot;
	int rem;
};

typedef struct ldiv_d ldiv_t;
struct ldiv_d 
{
	long quot;
	long rem;
};
*/

//
// Prototypes ===================
//

void *kmalloc (size_t size);
void kfree (void *ptr);

// Returns a pseudo-random number in the range of 0 to RAND_MAX.
int rand (void);

//Alimenta a fun��o rand.
//void srand(unsigned int seed);

//@todo: talvez essa fun��o esteja declara erradamente em systemcall.
//int system(const char *string);

int __ptsname (int fd, char *buf, size_t buflen);

#endif   

//
// End
//


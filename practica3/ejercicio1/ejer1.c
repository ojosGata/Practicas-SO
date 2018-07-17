/* Algoritmo de Peterson para 2 variables*/
bandera[0] = false
  bandera[1] = false
  turno      = 0 
  p0: bandera[0] = true                         
      turno = 1                                 
      while( bandera[1] && turno == 1 );        
                //no hace nada; espera.                                
      // sección crítica                        
 
      // fin de la sección crítica            
      bandera[0] = false                       
      
   p1: bandera[1] = true
	   turno = 0
	   while( bandera[0] && turno == 0 );
	   //no hace nada; espera.
	   // sección crítica
	   // fin de la sección crítica
	      bandera[1] = false
	      
////////////////////////////////
// Variables compartidas
bandera: array[0..N-1] of -1..n-2; /* inicializada a –1 */
turno: array[0..N-2] of 0..n-1; /* inicializada a 0 */
 
// Protocolo para Pi ( i=0,...,N-1 )
j:0..N-2; /* variable local indicando la etapa */
for j = 0 to N-2
{
   bandera[i] = j;
   turno[j] = i;
   while [(∃ k ≠ i : bandera[k] ≥ j) ∧ (turno[k] == i)] do; 
}
<sección crítica>
bandera[i] = -1;




// Solucion al problema de la seccion critica para 2 procesos
// Algoritmo de Peterson

// Variables globales compartidas
typedef enum { PRIMERO, SEGUNDO } TURNO;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
TURNO TurnoProceso;

// Inicializacion de variables
P1QuiereEntrar = P2QuiereEntrar = FALSE;
TurnoProceso = PRIMERO;

void Proceso1(){
    extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
    extern TURNO TurnoProceso;

   while (TRUE) {
   	P1QuiereEntrar = TRUE;
   	TurnoProceso = SEGUNDO;
   	while (P2QuiereEntrar && TurnoProceso == SEGUNDO);
			//--------------------
			// SECCIÓN CRÍTICA
			//--------------------

		P1QuiereEntrar = FALSE;
		// Seccion residual
    }
}

void Proceso2(){
   extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
   extern TURNO TurnoProceso;

	while (TRUE) {
		P2QuiereEntrar = TRUE;
		TurnoProceso = PRIMERO;
		while (P1QuiereEntrar && TurnoProceso == PRIMERO);
			//--------------------
			// SECCIÓN CRÍTICA
			//--------------------
		P2QuiereEntrar = FALSE;
		// Secci�n residual
    }
}

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void * hebraCrea(); //Hebra que crea la variable dinámica
void * hebraRecibe(void * var); //Hebra que recibe la variable dinámica

int main(){
	pthread_t hilos[2];
	int * mensaje = NULL; //Puntero a la variable que se intercambiará
	
	srand(time(NULL));
	
	//Crea la hebra generadora del mensaje
	pthread_create(hilos,NULL,hebraCrea,NULL);
	//Recibe el mensaje
	pthread_join(hilos[0],(void **) &mensaje);
	
	//Envía el mensaje a la hebra receptora
	pthread_create(hilos+1,NULL,hebraRecibe,(void *) mensaje);
	//Espera a la hebra receptora
	pthread_join(hilos[1],NULL);
	
	//Imprime el mensaje recibido de la segunda hebra
	printf("Recibido %d\n",*mensaje);
	
	//Liberación de memoria
	free(mensaje);
	
	return 0;
}

void * hebraCrea(){
	int * var = NULL;
	
	var = (int *) calloc(1,sizeof(int));
	
	//Genera un mensaje aleatorio, lo imprime y lo devuelve
	*var = rand() % 30;
	
	printf("Enviado %d\n",*var);
	
	pthread_exit((void*) var);
}

void * hebraRecibe(void * var){
	int * p = (int*) var;
	
	//Imprime el mensaje recibido, lo modifica y lo devuelve
	printf("Recibido %d\n",*p);
	*p = rand() % 30;
	printf("Cambiado a %d\n",*p);
	
	pthread_exit((void *) p);
}


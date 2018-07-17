#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
//funciones
void* lector(void * arg);
void* escritor(void * arg);

//Variable globales
pthread_mutex_t mutexLeer =	PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexEscribir = PTHREAD_MUTEX_INITIALIZER;

int cuentaLector;
int miDato=0;

int main(){
	
	cuentaLector=0;
	//Iniciar hebras productora y consumidora
	
	pthread_t hiloEscritor;
	pthread_t hiloLector;
	printf("\nCreadndo Hilos...");
	//Lanzar hebras productora y consumidora
	pthread_create(&hiloLector, NULL, lector,NULL);
	pthread_create(&hiloEscritor,NULL, escritor, NULL);
	//	Esperar las hebras
	printf("\nEsperando los hilos.....");
	pthread_join(hiloLector,NULL);
	pthread_join(hiloEscritor,NULL);
	//Destruir los semaforos y variables de condicion
	printf("\nDestruyendo los hilos");
	pthread_mutex_destroy(&mutexLeer);
	pthread_mutex_destroy(&mutexEscribir);
}
void *lector(void *arg){  /* codigo del lector */ 
	int estadoLector, estadoEscritor;
	printf("\nAntes de entrar en el bucle infinito de lector");
	
	while(1){
		estadoLector=pthread_mutex_lock(&mutexLeer);  // acceder  al dato 
		if(estadoLector!=0){
			printf("Error al cerrar el mutex de lectura\n");
			exit(EXIT_FAILURE);
		}
		cuentaLector++;
		if(cuentaLector==1){
			estadoEscritor=pthread_mutex_lock(&mutexEscribir);  /* condicion de escribir bloqueada*/ 
			if(estadoEscritor!=0){
				printf("Error al cerrar el mutex:escribir");
				exit(EXIT_FAILURE);
			}	

		}
		estadoLector=pthread_mutex_unlock(&mutexLeer);
		if(estadoLector!=0){
			printf("Error al desbloquear la condicion: leer");
			exit(EXIT_FAILURE);
		}
		//LEERDATOS
		printf("\nLector %d y Mi dato es: %d\n",cuentaLector,miDato);
		estadoLector=pthread_mutex_lock(&mutexLeer);
		if(estadoLector!=0){
			printf("Error al bloquear la condicion: leer");
			exit(EXIT_FAILURE);
		}
		cuentaLector--;
		if(cuentaLector==0){
			estadoEscritor=pthread_mutex_unlock(&mutexEscribir);  /*condicion de escribir desbloqueada*/ 
			if(estadoEscritor!=0){
				printf("Error al desbloquear la condicion:escribir");
				exit(EXIT_FAILURE);
			}	
		
		}
		estadoLector=pthread_mutex_unlock(&mutexLeer); 
		if(estadoLector!=0){
	  		printf("Error al abrir el mutexLeer");
			exit(EXIT_FAILURE);
		}
	}
	
}
void *escritor(void * arg){
 	int s;
	while(1){
		s=pthread_mutex_lock(&mutexEscribir); // acceder al dato cierro el semaforo de escribir 
		if(s!=0){
			printf("Error al cerrar el mutex");
			exit(EXIT_FAILURE);
		} 
		miDato = miDato + 1;
		printf("\nProduciendo el dato... %d\n",miDato);
		s=pthread_mutex_unlock(&mutexEscribir); 
		if(s!=0){
			printf("Error al abrir el mutex");
			exit(EXIT_FAILURE);
		}
	}
	
}

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
pthread_cond_t leer = PTHREAD_COND_INITIALIZER;
pthread_cond_t escribir =	PTHREAD_COND_INITIALIZER;
int cuentaLector;
int miDato;

int main(){
	srand(time(NULL));
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
	pthread_cond_destroy(&leer);
	pthread_cond_destroy(&escribir);
}
void *lector(void *arg){  /* codigo del lector */ 
	int s;
	printf("\nAntes de entrar en el bucle infinito de lector");
	s=pthread_mutex_lock(&mutexLeer);  // acceder  al dato 
	if(s!=0){
		printf("Error al cerrar el mutex de lectura\n");
		exit(EXIT_FAILURE);
	}	
	while(1){
		
		s=pthread_cond_wait(&leer,&mutexEscribir);
		if(s!=0){
			printf("Error al bloquear la condicion: leer\n");
			exit(EXIT_FAILURE);
		}
		cuentaLector++;
		if(cuentaLector==1){
			s=pthread_cond_wait(&escribir,&mutexLeer);  /* condicion de escribir bloqueada*/ 
			if(s!=0){
				printf("Error al bloquear la condicion:escribir");
				exit(EXIT_FAILURE);
			}	

		}
		s=pthread_cond_signal(&leer);
		if(s!=0){
			printf("Error al desbloquear la condicion: leer");
			exit(EXIT_FAILURE);
		}
		//LEERDATOS
		printf("\nLector %d y Mi dato es: %d\n",cuentaLector,miDato);
		s=pthread_cond_wait(&leer,&mutexEscribir);
		if(s!=0){
			printf("Error al bloquear la condicion: leer");
			exit(EXIT_FAILURE);
		}
		cuentaLector--;
		if(cuentaLector==0){
			s=pthread_cond_signal(&escribir);  /*condicion de escribir desbloqueada*/ 
			if(s!=0){
				printf("Error al desbloquear la condicion:escribir");
				exit(EXIT_FAILURE);
			}	
		
		}
		s=pthread_cond_signal(&leer); /*Condicion de leer desbloqueada*/
		if(s!=0){
			printf("Error al desbloquear la condicion: leer");
			exit(EXIT_FAILURE);
		}
		s=pthread_mutex_unlock(&mutexLeer); 
		if(s!=0){
	  		printf("Error al abrir el mutexLeer");
			exit(EXIT_FAILURE);
		}
	}
	
}
void *escritor(void * arg){
 	int s;
	s=pthread_mutex_lock(&mutexEscribir); // acceder al dato cierro el semaforo de escribir 
	if(s!=0){
		printf("Error al cerrar el mutex");
		exit(EXIT_FAILURE);
	}
	while(1){  
		s=pthread_cond_wait(&escribir,&mutexLeer); // se bloquea  
		if(s!=0){
			printf("Error al bloquear la condicion: no_lleno");
			exit(EXIT_FAILURE);
		}
		miDato = (rand()%100) + 1;
		printf("\nProduciendo el dato...\n");
		s=pthread_cond_signal(&escribir); /* buffer no vacio */ 
		if(s!=0){
			printf("Error al desbloquear la condicion: no vacio");
			exit(EXIT_FAILURE);
		}
		s=pthread_mutex_unlock(&mutexEscribir); 
		if(s!=0){
			printf("Error al abrir el mutex");
			exit(EXIT_FAILURE);
		}
	}
	
}

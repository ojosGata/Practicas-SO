#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
//funciones
void* lector(void * arg);
void* escritor(void * arg);

//Variable globales
pthread_mutex_t mtxCL =	PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //Para exclusión mutua
pthread_cond_t no_leer = PTHREAD_COND_INITIALIZER;
pthread_cond_t no_escribir =	PTHREAD_COND_INITIALIZER;
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
	pthread_mutex_destroy(&mtxCL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&no_leer);
	pthread_cond_destroy(&no_escribir);
}
void *lector(void *arg){  /* codigo del lector */ 
	printf("\nAntes de entrar en el bucle infinito de lector");
	while(1){
		pthread_cond_wait(&no_escribir,&mtxCL);
		cuentaLector++;
		if(cuentaLector==1){
			pthread_mutex_lock(&mutex);  /* condicion de escribir bloqueada*/ 
		}
		pthread_cond_signal(&no_escribir);
		//LEERDATOS
		printf("\nLector %d y Mi dato es: %d\n",cuentaLector,miDato);
		pthread_cond_wait(&no_escribir,&mtxCL);
		cuentaLector--;
		if(cuentaLector==0){
			pthread_mutex_unlock(&mutex);  /*condicion de escribir desbloqueada*/ 
		}
		pthread_cond_signal(&no_escribir); /*Condicion de leer desbloqueada*/
	}
	
}
void *escritor(void * arg){
	while(1){  
		pthread_cond_wait(&no_leer,&mutex); // se bloquea  
		miDato = (rand()%100) + 1;
		printf("\nProduciendo el dato...\n");
		pthread_cond_signal(&no_leer); /* buffer no vacio */ 
		
	}
	
}

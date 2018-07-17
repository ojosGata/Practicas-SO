//El problema del baño público en la universidad
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <semaphore.h>

#define AFORO 3
#define HOMBRES 5
#define MUJERES 6

//Definición de semaforos

sem_t bath; /*Inicializado a 3 controla el acceso al baño*/
sem_t semHombre; /*Inicializado a 1 controla el acceso de los hombres*/
sem_t semMujer; /*Inicializado a 1 controla el acceso de las mujeres*/
sem_t semCola; /*Inicializado a 1 controla el acceso*/

//Variable globales
int usuarios=0;
void *mujer( void *arg);
void *hombre(void *arg);


int main(){
	srand(time(NULL));
	int i;
	int j;
	//Iniciamos semaforos
	sem_init(&bath, 0,AFORO);
	sem_init(&semHombre, 0, 1);
	sem_init(&semMujer,0,1);
	sem_init(&semCola,0,1);
	//Definición de los hilos para la mujeres y los hombres
	pthread_t hiloMujeres[MUJERES];
	pthread_t hiloHombres[HOMBRES];
	//Creación de los hilos para mujeres y hombres
	for(i=0; i<MUJERES; i++){
		pthread_create(&hiloMujeres[i],NULL,mujer,NULL);
	}
	for(j=0;j<HOMBRES;j++){
		pthread_create(&hiloHombres[j],NULL, hombre,NULL);
	}
	//Espera de los hilos
	for(i=0;i<MUJERES;i++){
		pthread_join(hiloMujeres[i],NULL);
	}
	for(j=0;j<HOMBRES;j++){
		pthread_join(hiloHombres[j],NULL);
	}
	//destruir semaforos 
	sem_destroy(&bath);
	sem_destroy(&semHombre);
	sem_destroy(&semMujer);
	sem_destroy(&semCola);
}
void *mujer(void *arg){
	sem_wait(&semCola);
	sem_wait(&semMujer);
	usuarios++;
	if(usuarios == 1){
		sem_wait(&semHombre);
	}
	sem_post(&semMujer);
	sem_post(&semCola);
	sem_wait(&bath);//INiciamos sección critica
	printf("\nHay %d mujeres en el servicio...",usuarios);
	sleep((rand()%3));
	sem_post(&bath); //finalizamos la seccion critica
	sem_wait(&semCola);
	sem_wait(&semMujer);
	usuarios--;
	if(usuarios==0){
		sem_post(&semHombre);
	}
	sem_post(&semMujer);
	sem_post(&semCola);
	//pthread_exit();
}
void *hombre(void *arg){
	sem_wait(&semCola);
	sem_wait(&semHombre);
	usuarios++;
	if(usuarios == 1){
		sem_wait(&semMujer);
	}
	sem_post(&semHombre);
	sem_post(&semCola);
	sem_wait(&bath);//INiciamos sección critica
	printf("\nHay %d hombre en el servicio...",usuarios);
	sleep(rand()%3);
	sem_post(&bath);//Finalizamos la seccion critica
	sem_wait(&semCola);
	sem_wait(&semHombre);
	usuarios--;
	if(usuarios==0){
		sem_post(&semMujer);
	}
	sem_post(&semHombre);
	sem_post(&semCola);
	//pthread_exit(void);
}

